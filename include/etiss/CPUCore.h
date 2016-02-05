/**

@copyright

<pre>

	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.

</pre>

@author Marc Greim <marc.greim@mytum.de>

@date July 23, 2014

@version 0.1

*/
/**
	@file

	@brief defines main cpu core interface


*/

#ifndef ETISS_INCLUDE_CPUCORE_H_
#define ETISS_INCLUDE_CPUCORE_H_

#include "etiss/ClassDefs.h"
#include "etiss/Misc.h"
#include "etiss/LibraryInterface.h"
#include "etiss/JIT.h"
#include "etiss/CPUArch.h"
#include "etiss/Translation.h"
#include "etiss/System.h"
#include "etiss/InterruptHandler.h"
#include "etiss/Plugin.h"
#include "etiss/jit/ReturnCode.h"

#include <mutex>
#include <memory>
#include <list>

namespace etiss
{

// change this to enable an approximate instruction counter for processors. the instruction counter can be accessed via the VirtualStruct of the processor. the field is named "instructionCounter"
#define ETISS_CPUCORE_DBG_APPROXIMATE_INSTRUCTION_COUNTER 0


/**
	@brief instance of a cpu core
*/
class CPUCore : public VirtualStructSupport ,public etiss::ToString
{
    friend class CPUArchRegListenerInterface;
private:
    CPUCore(std::string name,std::shared_ptr<etiss::CPUArch> arch);
    class InterruptVectorWrapper : public InterruptVector
    {
    private:
        std::list<etiss::InterruptListenerPlugin*> plugins_;
    public:
        CPUCore & parent_;
        InterruptVectorWrapper(CPUCore & parent);
        virtual void setBit(unsigned bit,bool state);
        virtual bool getBit(unsigned bit) const;
        virtual unsigned width() const;
        virtual bool isActive() const;
        virtual void clear();
        void load(std::list<std::shared_ptr<etiss::Plugin> > plugins);
    };
public:
    ~CPUCore();
    /**
    	@brief reset the cpu state. NOTE: startindex != start address
    */
    inline void reset(etiss::uint64 * startindex)
    {
        arch_->resetCPU(cpu_,startindex);
    }
    /**
    	@return returns a pointer to the architecture specific cpu state structure
    */
    inline ETISS_CPU * getState()
    {
        return cpu_;
    }
    /**
        @return a virtual structure that allows to access fields of the cpu structure and sub srtuctures (e.g. plugins)
    */
    virtual inline std::shared_ptr<VirtualStruct> getStruct()
    {
        return vcpu_;
    }

    /**
    	@return returns a pointer to the interrupt vector of this cpu.
    */
    inline etiss::InterruptVector * getInterruptVector()
    {
        return intwrapper_;
    }
    /**
    	@brief get cpu architecture
    */
    inline std::shared_ptr<etiss::CPUArch> getArch()
    {
        return arch_;
    }
    /**
    	@brief set jit instance used for execution. if no jit instance is specified then the first loaded jit instance is used
    	@see etiss::loadJIT
    	@see etiss::getJIT
    	@see etiss::listJIT
    */
    inline void set(std::shared_ptr<etiss::JIT> jit)
    {
        jit_ = jit;
    }
    /**
    	@brief enable/disable timer. Has no effect if the architecture doesn't support a timer
    	@return true if timer enabled and supported by the architecture
    */
    inline void setTimer(bool on)
    {
        std::lock_guard<std::mutex> lock(mu_);
        timer_enabled_ = on;
    }
    /**
    	@brief adds a plugin. how the plugin is used is defined by the classes it implements
    	@attention the same plugin may not be added multiple times.
    	@see etiss::TransTranslatorPlugin
    	@see etiss::CoroutinePlugin
    	@see etiss::SystemWrapperPlugin
    */
    void addPlugin(std::shared_ptr<etiss::Plugin> plugin);
    /**
    	@brief remove a plugin
    */
    void removePlugin(std::shared_ptr<etiss::Plugin> plugin);
    /**
    	@brief remove all plugins
    */
    inline void removePlugins()
    {
        std::lock_guard<std::mutex> lock(mu_);
        plugins.clear();
    }
    /**
    	@brief set the number of blocks jumps in between the coroutines are not executed
    */
    inline void setBlockChainCount(unsigned bcc)
    {
        bcc_ = bcc;
    }
    /**
    	@brief function to execute this cpu with the given system.
    	@detail this function is (like any other function of this class) threadsafe. however if any function including this one is called while execute(1) is running, it will block until execute(1) returns.
    */
    etiss::int32 execute(ETISS_System & system);
    /**
    	@see execute(ETISS_System & system)
    */
    inline etiss::int32 execute(etiss::System & system)
    {
        std::shared_ptr<ETISS_System> sys = etiss::wrap(&system);
        if (sys.get() == 0)
            return RETURNCODE::GENERALERROR;
        etiss::uint32 ret = execute(*(sys.get()));
        return ret;
    }
    /**
    	@brief return the name of this cpu core
    */
    inline const std::string & getName()
    {
        return name_;
    }
    /**
    	@brief return the name of the configured jit or "" if no jit is present
    */
    inline std::string getJITName()
    {
        std::shared_ptr<etiss::JIT> jit = jit_;
        if (jit.get())
        {
            return jit->getName();
        }
        else
        {
            return "";
        }
    }

    inline const std::string & toString() const
    {
        return name_;
    }

public:
    /**
    	@brief tries to create a CPUCore instance with the given architecture

    	@return 0, if the given architecture is not present
    */
    static std::shared_ptr<CPUCore> create(std::string archname,std::string instancename,std::map<std::string,std::string> archoptions = std::map<std::string,std::string>());
    /**
    	@brief returns a list of currently present cpu cores
    */
    static std::list<std::string> list();
private:
    std::shared_ptr<etiss::CPUArch> arch_; ///< cpu architecture of this cpu core. may never be 0 or changed
    std::string name_; ///< name of the cpu core
    ETISS_CPU * cpu_;  ///< cpu state structure allocated by arch_
    std::shared_ptr<etiss::VirtualStruct> vcpu_;
    etiss::InterruptVector* intvector_; ///< cpu interrupt vector derived from cpu_ and allocated by arch_
    InterruptVectorWrapper * intwrapper_; ///< wrapped interrupt vector to allow interrupt listening
    bool timer_enabled_; ///< if true the a timer plugin allocated by arch_ will be added in CPUCore::execute
    std::shared_ptr<etiss::JIT> jit_; ///< JIT instance to use. may be 0 (etiss::getDefaultJIT() will be used in that case)
    std::mutex mu_;	///< mutex to lock the configuration of this cpu core. etiss::CPUCore::execution holds this lock during execution
    std::list<std::shared_ptr<Plugin> > plugins; ///< list of all plugins
    unsigned bcc_;
    unsigned exception_skip_count_;
    int blockCacheLimit_; ///TODO: possiblility to limit the cache size 

public:
   uint64_t instrcounter; /// this field is always present to maintain ABI compability but it is only used if ETISS_CPUCORE_DBG_APPROXIMATE_INSTRUCTION_COUNTER is set to 1

private:
    static std::mutex instances_mu_; ///< mutext for access to a list of cpu core instances
    static std::list<std::weak_ptr<CPUCore> > instances_; ///< list of weak references to currently present cpu cores (@see etiss::CPUCore::list)

};

}

#endif
