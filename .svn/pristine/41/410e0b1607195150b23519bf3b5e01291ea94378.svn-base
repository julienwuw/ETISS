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

@date July 29, 2014

@version 0.1

*/
/**
	@file

	@brief implementation of etiss/CPUCore.h

	@detail

*/
#include "etiss/CPUCore.h"
#include "etiss/ETISS.h"

using namespace etiss;

/**
	@see etiss/CPUArch.h
*/
void CPUArchRegListenerInterface::signalChangedRegisterValue(ETISS_CPU* cpu,const char * registerName)
{
    CPUCore * core = (CPUCore*) cpu->_etiss_private_handle_;
    if (!core){
    	etiss::log(etiss::ERROR,"CPUArchRegListenerInterface::signalChangedRegisterValue() called from outside etiss::CPUCore::execute(). this should not happen and indicates a faultiy CPUArch (or Plugin) implementation. This function may have been called indirectly from ETISS_signalChangedRegisterValue()");
    	return;
    }
    auto vs = core->getStruct();
    if (!vs){
    	etiss::log(etiss::ERROR,"CPUArchRegListenerInterface::signalChangedRegisterValue() called but CPUArch didn't provide a VirtualStruct.");
    	return;
    }
    auto field = vs->findName(registerName);
    if (!field){
    	field = vs->findPrettyName(registerName);
    	if (!field){
	    	etiss::log(etiss::ERROR,"CPUArchRegListenerInterface::signalChangedRegisterValue() called but the associated VirtualStruct has not the specified field.",registerName);
    		return;
    	}
    }
    if (!(field->flags_&etiss::VirtualStruct::Field::L)){
    	etiss::log(etiss::ERROR,"CPUArchRegListenerInterface::signalChangedRegisterValue() called but the field of the associated VirtualStruct doesn't have the listerner flags set (etiss::VirtualStruct::Field::L).",registerName);
    	return;
    }
    
    field->signalWrite();
}

CPUCore::InterruptVectorWrapper::InterruptVectorWrapper(CPUCore & parent) : parent_(parent) {}
void CPUCore::InterruptVectorWrapper::setBit(unsigned bit,bool state){
	bool consumed = false;
	for (auto iter = plugins_.begin();iter != plugins_.end();iter++){
		consumed |= (*iter)->interruptWrite(bit,state);
	}
	if (!consumed)
		parent_.intvector_->setBit(bit,state);
}
bool CPUCore::InterruptVectorWrapper::getBit(unsigned bit) const {
	return parent_.intvector_->getBit(bit);
}
unsigned CPUCore::InterruptVectorWrapper::width() const{
	return parent_.intvector_->width();
}
bool CPUCore::InterruptVectorWrapper::isActive() const{
	return parent_.intvector_->isActive();
}
void CPUCore::InterruptVectorWrapper::clear(){
	for (unsigned i = 0;i<width();i++){
		setBit(i,false);
	}
}
void CPUCore::InterruptVectorWrapper::load(std::list<std::shared_ptr<etiss::Plugin> > plugins){
	for (auto iter = plugins.begin();iter != plugins.end();iter++){
		etiss::Plugin * p = iter->get();
		if (p){
			etiss::InterruptListenerPlugin * ilp = p->getInterruptListenerPlugin();
			if (ilp){
				plugins_.push_back(ilp);
			}
		}
	}
}


std::mutex CPUCore::instances_mu_;
std::list<std::weak_ptr<CPUCore> > CPUCore::instances_;

