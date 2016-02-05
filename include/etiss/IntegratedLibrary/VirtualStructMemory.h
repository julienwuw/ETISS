#ifndef ETISS_PLUGIN_VIRTUALSTRUCTMEMORY_H
#define ETISS_PLUGIN_VIRTUALSTRUCTMEMORY_H

#include "etiss/VirtualStruct.h"
#include "etiss/System.h"

namespace etiss
{
namespace plugin
{

/**
	allows to read/write to a virtual structure as if it is a memory. Any mapped field is addressed as little endian.
*/
class VirtualStructMemory : public SimpleSystem
{
public:
    VirtualStructMemory(const etiss::VirtualStruct & str,std::function<uint64_t(etiss::VirtualStruct::Field *,bool & /*dontMount*/)> mountPoint,bool littleendian = true);
    virtual ~VirtualStructMemory();

    /**
    	@attention all mapped fields are addressed as little endian
    */
    virtual bool read(bool debug,ETISS_CPU * cpu,etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);
    /**
    	@attention all mapped fields are addressed as little endian
    */
    virtual bool write(bool debug,ETISS_CPU * cpu,etiss::uint64 addr,etiss::uint8 * buf,etiss::uint32 len);

    const etiss::VirtualStruct & mem_;

    /**
    	returns the internal mapping
    */
    inline const std::map<uint64_t,std::pair<etiss::VirtualStruct::Field * /*field*/,unsigned /*offset*/> > & getMapping()
    {
        return memmap_;
    }
    std::set<etiss::VirtualStruct::Field * > getMappedFields();

    inline uint64_t startAddr() {return startaddr_;}
    inline uint64_t endAddr() {return endaddr_;}

protected:
private:
    uint64_t startaddr_;
    /// excluded
    uint64_t endaddr_;
    std::map<uint64_t,std::pair<etiss::VirtualStruct::Field * /*field*/,unsigned /*offset*/> > memmap_;
    std::list<std::shared_ptr<VirtualStruct::Field> > references;
};

} // namespace plugin
} // namespace etiss

#endif // ETISS_PLUGIN_VIRTUALSTRUCTMEMORY_H
