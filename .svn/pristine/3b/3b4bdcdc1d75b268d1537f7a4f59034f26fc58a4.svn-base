
INSTALL_TARGET?=

INSTALL_ADDITIONS=$(sort $(dir $(wildcard ArchImpl/*/Install.mk)))
INSTALL_ADDITIONS+=$(sort $(dir $(wildcard JITImpl/*/Install.mk)))



INSTALL_CPY_INCLUDE+=$(wildcard include/*.h)
INSTALL_CPY_INCLUDE+=$(wildcard include/gdb/*.h)

INSTALL_CPY_INCLUDE_C+=$(wildcard include_c/jit/*.h)

.PHONY: all
all: install

.PHONY: $(INSTALL_CPY_INCLUDE)
$(INSTALL_CPY_INCLUDE):
	@mkdir -p $(dir $(INSTALL_TARGET)/$@) && cp -ab $@ $(INSTALL_TARGET)/$@

.PHONY: $(INSTALL_CPY_INCLUDE_C)
$(INSTALL_CPY_INCLUDE_C):
	@mkdir -p $(dir $(INSTALL_TARGET)/$@) && cp -ab $@ $(INSTALL_TARGET)/$@

.PHONY: $(INSTALL_ADDITIONS)
$(INSTALL_ADDITIONS):
	mkdir -p $(INSTALL_TARGET)/$@
	#@if [ -s $(realpath $(INSTALL_TARGET)/$@) ]; then echo Failed to resolve plugin target directory. Please try again.; exit 1; fi
	cd $@ && make -f Install.mk INSTALL_TARGET=$(realpath $(INSTALL_TARGET)/$@) DEBUG=$(DEBUG) OPTLEVEL=$(OPTLEVEL)


.PHONY: install
install: $(INSTALL_CPY_INCLUDE) $(INSTALL_CPY_INCLUDE_C) $(INSTALL_ADDITIONS)
	@cp -ab libETISS.so $(INSTALL_TARGET)/libETISS.so