CPUCore::CPUCore(std::string name,std::shared_ptr<etiss::CPUArch> arch) : arch_(arch),name_(name),cpu_(arch->newCPU()),vcpu_(arch->getVirtualStruct(cpu_)),intvector_(arch->createInterruptVector(cpu_)){
	arch_->resetCPU(cpu_,0);
	timer_enabled_ = true;
	bcc_ = 1;
	exception_skip_count_ = 0;
	blockCacheLimit_ = -1;
	intwrapper_ = intvector_?new InterruptVectorWrapper(*this):0;
#if ETISS_CPUCORE_DBG_APPROXIMATE_INSTRUCTION_COUNTER
    instrcounter = 0;
#endif
	
	if (cpu_){
        if (vcpu_){
            if (!vcpu_->findName("instructionPointer")){
                ETISS_CPU * cpu = cpu_;
                vcpu_->addField(
                    (new etiss::VirtualStruct::Field(
                                                    *vcpu_,
                                                    "instructionPointer",
                                                    "",
                                                    etiss::VirtualStruct::Field::R|etiss::VirtualStruct::Field::P,
                                                    8,
                                                    false,
                                                    [cpu](){
                                                    return (uint64_t) cpu->instructionPointer;},
														nullptr))->setDeleteP(std::function<void(etiss::VirtualStruct::Field*)>([](etiss::VirtualStruct::Field*f) {delete f; }))
                                                    );
            }
#if ETISS_CPUCORE_DBG_APPROXIMATE_INSTRUCTION_COUNTER
            if (!vcpu_->findName("instructionCounter"))
            {
                vcpu_->addField(
                    (new etiss::VirtualStruct::Field(
                                                    *vcpu_,
                                                    "instructionCounter",
                                                    "",
                                                    etiss::VirtualStruct::Field::R|etiss::VirtualStruct::Field::W|etiss::VirtualStruct::Field::P,
                                                    8,
                                                    false,
                                                    [this](){
                                                    return (uint64_t) instrcounter;},
                                                    [this](uint64_t v){
                                                    instrcounter = v;}
													    ))->setDeleteP(std::function<void(etiss::VirtualStruct::Field*)>([](etiss::VirtualStruct::Field*f) {delete f; }))
                                                    );
            }
#endif
        }
	}

}

void CPUCore::addPlugin(std::shared_ptr<etiss::Plugin> plugin)
    {
        if (plugin.get() != 0)
        {
            {
                std::lock_guard<std::mutex> lock(mu_);
                // check if the plugin is already present
                for ( const std::shared_ptr<etiss::Plugin> & p : plugins)
                {
                    if (p.get() == plugin.get())
                    {
                        etiss::log(etiss::WARNING,"cannot add the same plugin multiple times",*this,*(plugin.get()));
                        return;
                    }
                }
                if (plugin->plugin_core_){
	                etiss::log(etiss::WARNING,"A plugin has been added to multiple cores. This could be a serve problem.",*this,*(plugin.get()));
                }
                plugins.push_back(plugin);
            }
            plugin->plugin_core_ = this;
            plugin->addedToCPUCore(this);
        } else {
            etiss::log(etiss::WARNING,"etiss::CPUCore::addPlugin() called without passing a valid plugin pointer.",*this);
        }
    }
    
void CPUCore::removePlugin(std::shared_ptr<etiss::Plugin> plugin)
    {
        etiss::Plugin * p = plugin.get();
        bool removed = false;
        {
            std::lock_guard<std::mutex> lock(mu_);
            for (auto iter = plugins.begin(); iter != plugins.end();)
            {
                if (iter->get() == plugin.get())
                {
                    plugins.erase(iter++);
                    removed = true;
                    break;
                } else {
	                iter++;
               }
            }
        }
        if (removed)
        {
            p->plugin_core_ = nullptr;
            p->removedFromCPUCore(this);
        }
    }

std::shared_ptr<CPUCore> CPUCore::create(std::string archname,std::string instancename,std::map<std::string,std::string> archoptions)
{

    etiss::forceInitialization();

    // get arch
    std::shared_ptr<etiss::CPUArch> arch = getCPUArch(archname,archoptions);

    if (arch.get() == 0){
    	etiss::log(etiss::INFO,"Architecture not found.",archname);
    	return 0;
    }

    // creat core
    std::shared_ptr<CPUCore> ret(new CPUCore(instancename,arch));

    {
        std::lock_guard<std::mutex> lock(instances_mu_);
        instances_.emplace_back(ret);
    }

    return ret;

}

