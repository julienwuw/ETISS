
#include "GCCJIT.h"

#include <dlfcn.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <stdlib.h> //mkdtemp

GCCJIT::GCCJIT(bool cleanup) : etiss::JIT("gcc"),cleanup_(cleanup){
	
	id = 0;
	
	if (system(std::string("mkdir -p \"./tmp\"").c_str()))
		std::cerr << "ERROR: GCCJIT failed to create ./tmp folder. this may lead to a failure to compile code." << std::endl;
	
	path_ = "./tmp/XXXXXX";
	// create unique folder (mkdtemp)
	{
		char tmp[strlen(path_.c_str())+1];
		memcpy(tmp,path_.c_str(),strlen(path_.c_str())+1);
		if (mkdtemp(tmp)== 0){
			std::cerr << "ERROR: GCCJIT failed to get unique working folder. Resulting compilations my be unrelyable" << std::endl;
		} else {
			//std::cout << tmp << std::endl;
		}
		path_ = tmp;
		
		if (system(std::string("mkdir -p \""+path_+"\"").c_str())) // make folder if not present
			std::cerr << "ERROR: GCCJIT failed to create compilation path. this may lead to a failure to compile code." << std::endl;
	}
	path_ = path_ + "/";
	
}

GCCJIT::~GCCJIT(){
	if (cleanup_)
		if (path_.substr(0,6) == "./tmp/") // check path before recursive delete operation 
			if (system(std::string("rm -R \""+path_+"\"").c_str()))
				std::cerr << "ERROR: GCCJIT failed to clean up compilation files located in " << path_ << std::endl;
}

void * GCCJIT::translate(std::string code,std::set<std::string> headerpaths,std::set<std::string> librarypaths,std::set<std::string> libraries,std::string & error,bool debug){

	
	if (system(NULL) == 0) {
    		error = "system command execution not available";
		return 0;
	}
	
	unsigned lid = id++;
	
	std::string codefilename;
	{
		std::ofstream codeFile;
		std::stringstream ss;
		ss << "code_" << lid;
		codefilename = ss.str();
		codeFile.open((path_+codefilename+std::string(".c")).c_str());
		if (!codeFile.is_open()){
			error = "failed to create code file";
			return 0;
		}
		codeFile << code;
		codeFile.flush();
		codeFile.close();
	}
	std::stringstream ss;
	ss << "gcc -c -Wall -fPIC -march=native -mtune=native -pipe ";
	if (debug)
		ss << "-g -O0 ";
	else
		ss << "-Ofast ";
	for (std::set<std::string>::const_iterator iter = headerpaths.begin();iter != headerpaths.end();iter++){
		ss << "-I\"" << *iter << "\" ";
	}
	ss << path_ << codefilename << ".c" << " -o "<< path_ << codefilename << ".o";
	
	//std::cout << "EXECUTING: " << ss.str() << std::endl;
	
	int eval = system(ss.str().c_str());
	//std::cout << eval << std::endl;
	
	if (eval != 0){
		std::cout << "compiler failed with code: " << eval << std::endl;
	}
	
	ss.str("");
	
	ss << "gcc -shared ";
	/*
	if (debug)
		ss <<"-g -dl ";
	
	for (std::set<std::string>::const_iterator iter = librarypaths.begin();iter != librarypaths.end();iter++){
		ss << "-L\"" << *iter << "\" ";
	}
	for (std::set<std::string>::const_iterator iter = libraries.begin();iter != libraries.end();iter++){
		ss << "-l\"" << *iter << "\" ";
	}
	*/
	
	ss << "-o " << path_ <<"lib"<<codefilename<<".so "<< path_ <<codefilename<<".o";
	
	//std::cout << "EXECUTING: " << ss.str() << std::endl;
	eval = system(ss.str().c_str());
	//std::cout << eval << std::endl;
	
	if (eval != 0){
		std::cout << "compiler failed with code: " << eval << std::endl;
	}
	
	void * lib = dlopen((path_+"lib"+codefilename+std::string(".so")).c_str(),RTLD_NOW|RTLD_LOCAL);
	
	if (lib == 0){
		error = dlerror();
		return 0;
	}
		
	return lib;
	
	
}
void * GCCJIT::getFunction(void * handle,std::string name,std::string & error){
	void * ret = dlsym(handle,name.c_str());
	if (ret == 0){
		error = dlerror();
		return 0;
	}
	return ret;
}
void GCCJIT::free(void * handle){
	dlclose(handle);
}



