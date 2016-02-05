
DEBUG?=0
INSTALL_TARGET?=

all: install

libOR1KArch.so:
	make DEBUG=$(DEBUG)

.PHONY: install
install: libOR1KArch.so
	cp -ab libOR1KArch.so $(INSTALL_TARGET)/libOR1LArch.so
	cp -ab OR1K.h $(INSTALL_TARGET)/OR1K.h
