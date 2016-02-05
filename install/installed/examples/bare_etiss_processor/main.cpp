#include "etiss/ETISS.h"

#include "etiss/DebugSystem.h"

int main( int argc, const char* argv[] ) 
{


	// by default etiss wil search for plugin libraries in its install path and relative to the library using the file plugins/list.txt
	etiss::Initializer initializer(argc,argv);
	
	// if a custom library need to be added or etiss failed to find libraries then they can be added manually.
	// the library name must be given without the lib prefix or the .so suffix
	//etiss::loadLibrary("/path/to/library","LibraryName"); 
	
	// if a plugin library is not part of a shared library or the shared library is already loaded then a plugin library can be added like this
	//std::shared_ptr<etiss::LibraryInterface> mylib = std::shared_ptr<etiss::LibraryInterface>(new MyLib());
	//etiss::addLibrary(mylib);

	// create memory device
	etiss::DebugSystem dsys;
	// load image to memory
	if (!dsys.load(0,"../code.bin")){
		etiss::log(etiss::FATALERROR,"could not load image file ../code.bin. please change the path to point to the xample code.bin file.",ETISS_SRCLOC);
	}

	std::map<std::string,std::string> options;

	// create a cpu core named core0 with the or1k architecture
	options.clear();
	std::shared_ptr<etiss::CPUCore> cpu = etiss::CPUCore::create("or1k","core0",options);

	if (!cpu){
		etiss::log(etiss::ERROR,"failed to create cpu core");
		return -1;
	}

	
	// add the virtual structure of the cpu to the VirtualStruct root. 
	//this allows to access the field of the cpu from a global context. 
	//see etiss::VirtualStruct::getVirtualStruct() and etiss::VirtualStruct::getResolvedField().
	// in this case e.g. the instructionPointer can be read from a global context
	// by calling etiss::VirtualStruct::root()->getResolvedField("core0.instructionPointer")->read().
	etiss::VirtualStruct::root()->mountStruct("core0",cpu->getStruct()); 
	
	cpu->set(etiss::getJIT("LLVMJIT")); // use the clang/LLVM based just in time compiler. for debug purposes of generated code use the GCCJIT compiler. a TCC based compiler is also available (TCCJIT)

	// uncomment this if you want the cpu to start from an custom address
	//etiss::uint64 sa = 0;
	//cpu->reset(&sa);

	// uncomment to print each instruction when it is executed
	//options.clear();
	//cpu->addPlugin(etiss::getPlugin("PrintInstruction",options));	// a plugin that prints the instruction and its address when it is executed

	// uncomment to add a debugger plugin. the execution will wait until a debugger is connected
	//options.clear();
	//options["port"] = "2222"; // define port (default: 2222)
	//cpu->addPlugin(etiss::getPlugin("gdbserver",options)); // adds a gdb debug server (connect with "target remote localhost:2222")

	// add a logger. the example software will write some messages with the help pf this logger
	options.clear();
	options["logaddr"] = "0x80000000";
	options["logmask"] = "0xF0000000";
	cpu->addPlugin(etiss::getPlugin("Logger",options));

	int32_t exception = cpu->execute(dsys); // run cpu with the DebugSystem (in other cases that "system" is most likely a bus that connects the cpu to memory,periphery,etc)
	// NOTE: the logger plugin is of the type etiss::SystemWrapperPlugin and will wrap the passed system before it is used by the cpu to be able to redirect reads/writes for the logging address range.

	//print the exception code returned by the cpu core
	std::cerr << "CPU exited with exception: 0x" <<std::hex << exception << std::dec << ": " << etiss::RETURNCODE::getErrorMessages()[exception] << std::endl;

}