std::list<std::string> CPUCore::list()
{
    std::list<std::string> ret;
    {
        std::lock_guard<std::mutex> lock(instances_mu_);
        for (auto iter = instances_.begin(); iter != instances_.end(); iter++)
        {
            auto ptr = iter->lock();
            if (ptr.get() != 0)
            {
                ret.push_back(ptr->getName()+" ["+ptr->getArch()->getArchName()+","+ptr->getJITName()+"]"); // "CORENAME [ARCHITECTURE,JIT]
            }
        }
    }
    return ret;
}


CPUCore::~CPUCore()
{
    arch_->deleteInterruptVector(intvector_,cpu_);
    if (vcpu_){
        vcpu_->close();
        vcpu_.reset();
    }
    arch_->deleteCPU(cpu_);
    delete intwrapper_;
}

/**
	generates and compiles test code for the just in time compiler to check size of basic types
*/
static bool verifyJITSizeOf(std::string structname,etiss::int32 expected_size,etiss::JIT * jit,std::string prefix = std::string())
{
    if (jit == 0)
        return false;
    // generate code
    std::string error;
    std::string code = std::string(prefix+"\n#include \"etiss/jit/CPU.h\"\n#include \"etiss/jit/System.h\"\n#include \"etiss/jit/ReturnCode.h\"\n #include \"etiss/jit/types.h\"\n#include \"etiss/jit/fpu/softfloat.h\"\n etiss_int32 get_size(){ return sizeof(")+structname+");}";

    std::set<std::string> headers;
    headers.insert(etiss::cfg().get<std::string>("etiss_wd","./")+"include_c/");
    // compile
    void * handle = jit->translate(code,headers,std::set<std::string>(),std::set<std::string>(),error,true);
    if (handle == 0)
    {
        etiss::log(etiss::ERROR,std::string("Failed to compile test code [")+code+"] to check struct size: "+error);
        return false;
    }
    // check size
    typedef etiss::int32 (*get_size)(void);
    get_size gs = (get_size) jit->getFunction(handle,"get_size",error);
    if (gs == 0)
    {
        jit->free(handle);
        etiss::log(etiss::ERROR,std::string("Failed to get compiled function [get_size] to check struct size: ")+error);
        return false;
    }
    etiss::int32 r = gs();
    jit->free(handle);
    if (r != expected_size)
    {
        std::stringstream ss;
        ss << "Unexpected size of " << structname << ";";
        ss << " Expected: " << expected_size;
        ss << " Is: " << r;
        etiss::log(etiss::ERROR,ss.str());
        return false;
    }
    return true;

}
/**
	generates test code to check alignment of structures in the just in time compiler
*/
static bool verifyJITPragmaPack(etiss::JIT * jit)
{
    if (jit == 0)
        return false;
    std::string error;
    std::stringstream stru;
    etiss::int32 expected_size = 0;

    // add some types to test
    std::vector<const char * > types;
    std::vector<etiss::int32> typeslen;
    types.push_back("etiss_int8");
    typeslen.push_back(sizeof(etiss_int8));
    types.push_back("etiss_uint8");
    typeslen.push_back(sizeof(etiss_uint8));
    types.push_back("etiss_int16");
    typeslen.push_back(sizeof(etiss_int16));
    types.push_back("etiss_uint16");
    typeslen.push_back(sizeof(etiss_uint16));
    types.push_back("etiss_int32");
    typeslen.push_back(sizeof(etiss_int32));
    types.push_back("etiss_uint32");
    typeslen.push_back(sizeof(etiss_uint32));
    types.push_back("etiss_int64");
    typeslen.push_back(sizeof(etiss_int64));
    types.push_back("etiss_uint64");
    typeslen.push_back(sizeof(etiss_uint64));
    types.push_back("void*");
    typeslen.push_back(sizeof(void*));

    stru << "struct _etiss_test_struct {\n";
    // add eacht type followed by any other type to create different combinations
    for (size_t i = 0; i < types.size(); i++)
    {
        stru << types[i] << " var_" << i << ";\n";
        expected_size += typeslen[i];
        for (size_t j = 0; j < types.size(); j++)
        {
            if (j != i)
            {
                stru << types[j] << " var_" << i  << "_"<< j << ";\n";
                expected_size += typeslen[j];
            }
        }
    }

    stru << "};";

    std::string code = std::string("\n#include \"etiss/jit/types.h\"\n#pragma pack(push, 1)\n")+stru.str()+"\n#pragma pack(pop)\n etiss_int32 get_size(){ return sizeof(struct _etiss_test_struct);}";

    std::set<std::string> headers;
    headers.insert(etiss::cfg().get<std::string>("etiss_wd","./")+"include_c/");
    // compile
    void * handle = jit->translate(code,headers,std::set<std::string>(),std::set<std::string>(),error,true);
    if (handle == 0)
    {
        etiss::log(etiss::ERROR,std::string("Failed to compile test code [")+code+"] to check struct size: "+error);
        return false;
    }
    typedef etiss::int32 (*get_size)(void);
    // check size
    get_size gs = (get_size) jit->getFunction(handle,"get_size",error);
    if (gs == 0)
    {
        jit->free(handle);
        etiss::log(etiss::ERROR,std::string("Failed to get compiled function [get_size] to check struct size: ")+error);
        return false;
    }
    etiss::int32 r = gs();
    jit->free(handle);
    if (r != expected_size)
    {
        std::stringstream ss;
        ss << "Unexpected size of test structure;";
        ss << " Expected: " << expected_size;
        ss << " Is: " << r;
        etiss::log(etiss::ERROR,ss.str());
        return false;
    }
    return true;

}

