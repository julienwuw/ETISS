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

# simple CMakeLists.txt file that can be placed in folders to recurse into subfolders if
# the sub folder contains a CMakeLists.txt

unset(LOCAL_SUBDIRS)
FILE(GLOB LOCAL_SUBDIRS RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/*)
foreach(subdir ${LOCAL_SUBDIRS})
	if(IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${subdir})
		if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/${subdir}/CMakeLists.txt)
			add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/${subdir})
			message(STATUS "Including sub project ${subdir}.")
		else(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${subdir}/CMakeLists.txt)
			message(WARNING "Directory ${subdir} is not added to the current build because it lacks a CMakeLists.txt")
		endif(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${subdir}/CMakeLists.txt)
	endif(IS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/${subdir})
endforeach(subdir ${LOCAL_SUBDIRS})

ETISS_UPDATE_GLOBAL_VARIABLES()


