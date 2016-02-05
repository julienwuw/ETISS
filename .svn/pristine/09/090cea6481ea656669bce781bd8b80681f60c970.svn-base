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
#ifndef ETISS_INTERFACES_WISHBONE_H
#define ETISS_INTERFACES_WISHBONE_H

#include "etiss/interfaces/Delegate.h"

#include <utility>

namespace etiss
{
namespace interfaces
{

template<typename T>
/**
	simple helper struct to trigger static_assert only if the template is instantiated
*/
struct dependent_false: std::false_type {};

template<typename Type>
struct Foo {

};

template <typename BOOLSIG>
/**
	general helper function to read a signal; needs to be implemented as needed
*/
bool getBool(BOOLSIG & sig){
	static_assert( dependent_false<BOOLSIG>::value , "etiss::interfaces::getBool needs to be specialized" );
	return false; // never remove static_assert above!
}

template <typename BOOLSIG>
/**
	general helper function to set a signal; needs to be implemented as needed
*/
void setBool(BOOLSIG & sig,bool val){
	static_assert( dependent_false<BOOLSIG>::value , "etiss::interfaces::setBool needs to be specialized" );
}

template <typename VECTORSIG>
/**
	general helper function to read an address; needs to be implemented as needed
*/
uint64_t getAddr(VECTORSIG & sig){
	static_assert( dependent_false<VECTORSIG>::value , "etiss::interfaces::getAddr needs to be specialized" );
	return 0; // never remove static_assert above!
}


template <typename VECTORSIGSTORAGETYPE,typename VECTORSIG>
/**
	general helper function to read a signal; needs to be implemented as needed
*/
VECTORSIGSTORAGETYPE getData(VECTORSIG & sig){
	static_assert( dependent_false<VECTORSIG>::value , "etiss::interfaces::getData needs to be specialized" );
	return 0; // never remove static_assert above!
}

template <typename VECTORSIGSTORAGETYPE,typename VECTORSIG>
/**
	general helper function to set a signal; needs to be implemented as needed
*/
void setData(VECTORSIG & sig,VECTORSIGSTORAGETYPE val){
	static_assert( dependent_false<VECTORSIG>::value , "etiss::interfaces::setData needs to be specialized" );
}

template <typename SELSIG>
uint32_t getSel(SELSIG & sel_i){
	static_assert( dependent_false<SELSIG>::value , "etiss::interfaces::getSelData needs to be specialized" );
	return 0;
}



template <typename BOOLSIG,typename VECTORSIG>
class WishboneSignalMap
{
public:
    BOOLSIG& clk_i;
    BOOLSIG& ack_o;
    BOOLSIG& err_o;
    BOOLSIG& rty_o;
    BOOLSIG& cyc_i;
    BOOLSIG& stb_i;
    BOOLSIG& we_i;
    BOOLSIG& sel_i;
    BOOLSIG& bte_i;
    BOOLSIG& cti_i;
    VECTORSIG& dat_o;
    VECTORSIG& adr_i;
    VECTORSIG& dat_i;
public:
    WishboneSignalMap (
        BOOLSIG& clk_o,
        BOOLSIG& ack_i,
        BOOLSIG& err_i,
        BOOLSIG& rty_i,
        BOOLSIG& cyc_o,
        BOOLSIG& stb_o,
        BOOLSIG& we_o,
        BOOLSIG& sel_o,
        BOOLSIG& bte_o,
        BOOLSIG& cti_o,
        VECTORSIG& dat_i,
        VECTORSIG& adr_o,
        VECTORSIG& dat_o
    ) :
        clk_i(clk_o),
        ack_o(ack_i),
        err_o(err_i),
        rty_o(rty_i),
        cyc_i(cyc_o),
        stb_i(stb_o),
        we_i(we_o),
        sel_i(sel_o),
        bte_i(bte_o),
        cti_i(cti_o),
        dat_o(dat_i),
        adr_i(adr_o),
        dat_i(dat_o)
    {
    }

};

template <typename T,unsigned bytes,bool swap>
bool sel_i_range(T sel_i,unsigned & start,unsigned & len,unsigned & addroff){
    start = 0;
    len = 0;
    while ((sel_i&1) == 0){
        start++;
        sel_i >>= 1;
    }
    while ((sel_i&1) == 1){
        len++;
        sel_i >>= 1;
    }
    if (swap)
        start = bytes-start-len;
    addroff = 0;

    return sel_i == 0;


}

template <typename BOOLSIG,typename VECTORSIG,bool instrBus,bool flipEndianess,unsigned bytewidth = sizeof(VECTORSIG),typename VECTORSIGSTORAGETYPE = VECTORSIG>
/**
	connects a wishbone bus interface implemented with the variables of WishboneSignalMap to a ETISS_System structure. the template parameter instrBus defined is the iread/iwrite or dread/dwrite functions are used (-> instruction bus or data bus)
*/
class WishboneBus : public Delegate
{
    static_assert(bytewidth == sizeof(VECTORSIGSTORAGETYPE),"bytewidht != sizeof(VECTORSIGSTORAGETYPE)");
private:
    inline void handleEndianness(uint8_t * buf)
    {
        if (flipEndianess)
        {
            for (unsigned i = 0; i<(bytewidth>>1); ++i)
            {
                std::swap(buf[i],buf[bytewidth-1-i]);
            }
        }
    }
private:
    uint64_t lastutime;
    bool lastclock;
    bool useposclkedge;
    uint64_t etime;
    VECTORSIGSTORAGETYPE dat_o;
    bool po_err;
    unsigned pending;
public:
    WishboneSignalMap<BOOLSIG,VECTORSIG> & sigs;
    WishboneBus(WishboneSignalMap<BOOLSIG,VECTORSIG> & sigs,ETISS_System & system,ETISS_CPU & cpu) : Delegate(system,cpu), lastutime(0),lastclock(false),useposclkedge(true),etime(0),dat_o(0),po_err(false),pending(0),sigs(sigs) {}
    void init()
    {
        sigs.ack_o = false;
        sigs.err_o = false;
        sigs.rty_o = false;
        sigs.dat_o = 0;
        pending = 0;
    }
    void update(uint64_t time,bool premain,bool reset)
    {
        if (time <= lastutime && !time==0) // safeguard
            return;
        if (!premain) // store last update time
            lastutime = time;

        bool clkedge = (((bool)lastclock)!=(getBool(sigs.clk_i))) && ((getBool(sigs.clk_i))==((bool)useposclkedge)); // detect clock edge
        //bool falseclkedge = (((bool)lastclock)!=(getBool(sigs.clk_i))) && ((getBool(sigs.clk_i))!=((bool)useposclkedge)); // detect opposite clock edge

        if (!premain)	// store last clock edge
            lastclock = getBool(sigs.clk_i);

        if (reset)   // reset
        {
            init();
        }
        else
        {
            if (premain)  // apply pending signal changes
            {
                if (pending != 0)    // signal changes to apply?
                {
                	if (time >= etime){ // event ready?
						switch (pending){
						case 1: // read
							setBool(sigs.ack_o,!po_err);
							setBool(sigs.err_o,po_err);
							setBool(sigs.rty_o, false);
							if (!po_err)
								setData<VECTORSIGSTORAGETYPE,VECTORSIG>(sigs.dat_o,dat_o);
							break;
						case 2: //write
							sigs.ack_o = !po_err;
							sigs.err_o = po_err;
							break;
						default:
							etiss_log(FATALERROR,"variable \"pending\" has an invalid value");
						}
						if (clkedge)
							pending = 0; // clear event
                	}
                }
                else if (clkedge)
                {
                    setBool(sigs.ack_o,false);
                    setBool(sigs.err_o,false);
                    setBool(sigs.rty_o, false);
                    setData<VECTORSIGSTORAGETYPE,VECTORSIG>(sigs.dat_o,0);
                }
            }
            else     // reevaluate signals
            {
                if (clkedge && (pending==0))
                {
                	{ // immediate reset of signals
						setBool(sigs.ack_o,false);
						setBool(sigs.err_o,false);
						setBool(sigs.rty_o, false);
                	}
                    setData<VECTORSIGSTORAGETYPE,VECTORSIG>(sigs.dat_o,0);
                    if (getBool(sigs.cyc_i) && getBool(sigs.stb_i))
                    {
                        uint64_t addr = getAddr(sigs.adr_i);
                        VECTORSIGSTORAGETYPE buf = 0;
                        uint64_t ltime = time;
                        unsigned soff,slen,aoff;
                        if (getBool(sigs.we_i))  // write
                        {
                            if (!sel_i_range<uint8_t,4,flipEndianess>(getSel(sigs.sel_i),soff,slen,aoff))
                                std::cout << "invalid sel_i: " << +getSel(sigs.sel_i) << " we_i: " << getBool(sigs.we_i) << std::endl;
                            buf = getData<VECTORSIGSTORAGETYPE,VECTORSIG>(sigs.dat_i);
                            if (flipEndianess && slen < bytewidth)
                                buf = buf << (slen*8); // move bits to right position before flipping
                            handleEndianness((uint8_t*)&buf);
                            po_err = !write(instrBus,ltime,addr+aoff,((uint8_t*)&buf)+soff,slen);
                            pending = 2;
                        }
                        else     // read
                        {
                            if (!sel_i_range<uint8_t,4,flipEndianess>(getSel(sigs.sel_i),soff,slen,aoff))
                                std::cout << "invalid sel_i: " << +getSel(sigs.sel_i) << " we_i: " << getBool(sigs.we_i) << std::endl;
                            //if (sigs.sel_i.val!=0xF)
                                //std::cout << "sel_i: " << +sigs.sel_i.val << " addr: " << std::hex << addr << " addr real: " << std::hex << addr+aoff << std::endl;
                            po_err = !read(instrBus,ltime,addr+aoff,((uint8_t*)&buf)+soff,slen);
                            handleEndianness((uint8_t*)&buf);
                            dat_o = buf; // store but don't provide result
                            pending = 1;
                        }
                        etime = ltime; // store event time
                    }
                }
            }
        }
    }
private:


};



} // namespace interfaces
} // namespace etiss

#endif // ETISS_INTERFACES_WISHBONE_H