/**
	small helper function to handle exceptions. in most cases the exception is simply passed on to etiss::CPUArch::handleExcpetion()
*/
static void etiss_CPUCore_handleException(ETISS_CPU * cpu,etiss::int32 & code,BlockLink * & block_ptr,Translation & translator,CPUArch * arch)
{

#if DEBUG
    if (unlikely(code == RETURNCODE::NOERROR))
    {
        etiss::log(etiss::ERROR,"etiss_CPUCore_handleException may not be called with error code NOERROR");
    }
#endif

    switch (code)
    {
    case RETURNCODE::RELOADBLOCKS:
        block_ptr = 0; // doesn't hold a reference and thus might become invalid
        translator.unloadBlocks();
        code = RETURNCODE::NOERROR;
        return;
	case RETURNCODE::RELOADCURRENTBLOCK:
		if (block_ptr)
			block_ptr->valid = false; // invalidate but don't delete block
		block_ptr = 0;
        code = RETURNCODE::NOERROR;
        return;
    case RETURNCODE::GDBNOERROR:
        code = RETURNCODE::NOERROR;
        return;
    case RETURNCODE::CPUFINISHED:
        return;
    default:
        code = arch->handleException(code,cpu);
        return;
    }


}

class LegacyRegisterDevicePluginListener : public etiss::VirtualStruct::Field::Listener {
public:
	std::list<etiss::RegisterDevicePlugin*>	plugins;
	LegacyRegisterDevicePluginListener(const std::list<etiss::RegisterDevicePlugin*> & plugins_) : plugins(plugins_){}
	virtual ~LegacyRegisterDevicePluginListener(){}
	virtual void write(etiss::VirtualStruct::Field & field,uint64_t val){
		std::string name = field.name_;
		const char * cname = name.c_str();
		for (auto plugin : plugins){
			if (plugin){
				plugin->changedRegister(cname);
			}
		}
	}
};

