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


if(NOT OR1KArch_TEMPLATE_REINCLUDED)

	set(ETISS_PROJECT_NAME OR1KArch)
	set(ETISS_PROJECT_PATH ${CMAKE_CURRENT_LIST_DIR})
	set(${ETISS_PROJECT_NAME}_TEMPLATE_REINCLUDE ${CMAKE_CURRENT_LIST_FILE})

	include(../../CMakeLists.txt.project.template)
	
else(NOT OR1KArch_TEMPLATE_REINCLUDED)

add_custom_command(	OUTPUT "${PROJECT_BINARY_DIR}/OR1KIncludedFiles.h" "${PROJECT_BINARY_DIR}/OR1KIncludedFiles.cpp" 
			COMMAND IncludedFilesGenerator -fl "include_c/Arch/OR1K/OR1K.h,${ETISS_PROJECT_PATH}/OR1K.h" -ns or1k::storedfiles -h "${PROJECT_BINARY_DIR}/OR1KIncludedFiles.h" -cpp "${PROJECT_BINARY_DIR}/OR1KIncludedFiles.cpp" -hi "OR1KIncludedFiles.h"
			WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
			DEPENDS IncludedFilesGenerator "${ETISS_PROJECT_PATH}/OR1K.h"
			COMMENT "Generating code to include some header files for OR1KArch"
			)
set(${ETISS_PROJECT_NAME}_ADDITIONAL_PROJECT_FILES "${PROJECT_BINARY_DIR}/OR1KIncludedFiles.cpp" "${PROJECT_BINARY_DIR}/OR1KIncludedFiles.h")



endif(NOT OR1KArch_TEMPLATE_REINCLUDED)
