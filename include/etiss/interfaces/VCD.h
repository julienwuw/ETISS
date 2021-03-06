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

@date November 21, 2014

@version 0.4

*/
/**
	@file

	@brief

	@detail

*/
#ifndef ETISS_INTERFACES_VCD_H
#define ETISS_INTERFACES_VCD_H

#include "etiss/Misc.h"

#include <iostream>
#include <fstream>
#include <vector>



/**
	macro to add a TraceableField to a VCD instance.
	@attention only works with TraceableField variables
	e.g.
	etiss::interfaces::VCD cpuLog("cpu.vcd");
	TraceableField<int> var;
	ETISS_INTERFACES_VCD_DECLARE(cpuLog,var)

	in above example the output wire will be named "var"
*/
#define ETISS_INTERFACES_VCD_DECLARE(LOG,VAR,WIDTH) { (VAR).vcd = & (LOG); (LOG).declare((VAR),ETISS_TOSTRING(VAR),WIDTH,(VAR).errval); }


namespace etiss
{
namespace interfaces
{

/**
	@attention this class streams the output to a file. the update() function may therfore only be called with equal or increasing time values
*/
class VCD : public etiss::ToString
{
public:
    class Signal
    {
    public:
        inline Signal() : valid(false) {}
        std::string name;
        //std::string module;
        bool valid;
        uint64_t value;
        unsigned width;
        std::string ident;
        uint64_t undefined;
    };
    etiss_del_como(VCD)

    VCD(const std::string & file,const std::string & comment = std::string());
    virtual ~VCD();

    template <typename T>
    inline bool declare(T & variable,const std::string & name,unsigned width,uint64_t initialvalue,uint64_t undefined = -1)
    {
        return declare((void*) & variable,name,width,initialvalue,undefined);
    }

    template <typename T>
    inline void update(double time_s,const T & variable,uint64_t value,uint64_t undefined = 0)
    {
        update((uint64_t)(time_s*1000000000000.0),(void*) & variable,value,undefined);
    }

    inline std::string toString() const
    {
        return std::string("VCD { file=\"") + file + "\"}";
    }

    void close();

protected:
    bool declare(void * variable,const std::string & name,unsigned width,uint64_t initialvalue,uint64_t undefined);
    void update(uint64_t time_ps,void * variable,uint64_t value,uint64_t undefined);
    void flush();
private:
    std::ofstream out_;
    bool valid_;
    bool dumpstarted_;
    std::vector<Signal> sigs_;
    uint64_t lasttime_ps;
    std::map<void*,int> ptr2index_; ///TODO replace with better lookup
    std::string dumpvar;
    std::string file;
};

} // namespace interfaces
} // namespace etiss

#endif // ETISS_INTERFACES_VCD_H
