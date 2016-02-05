# Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich
# 
# 	The above copyright notice and this permission notice shall be included in
# 	all copies or substantial portions of the Software.
# 
# 	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# 	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# 	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# 	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# 	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# 	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# 	THE SOFTWARE.

LIBS__=$(wildcard lib/lib*.so)

LIBS__+=$(wildcard ArchImpl/*/lib*.so)

LIBS__+=$(wildcard JITImpl/*/lib*.so)

LIBS__+=$(wildcard PluginImpl/*/lib*.so)

LIBS__=$(wildcard .//lib/lib*.so)

LIBS__+=$(wildcard .//ArchImpl/*/lib*.so)

LIBS__+=$(wildcard .//JITImpl/*/lib*.so)

LIBS__+=$(wildcard .//PluginImpl/*/lib*.so)

LIBS__+=$(foreach dir,$(PATH::= ),$(wildcard $(dir)/ArchImpl/*/lib*.so))

LIBS__+=$(foreach dir,$(PATH::= ),$(wildcard $(dir)/JITImpl/*/lib*.so))

LIBS__+=$(foreach dir,$(PATH::= ),$(wildcard $(dir)/PluginImpl/*/lib*.so))

LIBS__+=$(foreach dir,$(PATH::= ),$(wildcard $(dir)/ETISS/lib/lib*.so))

LIBS=$(sort $(LIBS__))

.PHONY: all
all: printlibs

.PHONY: $(LIBS)
$(LIBS):
	@echo $(patsubst lib%.so,%,$(notdir $@)),$(realpath $(dir $@)),$(patsubst lib%.so,%,$(notdir $@)) #write library name 2 times for output verification

.PHONY: printlibs
printlibs: $(LIBS)

