
#pass this parameter to put the object file into a custom location. e.g.: FAULT_XML_MODULE_BUILD="../build/" -> object files will be in "../build/fault/*.o"
# ATTENTION: folder MUST end with a seperator ( / )
FAULT_XML_MODULE_BUILD?=

FAULT_XML_MODULE_SOURCES=$(wildcard fault/*.cpp) $(wildcard fault/xml/*.cpp)
# use this to include the object files directly without using fault_xml_module.a
FAULT_XML_MODULE_OBJECTS=$(FAULT_XML_MODULE_SOURCES:%.cpp=$(FAULT_XML_MODULE_BUILD)%.o)

fault_xml_module_all: fault_xml_module.a

$(FAULT_XML_MODULE_BUILD)fault/%.o: fault/%.cpp
	mkdir -p $(dir $@)
	gcc -c -MMD -I./ -O2 -g1 -o $@ $<

-include $(FAULT_XML_MODULE_BUILD)fault/*.d
-include $(FAULT_XML_MODULE_BUILD)fault/xml/*.d

fault_xml_module.a: $(FAULT_XML_MODULE_OBJECTS)
	ar rcs fault_xml_module.a $(FAULT_XML_MODULE_OBJECTS)
	
clean:
	rm -f fault/*.o
	rm -f fault/xml/*.o
	rm -f fault/*.d
	rm -f fault/xml/*.d
