
#include "etiss/JIT.h"

#include "llvm/ExecutionEngine/Interpreter.h" // link interpreter into library (currently not used)
#include "llvm/ExecutionEngine/MCJIT.h" // IMPORTANT link MCJIT into library. if this is not included then the performance will drop by ~50%
#include "clang/CodeGen/CodeGenAction.h" // code generation action "compile to IR" (for mcjit)
#include "clang/Basic/DiagnosticOptions.h" // logging
#include "clang/Frontend/CompilerInstance.h" // compiler
#include "clang/Frontend/CompilerInvocation.h" // compilation run
#include "clang/Frontend/FrontendDiagnostic.h"	// logging
#include "clang/Frontend/TextDiagnosticPrinter.h" //logging
#include "llvm/Support/TargetSelect.h" // target arch
#include "llvm/Support/raw_ostream.h" // logging
#include "llvm/ADT/SmallString.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h" // interface to MCJIT
//#include "llvm/ExecutionEngine/JIT.h" // old execution engine (performance drop ~50 to MCJIT)
#include "llvm/IR/Module.h" // compiled code container
#include "llvm/IR/LLVMContext.h" 
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <clang/CodeGen/CodeGenAction.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/CompilerInvocation.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <llvm/ADT/IntrusiveRefCntPtr.h>
#include <llvm/ADT/OwningPtr.h>
#include "llvm/Support/Host.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/Scalar.h"
#include <cctype>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <mutex>


namespace etiss {

	/**
		@brief contains compiled code from LLVMJIT::translate and a execution engine
	*/
	class LLVMLibrary {
	public:
		LLVMLibrary(llvm::LLVMContext  & context,llvm::Module * module);
		~LLVMLibrary();
		/**
			@brief lookup function name; NOTE: functions only NOT symbols
		*/
		void * getFunction(std::string name,std::string & error);
	private:
		llvm::ExecutionEngine * engine_;
		std::string error_;
	};

	class LLVMJIT : public etiss::JIT{
	public:
		LLVMJIT();
		virtual ~LLVMJIT();
		virtual void * translate(std::string code,std::set<std::string> headerpaths,std::set<std::string> librarypaths,std::set<std::string> libraries,std::string & error,bool debug = false);
		virtual void * getFunction(void * handle,std::string name,std::string & error);
		virtual void free(void * handle);
	private:
		llvm::LLVMContext context_;
		clang::CompilerInstance clang_;
	};
	
	

}

