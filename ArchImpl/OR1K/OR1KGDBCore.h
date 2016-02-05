#ifndef ETISS_OR1KARCH_OR1KGDBCORE_H_
#define ETISS_OR1KARCH_OR1KGDBCORE_H_

#include "etiss/IntegratedLibrary/gdb/GDBCore.h"
#include "OR1K.h"

class OR1KGDBCore : public etiss::plugin::gdb::GDBCore {
public:
	virtual std::string mapRegister(unsigned index);
	virtual unsigned mapRegister(std::string name);
	virtual unsigned mappedRegisterCount();
	virtual etiss::uint64 getInstructionPointer(ETISS_CPU * cpu);
};

#endif
