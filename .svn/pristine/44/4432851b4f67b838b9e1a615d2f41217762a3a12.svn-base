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
	
	@brief implementation of etiss/IntegratedLibrary/gdb/Hex.h

	@detail 

*/
#include "etiss/IntegratedLibrary/gdb/Hex.h"

using namespace etiss::plugin::gdb::hex;

uint8_t etiss::plugin::gdb::hex::fromHex(char c){
	if (c <= '9' && c >= '0'){
		return (uint8_t)(c-'0');
	} else if (c <= 'f' && c >= 'a') {
		return (uint8_t)(c-'a'+10);
	} else if (c <= 'F' && c >= 'A'){
		return (uint8_t)(c-'A'+10);
	} else {
		return 16;
	}
}
char etiss::plugin::gdb::hex::toHex(uint8_t l){
	if (l<10){
		return '0' + (char)l;
	} else if (l<16){
		return 'A' + (char)l - 10;
	} else {
		return '?';
	}
}


uint8_t etiss::plugin::gdb::hex::toByte(std::string hex,unsigned pos){
	return toByte(hex[pos],hex[pos+1]);
}
uint8_t etiss::plugin::gdb::hex::toByte(char h,char l){
	return fromHex(h)<<4 | fromHex(l);
}

std::string etiss::plugin::gdb::hex::fromByte(uint8_t byte){
	std::string ret = "  ";
	ret[0] = toHex(byte>>4);
	ret[1] = toHex(byte&0x0F);
	return ret;
}

void etiss::plugin::gdb::hex::fromByte(std::string & append,uint8_t byte){
	append.push_back(toHex(byte>>4));
	append.push_back(toHex(byte&0x0F));
}

std::string etiss::plugin::gdb::hex::fromBytes(uint8_t * buf,unsigned length){
	std::string ret;
	ret.resize(length*2);
	for (unsigned i = 0;i<length;i++){
		ret[i*2] = toHex(buf[i]>>4);
		ret[i*2+1] = toHex(buf[i]&0x0F);
	}
	return ret;
}
