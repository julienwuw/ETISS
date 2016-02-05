#include "LLVMJIT.h"
#include "etiss/ETISS.h"

#include <iostream>

using namespace etiss;

using namespace llvm;
using namespace clang;

std::mutex etiss_jit_llvm_init_mu_;
bool etiss_jit_llvm_init_done_ = false;



LLVMLibrary::LLVMLibrary(llvm::LLVMContext  & context,llvm::Module * module) : engine_(0){
	
	if (module != 0){
		// create engine
		engine_ = EngineBuilder(module)
			.setErrorStr(&error_)
			.setUseMCJIT(true)
			.setOptLevel(CodeGenOpt::Aggressive)
			.setRelocationModel(llvm::Reloc::Static)
			.create();
		if (engine_ == 0) {
			std::cout << "ERROR: LLVM: failed to create execution engine: " << error_ << std::endl;
			error_ = "Failed to create execution engine: " + error_;
		} else {
			// "compile" module for access
			engine_->finalizeObject(); 
		}
	} else {
		error_ = "Failed to get module from action";
	}

	
}
LLVMLibrary::~LLVMLibrary(){
	delete engine_;
}

void * LLVMLibrary::getFunction(std::string name,std::string & error){
	if (engine_){
		// get function decalaration
		Function * f = engine_->FindFunctionNamed(name.c_str()); 
		if (f != 0){
			//get function pointer
			void * ret = engine_->getPointerToFunction(f);
			if (ret != 0){
				return ret;
			} else {
				error = "Failed to get function: "+error_;
			}
		} else {
			error = "Failed to find function: "+name;
		}
	} else {
		error = "no llvm execution engine present";
	}
	return 0;
}

LLVMJIT::LLVMJIT() : JIT("LLVMJIT") {
	
	// init environment once
	etiss_jit_llvm_init_mu_.lock();
	if (!etiss_jit_llvm_init_done_) {
		//LLVMInitializeNativeTarget();
		InitializeNativeTarget();
		InitializeNativeTargetAsmPrinter();
		InitializeNativeTargetAsmParser();
		etiss_jit_llvm_init_done_ = true;
	}
	etiss_jit_llvm_init_mu_.unlock();
	
	// create logger
	DiagnosticOptions * diagOpts = new DiagnosticOptions();
	TextDiagnosticPrinter* diagPrinter = new TextDiagnosticPrinter(llvm::outs(), diagOpts);
	clang_.createDiagnostics(diagPrinter);
	
	// configure compiler target
	clang::TargetOptions * pto = new clang::TargetOptions();
	pto->Triple = llvm::sys::getDefaultTargetTriple();
	TargetInfo * pti = TargetInfo::CreateTargetInfo(clang_.getDiagnostics(), pto);
	clang_.setTarget(pti);

	// initialize compiler parts
	clang_.createFileManager();
	clang_.createSourceManager(clang_.getFileManager());
	clang_.createPreprocessor();
	
}

LLVMJIT::~LLVMJIT(){
	
}

void * LLVMJIT::translate(std::string code,std::set<std::string> headerpaths,std::set<std::string> librarypaths,std::set<std::string> libraries,std::string & error,bool debug){
	
	
	
	void* ret = 0;
	
	// diagnostics
	DiagnosticOptions * diagOpts = new DiagnosticOptions();
	TextDiagnosticPrinter * DiagClient = new TextDiagnosticPrinter(llvm::errs(), diagOpts);
	IntrusiveRefCntPtr<DiagnosticIDs> DiagID(new DiagnosticIDs());
	DiagnosticsEngine Diags(DiagID,diagOpts,DiagClient);
	
	
	
	// compilation task
	std::vector<const char*> args;
	std::vector<std::string> args_ref;
	args.push_back("/etiss_llvm_clang_memory_mapped_file.c");
	args.push_back("-O3");
	for (auto iter = headerpaths.begin();iter!=headerpaths.end();iter++){
		args_ref.push_back("-I"+*iter);
		args.push_back(args_ref.back().c_str());
	}

	///TODO: implement method to find/configure standard header path at runtime
#ifdef CLANG_HEADERS
#define CLANG_HEADERS_tostring_(X) #X
#define CLANG_HEADERS_tostring(X) CLANG_HEADERS_tostring_(X)
	args.push_back("-isystem"); // include as system headers to supress warnings
	args_ref.push_back(etiss::cfg().get<std::string>("etiss_wd",CLANG_HEADERS_tostring(CLANG_FALLBACK_PATH))+CLANG_HEADERS_tostring(CLANG_HEADER_REALTIVE_PATH));
	args.push_back(args_ref.back().c_str());
#endif

	// libraries are not needed
	//for (auto iter = librarypaths.begin();iter!=librarypaths.end();iter++){
	//	args_ref.push_back("-L"+*iter);
	//	args.push_back(args_ref.back().c_str());
	//}
	//for (auto iter = libraries.begin();iter!=libraries.end();iter++){
	//	args_ref.push_back("-l"+*iter);
	//	args.push_back(args_ref.back().c_str());
	//}
	//configure compiler call
	CompilerInvocation::CreateFromArgs(clang_.getInvocation(), &args[0], &args[0] + args.size(), Diags);
	// input file is mapped to memory area containing the code
	llvm::MemoryBuffer * buffer = MemoryBuffer::getMemBufferCopy(code,"/etiss_llvm_clang_memory_mapped_file.c");
	clang_.getSourceManager().overrideFileContents(clang_.getFileManager().getVirtualFile("/etiss_llvm_clang_memory_mapped_file.c",buffer->getBufferSize(),0),buffer,true);
	//buffer = MemoryBuffer::getMemBufferCopy(code,"/etiss_llvm_clang_memory_mapped_file.c");
	//clang_.getPreprocessorOpts().addRemappedFile("/etiss_llvm_clang_memory_mapped_file.c", buffer);
	//clang_.createPreprocessor();
	
	
	// compiler should only output llvm module
	EmitLLVMOnlyAction * action = new EmitLLVMOnlyAction();
	
	// compile
	if (!clang_.ExecuteAction(*action)){
		error = "failed to execute translation action ";
		return 0;
	}	
	
	
	// load module with mcjit
	LLVMLibrary * lib = new LLVMLibrary(context_,action->takeModule()); // translfer module ownershif from action to the engine
	
	//TODO: check if lib is valid now not later
	
	ret = (void*)lib;
	
	delete buffer;
	
	return ret;

}
void * LLVMJIT::getFunction(void * handle,std::string name,std::string & error){
	return ((LLVMLibrary*)handle)->getFunction(name,error);
}
void LLVMJIT::free(void * handle){
	delete (LLVMLibrary*) handle;
}