etiss::int32 CPUCore::execute(ETISS_System & _system)
{

    ETISS_System * system = &_system; // change to pointer for reassignments

    if (!ETISS_System_isvalid(system)){ // check if required functions are present
        return RETURNCODE::INVALIDSYSTEM;
   	}

    std::lock_guard<std::mutex> lock(mu_); // lock class fields from modification

    CPUArch * arch = arch_.get(); // get cpu arch

    if (arch == 0)
        return RETURNCODE::GENERALERROR;


    ETISS_CPU * cpu = cpu_; // get cpu structure

    if (cpu == 0)
    {
        return RETURNCODE::GENERALERROR;
    }

    cpu->_etiss_private_handle_ = (void*)this; // init pointer to execute RegisterDevicePlugins. the value of tis pointer may be invalid/subject to change and may not be used by external code

    // get JIT instance
    std::shared_ptr<JIT> jiti = jit_; // copy jit because it may change

    if (jiti.get() == 0)  // if not present fall back to first loaded jit implementation
    {
        etiss::log(etiss::INFO,std::string("Using default jit instance for CPUCore: ")+name_);
        jiti = etiss::getDefaultJIT();
    }

    if (jiti.get() == 0)  // jit must be present
    {
        etiss::log(etiss::ERROR,std::string("No JIT available to ")+name_);
        return RETURNCODE::JITERROR;
    }

    // verify jit
    if (etiss::cfg().get<bool>("verifyJIT",true))
    {
        if (!verifyJITSizeOf("etiss_int64",sizeof(etiss_int64),jiti.get())) return RETURNCODE::JITCOMPILATIONERROR;
        if (!verifyJITSizeOf("etiss_int32",sizeof(etiss_int32),jiti.get())) return RETURNCODE::JITCOMPILATIONERROR;
        if (!verifyJITSizeOf("etiss_int16",sizeof(etiss_int16),jiti.get())) return RETURNCODE::JITCOMPILATIONERROR;
        if (!verifyJITSizeOf("etiss_int8",sizeof(etiss_int8),jiti.get())) return RETURNCODE::JITCOMPILATIONERROR;
        if (!verifyJITSizeOf("ETISS_CPU",sizeof(ETISS_CPU),jiti.get())) return RETURNCODE::JITCOMPILATIONERROR;
        if (!verifyJITPragmaPack(jiti.get())) return RETURNCODE::JITCOMPILATIONERROR;
        etiss::log(etiss::INFO,std::string("JIT compiler ")+jiti->getName()+" has passed the verification tests (tested by CPUCore "+name_+")");
    }
	// add default timer plugin from arch
    if (timer_enabled_)
    {
        Plugin * timerInstance = arch->newTimer(cpu);
        if (timerInstance==0)
        {
            etiss::log(etiss::ERROR,"ERROR: default timer requested but not supported by architecture");
            return RETURNCODE::GENERALERROR;
        }
        else
        {
            auto local_arch = arch_;
            plugins.push_back(std::shared_ptr<etiss::Plugin>(timerInstance,[local_arch](etiss::Plugin* p)
            {
                local_arch->deleteTimer(p);
            }));
        }
    }

    // copy system wrapper plugins to list and update system (pre plugin init)
    std::list<SystemWrapperPlugin*> syswrappers;
    {
        for (auto iter = plugins.begin(); iter != plugins.end(); iter++)
        {
            SystemWrapperPlugin* c = iter->get()->getSystemWrapperPlugin();
            if (c != 0)
            {
                ETISS_System * wsys = c->wrap(cpu,system);
                if (wsys != 0)
                {
                    syswrappers.push_front(c); // inverse order for easy iteration
                    system = wsys;
                }
                else
                {
                    std::cout << "WARNING: SystemWrapperPlugin \"" << c->getPluginName() << "\" failed to wrap ETISS_System instance"<< std::endl;
                }
            }
        }
    }

    // initialize plugins
    for (auto iter = plugins.begin(); iter != plugins.end(); iter++)
    {
        Plugin * p = iter->get();
        if (p)
        {
            p->plugin_cpu_ = cpu;
            p->plugin_system_ = system;
            p->plugin_arch_ = arch;
            p->init(cpu,system,arch);
        }
    }

    // copy coroutine plugins to array
    bool cor_enabled = false;
    unsigned cor_count = 0;
    CoroutinePlugin ** cor_array = 0;
    {
        std::list<CoroutinePlugin*> cl;
        for (auto iter = plugins.begin(); iter != plugins.end(); iter++)
        {
            CoroutinePlugin* c = iter->get()->getCoroutinePlugin();
            if (c != 0)
            {
                cl.push_back(c);
            }
        }
        cor_count = (unsigned)cl.size();
        if (cor_count>0)
            cor_array = new CoroutinePlugin*[cor_count];
        unsigned i = 0;
        for (std::list<CoroutinePlugin*>::iterator iter = cl.begin(); iter!= cl.end(); iter++)
        {
            cor_array[i++] = *iter;
        }
        cor_enabled = cor_count > 0;
    }



    // create translation object
    Translation translation(arch_,jiti,plugins,*system,*cpu);

    void ** plugins_handle_ = translation.init();

    if (plugins_handle_ == nullptr){
		return etiss::RETURNCODE::GENERALERROR;
    }



    //enable RegisterDevicePlugin listeneing by adding a listener to all fields of the VirtualStruct
    etiss::VirtualStruct::Field::Listener * listener = 0;
    {
    	std::list<RegisterDevicePlugin*> regdevices;
        for (auto iter = plugins.begin(); iter != plugins.end(); iter++)
        {
            RegisterDevicePlugin* c = iter->get()->getRegisterDevicePlugin();
            if (c != 0)
            {
                regdevices.push_back(c);
            }
        }
        if (!regdevices.empty()){
        	etiss::log(etiss::INFO,"etiss::RegisterDevicePlugin is a legacy convenience plugin. it may become deprecated later on. consider using etiss::VirtualStruct::Field::Listener to directly listen only for relevant fields.");
        
        	if (vcpu_){
        
		    	listener = new LegacyRegisterDevicePluginListener(regdevices);
		    	
		    	vcpu_->foreachField ([listener](std::shared_ptr<etiss::VirtualStruct::Field> f){f->addListener(listener);}); // add listener to all current field of struct
		    	
		    	//TODO: maybe later VirtualStruct will support a listener for added/removed fields. in that case the lisener of this function should also be added to new fields
        	
        	} else {
        		etiss::log(etiss::WARNING,"etiss::RegisterDevicePlugin added to a CPUCore that doesn't have a VirtualStruct.",name_);	
        	}
        
        }
    }

    // start execution loop

    float startTime = (float)clock()/CLOCKS_PER_SEC; //TESTING

    BlockLink * blptr = 0; ///< poiter to the current block

    etiss::int32 exception = RETURNCODE::NOERROR;


    // execution loop
    {
#if ETISS_DBG_ICOUNT_LIMIT > 0 && ETISS_CPUCORE_DBG_APPROXIMATE_INSTRUCTION_COUNTER
        while (likely(instrcounter < ETISS_DBG_ICOUNT_LIMIT))
        {
#else
        while (true)
        {
#endif

            // execute coroutines
            if (likely(cor_enabled))
            {
                for (unsigned i = 0; i<cor_count; i++) // iterate over plugins
                {
                    exception = cor_array[i]->execute();	// execute plugin
                    if (unlikely(exception != RETURNCODE::NOERROR))  // check exception
                    {
                        etiss_CPUCore_handleException(cpu,exception,blptr,translation,arch); // handle exception
                        if (unlikely(exception != RETURNCODE::NOERROR))  // check if exception handling failed
                        {
                            goto loopexit; // return exception; terminate cpu
                        }
                    }
                }
            }

            for (unsigned bc = 0; bc<bcc_; bc++)
            {
                // if not block internal jump // NOTE: removed since tests showed that this decreases performance
                //if (!(blptr != 0 && blptr->valid && blptr->start<=cpu->instructionPointer && blptr->end > cpu->instructionPointer)){
                blptr = translation.getBlockFast(blptr,cpu->instructionPointer); // IMPORTANT: no pointer reference is kept here. if the translator performs a cleanup then blptr must be set to 0
                //}

                if (unlikely(blptr == 0))  // if no block function pointer could be acquired
                {
                    if (false)
                    {
                        // emulation interface? switch jit?
                        exception = RETURNCODE::ARCHERROR;
                        goto loopexit;
                    }
                    else
                    {
                        std::cout << "CPU execution stopped: Cannot execute from instruction index " << std::hex << cpu->instructionPointer << ": no translated code available" << std::endl;
                        exception = RETURNCODE::JITCOMPILATIONERROR;
                        goto loopexit;
                    }

                }
                else
                {
                    //etiss::log(etiss::FATALERROR,"disabled etiss iss");
#if ETISS_CPUCORE_DBG_APPROXIMATE_INSTRUCTION_COUNTER
                    uint64 oldinstrptr = cpu->instructionPointer; //TESTING
#endif

                    exception = (*(blptr->execBlock))(cpu,system,plugins_handle_);

#if ETISS_CPUCORE_DBG_APPROXIMATE_INSTRUCTION_COUNTER
                    instrcounter += blptr->end-oldinstrptr; //TESTING ///TODO handle early exception exit?
#endif

                }

                // check for exception in executed block
                if (unlikely(exception != RETURNCODE::NOERROR))
                {
                    etiss_CPUCore_handleException(cpu,exception,blptr,translation,arch); // handle exception
                    if (unlikely(exception != RETURNCODE::NOERROR))  // check if exception handling failed
                    {
                        goto loopexit; // exception; terminate cpu
                    }
                }
            }

            // sync time after block
            system->syncTime(system->handle,cpu);

        }
    }

loopexit:

    float endTime = (float)clock()/CLOCKS_PER_SEC;

    // print some statistics
    etiss::log(etiss::INFO,std::string("CPUTime: ")+etiss::toString(cpu->cpuTime_ps/1000000000000.0) + " Time: " + etiss::toString(endTime-startTime));
    etiss::log(etiss::INFO,std::string("CPUCycles (estimated): ") + etiss::toString(cpu->cpuTime_ps/(float)cpu->cpuCycleTime_ps));
    etiss::log(etiss::INFO,std::string("MIPS (estimated): ") + etiss::toString(cpu->cpuTime_ps/(float)cpu->cpuCycleTime_ps/(endTime-startTime)/1000000.0));
#if ETISS_CPUCORE_DBG_APPROXIMATE_INSTRUCTION_COUNTER
    etiss::log(etiss::INFO,std::string("MIPS (good estimation): ") + etiss::toString(instrcounter/((double)cpu->cpuTime_ps/1000000.0)));
#endif

    // cleanup plugins
    for (auto iter = plugins.begin(); iter != plugins.end(); iter++)
    {
        Plugin * p = iter->get();
        if (p)
        {
            p->cleanup();
            p->plugin_cpu_ = nullptr;
            p->plugin_system_ = nullptr;
            p->plugin_arch_ = nullptr;
        }
    }

    // undo system wrapping
    for (std::list<SystemWrapperPlugin*>::iterator iter = syswrappers.begin() ; iter != syswrappers.end(); iter++)
    {
        ETISS_System * psys = (*iter)->unwrap(cpu,system);
        if (psys != 0)
        {
            system = psys;
        }
        else
        {
            std::cout << "SERVE WARNING: SystemWrapperPlugin \"" << (*iter)->getPluginName() << "\" failed to unwrap ETISS_System instance. Most likely results in a memory leak."<< std::endl;
            break;
        }
    }

    delete[] cor_array;

	if (listener){
	
		vcpu_->foreachField([listener](std::shared_ptr<etiss::VirtualStruct::Field> f){f->removeListener(listener);});
	
		delete listener;
	}

    return exception;

}



