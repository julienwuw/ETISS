#
#	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich
#	
#	The above copyright notice and this permission notice shall be included in
#	all copies or substantial portions of the Software.
#	
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#	THE SOFTWARE.
#	
#	
#	Author: Marc Greim <marc.greim@mytum.de>
#

### recurse into sub directories
unset(LOCAL_SUBDIRS)
FILE(GLOB LOCAL_SUBDIRS ./ *)
foreach(subdir ${LOCAL_SUBDIRS})
	if(IS_DIRECTORY ${subdir})
		add_subdirectory(${subdir})
	endif()
endforeach()


unset(LOCAL_SOURCE)
FILE(GLOB LOCAL_SOURCE *.cpp)

set(ETISS_SOURCE ${ETISS_SOURCE} ${LOCAL_SOURCE} PARENT_SCOPE)
