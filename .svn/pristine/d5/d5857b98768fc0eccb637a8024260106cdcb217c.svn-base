#################################################################################################
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
#	author Marc Greim <marc.greim@mytum.de>
#
#	date June 24, 2014
#
#	version 0.1
#
#	This makefile include contains code to check prerequisites for building or 
#	executing ETISS. Configuration detection should be done in this file too
#
###############################################################################################



python_version_full := $(wordlist 2,4,$(subst ., ,$(shell python -V 2>&1)))
python_version_major := $(word 1,${python_version_full})
python_version_minor := $(word 2,${python_version_full})
python_version_patch := $(word 3,${python_version_full})

TARGET_CHECK_BUILD+= script/etiss/cpplint.py 

ifneq ($(ETISS_USE_PYTHON),0)
	TARGET_CHECK_BUILD+= build/se_check_python
endif

Prerequisites_all: all

build/se_check_python:
	mkdir -p build
	touch build/se_check_python
	@if [ ${python_version_major} -eq 2 ] ; then \
		if [ ${python_version_minor} -lt 7 ] ; then \
			echo "ERORR: wrong python version. Upgrade to version 2.7"; \
			exit 1;\
		elif [ ${python_version_minor} -gt 7 ] ; then \
			echo "NOTE: phyton scripts have only been tested with python version 2.7";\
		fi \
	elif [ ${python_version_major} -gt 2 ] ; then \
		echo "NOTE: phyton scripts have only been tested with python version 2.7";\
	elif [ ${python_version_major} -lt 2 ] ; then \
		echo "ERORR: wrong python version. Upgrade to version 2.7"; \
		exit 1;\
	fi


script/etiss/cpplint.py:
	-mkdir -p script/etiss/
	-cd script/etiss/ && wget http://google-styleguide.googlecode.com/svn/trunk/cpplint/cpplint.py


