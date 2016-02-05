

#include "SystemCBridge.h" // SystemC <-> ETISS
#include "SimpleMemory.h" // Systemc -> memory

#include "etiss/ETISS.h" // ISS


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

	std::vector<std::string> vargs;
	for (int i = 0;i<argc;i++){
		vargs.push_back(argv[i]);
	}
	
	etiss::initialize(vargs);

	{

		// create cpu instance
		std::shared_ptr<etiss::CPUCore> cpu = etiss::CPUCore::create("or1k","core0");
		if (cpu == 0){
			return -2;
		}
		
		cpu->set(etiss::getJIT("LLVMJIT"));
	
		// create systemc interface
		SystemCBridge cpubridge("ETISS",32,cpu);

		// create systemc memory backend
		SimpleMemory sm("Memory");
		
		// connect system to memory
		cpubridge.d_bus.bind(sm.tsktForCPU_d);
		cpubridge.i_bus.bind(sm.tsktForCPU_i);
		
		// load image to memory
		sm.load(0,"../SW/code.bin");
		
		DummyInterruptModule dim("dim");
		sc_in<bool> * irq_in_2 = cpubridge.allocateIRQ(2);
		irq_in_2->bind(dim.irq_sig_2);
		sc_in<bool> * reset_in = cpubridge.allocateReset();
		reset_in->bind(dim.reset_sig);

		sc_start(300000, SC_MS);
                
        
	}
	
         
	etiss::shutdown();
	
	return 0;
}
