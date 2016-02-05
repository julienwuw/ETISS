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

set(ETISS_INCLUDE_DIRS "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/include" "")
if(NOT OFF)
set(ETISS_LIBRARIES "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/lib/libETISS.so")
endif()

if (NOT ETISS_DISABLE_COMPILERFLAGS)
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" ETISS_USE_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" ETISS_USE_CXX0X)
	if(ETISS_USE_CXX11)
		set(C_ETISS_USE_CXX11 1)
		set(C_ETISS_USE_CXX0X 1)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
		message("ETISS added the -std=c++11 option to CMAKE_CXX_FLAGS. this can be disabled by setting ETISS_DISABLE_COMPILERFLAGS to ON")
	elseif(ETISS_USE_CXX0X)
		set(C_ETISS_USE_CXX11 0)
		set(C_ETISS_USE_CXX0X 1)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
		message("ETISS added the -std=c++0x option to CMAKE_CXX_FLAGS. this can be disabled by setting ETISS_DISABLE_COMPILERFLAGS to ON")
	else()
		set(C_ETISS_USE_CXX11 0)
		set(C_ETISS_USE_CXX0X 0)
		message(WARNING "The compiler ${CMAKE_CXX_COMPILER} doesn't support the --std==c++11 / --std=c++0x otions. ETISS requires at least C++0x as implemented by gcc 4.6. Please ensure that the compiler is up to the task.")
	endif()
endif()

file(GLOB_RECURSE SUBPROJECTS_CMAKE "/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/installed/cmake/*.cmake")
string(REGEX REPLACE "[^;]ETISSConfig.cmake;?" "" SUBPROJECTS_CMAKE "${SUBPROJECTS_CMAKE}")
string(REGEX REPLACE "[^;]*ConfigVersion.cmake;?" "" SUBPROJECTS_CMAKE "${SUBPROJECTS_CMAKE}")
foreach(sp ${SUBPROJECTS_CMAKE})
	include(${sp})
endforeach(sp ${SUBPROJECTS_CMAKE})

set(ETISS_SOURCES ${ETISS_SOURCES} "")
set(ETISS_LIBRARIES ${ETISS_LIBRARIES} "pthread;dl;/nfs/TUEIEDAprojects/SystemDesign/work/virtualprototyping/YurunWu/etiss/0.4.3_lite_CortexM0/install/JITImpl/TCC/tcc_unix/build/libtcc.a")

