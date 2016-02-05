

#include "cpu_etiss_sc.h" // SystemC <-> ETISS
#include "SimpleMemory.h" // Systemc -> memory

///interrupt and reset module
class DummyInterruptModule : public sc_core::sc_module {
public:
	SC_HAS_PROCESS(DummyInterruptModule);
	DummyInterruptModule(sc_core::sc_module_name name) : sc_core::sc_module(name){
		irq_out_2.bind(irq_sig_2);
		reset_out.bind(reset_sig);
		SC_THREAD(thread);
	}
	sc_out<bool> irq_out_2;
	sc_signal<bool> irq_sig_2;
	sc_out<bool> reset_out;
	sc_signal<bool> reset_sig;
private:
	void thread(){
	/*
		wait(1,SC_NS);
		irq_out_2->write(false);
		wait(11830,SC_NS);
		irq_out_2->write(true);
		wait(100000,SC_NS);
		irq_out_2->write(false);
	*/
		reset_out->write(false);
		wait(23000,SC_NS);
		reset_out->write(true);
		wait(24000,SC_NS);
		reset_out->write(false);	
	}
};


int  sc_main(int argc, char *argv[]){


	etiss::Initializer etiss_init(argc,argv); //initialize etiss. the object must persist as long as etiss is used

	{
		//etiss::loadLibrary("path/to/library","library_name"); //manual loading of libraries if needed

		// create cpu instance
		std::shared_ptr<etiss::CPUCore> core = etiss::CPUCore::create("or1k","core0"); //or1k is the architecture
		if (core == 0){
			return -2;
		}
		
		core->set(etiss::getJIT("LLVMJIT")); //use clang/llvm for the runtime compilation of transated instructions
		
		std::map<std::string,std::string> options;
		options["logaddr"] = "0x80000000"; // start address of the logger
		options["logmask"] = "0xF0000000"; // mask. if a bus access happens and the address & 0xF0000000 equals 0x80000000 then the logger will handle that access
		core->addPlugin(etiss::getPlugin("Logger",options)); // adds a simple logger that prints characted to std::cout to the cpu. the logger will reside inbetween the processor and the systemc interface
		
		// create systemc wrapper around the etiss::CPUCore. from now on anything task related to that cpu (bus,interrupts,reset) is done by this wrapper
		CpuETISSSC or1kcore1_sc(core);

		// create systemc memory backend. simple instruction and data socket that directly access simulated memory (=byte array)
		SimpleMemory sm("Memory");
		
		// connect system to memory
		or1kcore1_sc.data_isock.bind(sm.tsktForCPU_d);
		or1kcore1_sc.instr_isock.bind(sm.tsktForCPU_i);
		
		// load image to memory
		sm.load(0,"code.bin"); // loads the image from the curretn example folder. the image needs the or1k architecture of the etiss::CPUCore.
		
		DummyInterruptModule dim("dim");
		sc_in<bool> * irq_in_2 = or1kcore1_sc.allocateIRQ(2);
		irq_in_2->bind(dim.irq_sig_2);
		sc_in<bool> * reset_in = or1kcore1_sc.allocateReset();
		reset_in->bind(dim.reset_sig);

		sc_start(300000, SC_MS);
                
        
	}
	
         
	etiss::shutdown();
	
	return 0;
}
