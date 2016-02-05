#ifndef ETISS_PLUGIN_VVLOGGER_H_
#define ETISS_PLUGIN_VVLOGGER_H_

#include "etiss/Plugin.h"

#include <fstream>

namespace etiss
{

namespace plugin
{

/**
	writes the value of a field before each instruction

*/
class VariableValueLogger : public etiss::TranslationPlugin
{
public:

    VariableValueLogger(const std::string & field,const std::string & file,std::function<void(std::ostream & out,const std::string & field,uint64_t value)> writer);
    virtual ~VariableValueLogger();
    virtual void initCodeBlock(etiss::CodeBlock & block)const;
    virtual void finalizeInstrSet(etiss::instr::ModedInstructionSet & ) const;
public:
    void writeValue();
protected:
    virtual std::string _getPluginName() const;
private:
    std::string field_;
    std::function<void(std::ostream & out,const std::string & field,uint64_t value)> writer_;
    std::ofstream out_;
};

}

}

#endif
