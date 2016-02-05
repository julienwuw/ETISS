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

	@brief implements etiss/ReturnCode.h

	@detail

*/
// special define to generate registration functionality of error codes for the maps provided in this file
#define ETISS_RETURNCODE_REGISTRATION_BODY
#include "etiss/jit/ReturnCode.h"


std::map<etiss::int32,const char*> & etiss::RETURNCODE::getErrorMessages(){
	static std::map<etiss::int32,const char*> map;
	return map;
}

std::map<etiss::int32,const char*> & etiss::RETURNCODE::getErrorNames(){
	static std::map<etiss::int32,const char*> map;
	return map;
}

int32_t etiss::RETURNCODE::setTemporary(const std::string & msg){
    static std::mutex mu;
    static std::string msgs[ETISS_RETURNCODE_TEMPORARY_COUNT];
    static int32_t pos = 0;
    std::lock_guard<std::mutex> lock(mu);
    int32_t ret = pos;
    pos = (pos+1)%ETISS_RETURNCODE_TEMPORARY_COUNT;
    msgs[ret] = msg;
    return ret;
}

int32_t etiss_returncode_setTemporary(const char * msg){
    return etiss::RETURNCODE::setTemporary(std::string(msg));
}



