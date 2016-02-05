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


if(NOT ARMv6M_TEMPLATE_REINCLUDED)

	set(ETISS_PROJECT_NAME ARMv6M)
	set(ETISS_PROJECT_PATH ${CMAKE_CURRENT_LIST_DIR})
	set(${ETISS_PROJECT_NAME}_TEMPLATE_REINCLUDE ${CMAKE_CURRENT_LIST_FILE})

	include(../../CMakeLists.txt.project.template)
	
else(NOT ARMv6M_TEMPLATE_REINCLUDED)

add_custom_command(	OUTPUT "${PROJECT_BINARY_DIR}/ARMv6MIncludedFiles.h" "${PROJECT_BINARY_DIR}/ARMv6MIncludedFiles.cpp" 
			COMMAND IncludedFilesGenerator -fl "include_c/Arch/ARMv6M.h,${ETISS_PROJECT_PATH}/ARMv6M.h" -ns armv6m::storedfiles -h "${PROJECT_BINARY_DIR}/ARMv6MIncludedFiles.h" -cpp "${PROJECT_BINARY_DIR}/ARMv6MIncludedFiles.cpp" -hi "ARMv6MIncludedFiles.h"
			WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
			DEPENDS IncludedFilesGenerator "${ETISS_PROJECT_PATH}/ARMv6M.h"
			COMMENT "Generating code to include some header files for ARMv6M"
			)
set(${ETISS_PROJECT_NAME}_ADDITIONAL_PROJECT_FILES "${PROJECT_BINARY_DIR}/ARMv6MIncludedFiles.cpp" "${PROJECT_BINARY_DIR}/ARMv6MIncludedFiles.h")



endif(NOT ARMv6M_TEMPLATE_REINCLUDED)
