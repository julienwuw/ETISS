
#include "OR1KGDBCore.h"

#include <sstream>

std::string OR1KGDBCore::mapRegister(unsigned index){
	if (index < 32){
		std::stringstream ss;
		ss << "R" << index;
		return ss.str();
	}
	switch (index){
	case 32:
		return "PPC";
	case 33:
		return "NPC";
	case 34:
		return "SR";
	}
	return "";
}
unsigned OR1KGDBCore::mapRegister(std::string name){
	return INVALIDMAPPING;
}
unsigned OR1KGDBCore::mappedRegisterCount(){
	return 35;
}
etiss::uint64 OR1KGDBCore::getInstructionPointer(ETISS_CPU * cpu){
	return (*((OR1K*)cpu)->NPC)>>2;
}
