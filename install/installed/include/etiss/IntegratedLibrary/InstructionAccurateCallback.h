#ifndef ETISS_PLUGIN_InstructionAccurateCallback_H_
#define ETISS_PLUGIN_InstructionAccurateCallback_H_

#include "etiss/Plugin.h"

#include <fstream>

namespace etiss
{

namespace plugin
{

/**
	writes the value of a field before each instruction

*/
class InstructionAccurateCallback : public etiss::TranslationPlugin
{
public:

    InstructionAccurateCallback();
    virtual ~InstructionAccurateCallback();
    virtual void initCodeBlock(etiss::CodeBlock & block)const;
    virtual void finalizeInstrSet(etiss::instr::ModedInstructionSet & ) const;
protected:
    virtual std::string _getPluginName() const;
public:
	void call();
};

}

}

#endif
