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

@date July 28, 2014

@version 0.1

*/
/**
	@file
	
	@brief defines a general interface to set interrupt bits

	@detail 

*/

#ifndef ETISS_INCLUDE_INTERRUPTVECTOR_H_
#define ETISS_INCLUDE_INTERRUPTVECTOR_H_

#include <mutex>
#include <vector>
#include <list>
#include <set>
#include "etiss/jit/types.h"
#include "etiss/Misc.h"

namespace etiss {

	/**
		@brief interface to set interrupt bits
	*/
	class InterruptVector {
	public:
		virtual ~InterruptVector();
		/**
			@brief set the bit of an interrupt line to state (true = raised)
		*/
		virtual void setBit(unsigned bit,bool state) = 0;
		/**
			@brief get the bit of an interrupt line
		*/
		virtual bool getBit(unsigned bit) const = 0;
		/**
			@brief number of interrupt bits
		*/
		virtual unsigned width() const = 0;
		/**
			@return true if any bit is set to true
		*/
		virtual bool isActive() const;
		/**
			@brief sets every bit to false
		*/
		virtual void clear();
		
	};
	
	
	
	template <typename INT>
	/**
		@brief template implementation of an InterruptVector that uses integer variables to store interrupt bit values and to read interrupt masks. this implementaion should work with most cpu architecture implementations.
	*/
	class MappedInterruptVector : public InterruptVector {
	public:
		typedef typename std::vector<INT*> Vector;
		/**
			@brief pass two equally long integer pointer vectors that will be used for interrupt bit vectors and masks
		*/
		MappedInterruptVector(Vector vec,Vector mask) : vector_(vec),mask_(mask){
			if (vector_.size() > mask.size() ){
				vector_.resize(mask.size());
				etiss::log(etiss::ERROR,"MappedInterruptVector: the interrupt and mask vectors must have equal size.");
			}
			if (vector_.size() < mask.size() ){
				mask.resize(vector_.size());
				etiss::log(etiss::ERROR,"MappedInterruptVector: the interrupt and mask vectors must have equal size.");
			}
		}
		virtual ~MappedInterruptVector(){
		
		}
		virtual void setBit(unsigned bit,bool state){
			unsigned o = bit%(sizeof(INT)*8);
			unsigned i = (bit-o)/(sizeof(INT)*8);
			if (i<vector_.size()){
				INT mask = ((INT)1)<<o;
				*vector_[i] = (*vector_[i] & ~mask) | (state ? mask : 0);
			}
		}
		virtual bool getBit(unsigned bit) const{
			unsigned o = bit%(sizeof(INT)*8);
			unsigned i = (bit-o)/(sizeof(INT)*8);
			if (i<vector_.size()){
				return (*vector_[i] &  *mask_[i]) != 0;
			}
			return false;
		}
		virtual unsigned width() const{
			return (unsigned)vector_.size() * sizeof(INT);
		}
		virtual bool isActive() const {
			for (unsigned i = 0;i<vector_.size();i++){
				if ( *vector_[i] & *mask_[i] )
					return true;
			}
			return false;
		}
		virtual void clear() {
			for (unsigned i = 0;i<vector_.size();i++){
				*vector_[i] = (INT)0;
			}
		}
	private:
		Vector vector_;
		Vector mask_;
	};
	
	

}

#endif
