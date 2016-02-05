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

@date September 2, 2014

@version 0.1

*/
/**
	@file
	
	@brief provides a fast memory implementation for ETISS	
	
*/

#include <memory>
#include "etiss/jit/System.h"

namespace etiss {

	/**
		creates a very fast ETISS_System structure. 
		segmentation faults are possible if the read access happens outside of the range 0 to size-1.
		writing to areas that have been translated results in undefined behaviour.
		instruction write access return etiss::RETURNCODE::IBUS_WRITE_ERROR.
		time synchronization is disabled but may be changed if a custom handle is not required;
	*/
	std::shared_ptr<ETISS_System> createFastMemory(size_t size);


}
