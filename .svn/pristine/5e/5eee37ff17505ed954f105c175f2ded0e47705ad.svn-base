/**

@copyright
<pre>


	Copyright (c) 2014 Institute for Electronic Design Automation, TU Munich

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.


</pre>
@author Marc Greim <marc.greim@mytum.de>

@date December 19, 2014

@version 0.4

*/
/**
	@file

	@brief implements a code generator to include files as arrays


*/

#include <iostream>
#include <list>
#include <string>
#include <fstream>

static bool equalFileContent(const std::string & file1,const std::string & file2){

    std::ifstream in1,in2;
    in1.open(file1);
    if (!in1.is_open())
        return false;
    in2.open(file2);
    if (!in2.is_open()){
        in1.close();
        return false;
    }


    bool ret = std::equal(std::istreambuf_iterator<char>(in1), std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(in2));

    in1.close();
    in2.close();

    return ret;

}

static bool copyFile(const std::string & from,const std::string & to){
    std::ifstream source(from.c_str(), std::ios::binary);
    if (!source.is_open())
        return false;
    std::ofstream dest(to.c_str(), std::ios::binary);
    if (!dest.is_open()){
        source.close();
        return false;
    }

    std::istreambuf_iterator<char> begin_source(source);
    std::istreambuf_iterator<char> end_source;
    std::ostreambuf_iterator<char> begin_dest(dest);
    std::copy(begin_source, end_source, begin_dest);

    source.close();
    dest.close();
    return true;
}

static std::list<std::string> split(const std::string & s,const std::string & sep){

	std::list<std::string> ret;

	size_t oldpos = 0;
	size_t pos;
	do {
		pos = s.find(sep,oldpos);
		ret.push_back(s.substr(oldpos,(pos==std::string::npos)?(pos):(pos-oldpos)));
		oldpos = pos+sep.size();

	} while (pos != std::string::npos);
	return ret;
}

static std::list<std::pair<std::string,std::string> > splitCMake(const std::string & str){
	std::list<std::string> l1 = split(str,";");
	std::list<std::pair<std::string,std::string> > l2;
	for (std::list<std::string>::iterator iter = l1.begin();iter != l1.end();++iter){
		std::list<std::string> tmp = split(*iter,",");
		if (tmp.size() == 2){
			l2.push_back(std::make_pair(*tmp.begin(),*++tmp.begin()));
		} else if (tmp.size() == 1){
			l2.push_back(std::make_pair(*tmp.begin(),*tmp.begin()));
		} else {
			std::cerr << "invalid string from cmake: " << *iter << std::endl;
		}
	}
	return l2;
}

static char tohex[] =
{
	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'A',
	'B',
	'C',
	'D',
	'E',
	'F'
};

#define ETISS_DO_CHAR_CAST 1
/**

*/
static size_t writeData(std::ostream & out,std::istream & in){
    //TODO in case of a string in a file it would be better to write an escaped c string
	char c = 0;
	char buf[12];
	buf[0] = '(';
	buf[1] = 'c';
	buf[2] = 'h';
	buf[3] = 'a';
	buf[4] = 'r';
	buf[5] = ')';
	buf[6] = '0';
	buf[7] = 'x';
	buf[10] = ',';
	buf[11] = 0;
	size_t size = 0;
	while (in.get(c)){
		buf[8] = tohex[(c>>4)&0x0F];
		buf[9] = tohex[c&0x0F];
#if ETISS_DO_CHAR_CAST
        	out << buf;
#else
		out << &buf[6];
#endif
		size++;
	}
	out << "(char)0x00";
	return size;
}


int main(int argc ,char** argv){

	std::list<std::pair<std::string,std::string> > includedFiles;

	std::string outputFile_cpp;
	std::string destFile_cpp;
	std::string outputFile_h;
	std::string destFile_h;
	std::string outputFile_h_include;
	std::string outputFile_inclist;

	std::list<std::string> namespaces;
	std::string count = "count";
	std::string dataarray = "data";
	std::string namearray = "names";
	std::string sizearray = "datalen";


	for (int i = 0;i<argc;++i){
		std::string arg = argv[i];
		if (arg == "-fl"){ // file list
			if ((++i)<argc){
				std::list<std::pair<std::string,std::string> > files = splitCMake(argv[i]);
				includedFiles.insert(includedFiles.end(),files.begin(),files.end());
				std::cout << "INFO: including files: " << argv[i] << std::endl;
			} else {
				std::cerr << "no file list (filename1,filepath1;...;filenameN,filepathN) provided for -fl" << std::endl;
			}
		}
		if (arg == "-ns"){ // namespace list
			if ((++i)<argc){
				std::list<std::string> ns = split(argv[i],"::");
				namespaces.insert(namespaces.end(),ns.begin(),ns.end());
			} else {
				std::cerr << "expected namespace (namespace1::...::namespaceN) after -ns" << std::endl;
			}
		}
		if (arg == "-cpp"){ // cpp file
			if ((++i)<argc){
				destFile_cpp = argv[i];
			} else {
				std::cerr << "expected target cpp file name after -cpp" << std::endl;
			}
		}
		if (arg == "-h"){ // header file
			if ((++i)<argc){
				destFile_h = argv[i];
				outputFile_h_include = argv[i];
			} else {
				std::cerr << "expected target header file name after -h" << std::endl;
			}
		}
		if (arg == "-hi"){ // header include string for cpp file
			if ((++i)<argc){
				outputFile_h_include = argv[i];
			} else {
				std::cerr << "expected header include file name for the cpp file after -hi" << std::endl;
			}
		}
		if (arg == "-li"){ //
			if ((++i)<argc){
				outputFile_inclist = argv[i];
			} else {
				std::cerr << "expected target file to print included files after -li" << std::endl;
			}
		}
		if (arg =="--help"){
			std::cout << 	"IncludedFilesGenerator\nCopyright (c) 2014-2015 Institute for Electronic Design Automation, TU Munich\n\n"
				<<	"Arguments: "
				<< 	"\t-fl <list of files>			the files to include. an file entry must be of the form <stored file path>,<filepath> . multiple entries are seperated by a \";\". e.g. include_c/etiss/jit/types.h,~/ETISS/trunk/include_c/etiss/jit/types.h;include_c/etiss/jit/cpu.h,~/ETISS/trunk/include_c/etiss/jit/cpu.h\n"
				<<	"\t-ns <full namespace prefix>	namespace of the variables. e.g. my::name::space\n"
				<<	"\t-cpp <filepath>				output file name of the generated cpp file\n"
				<<	"\t-h <filepath>				output file name of the generated header file\n"
				<<	"\t-hi <relative path>			the include string for the cpp file to include the header with th right path.e.g. -hi include/GenHeader.h  -> #include \"include/GenHeader.h\"\n"
				<<	"\t-li <filepath> 				write a file that lists all included files\n";
		}
	}

	outputFile_h = destFile_h + ".tmp";
    outputFile_cpp = destFile_cpp + ".tmp";

	// write header
	{
		std::ofstream out;
		out.open(outputFile_h.c_str());

		out << "#include <cstddef>\n"; // for size_t type

		if (!out.is_open()){
			std::cerr << "ERROR: could not open file " << outputFile_h << std::endl;
			return -2;
		}

		for (std::list<std::string>::iterator iter = namespaces.begin();iter != namespaces.end();++iter){
			out << "namespace " << *iter << " {\n";
		}

		out << "extern const size_t " << count << ";\n";
		out << "extern const size_t " << sizearray << "[];\n";
		out << "extern const char * const " << dataarray << "[];\n";
		out << "extern const char * const " << namearray << "[];\n";

		for (std::list<std::string>::iterator iter = namespaces.begin();iter != namespaces.end();++iter){
			out << "} //" << *iter <<"\n";
		}

		out.flush();
		out.close();
	}

	// write body

	{
		std::ofstream liout;
		if (!outputFile_inclist.empty()){
			liout.open(outputFile_inclist.c_str());
			if (!liout.is_open()){
				std::cerr << "ERROR: could not write to file " << outputFile_inclist << std::endl;
			}
		}
		std::ofstream out;
		out.open(outputFile_cpp.c_str());

		if (!out.is_open()){
			std::cerr << "ERROR: could not open file " << outputFile_h << std::endl;
			return -1;
		}

		out << "#include \"" << outputFile_h_include << "\"\n";

		for (std::list<std::string>::iterator iter = namespaces.begin();iter != namespaces.end();++iter){
			out << "namespace " << *iter << " {\n";
		}

		out << "const size_t " << count << " = " << includedFiles.size() << ";\n";
		out << "const char * const " << namearray << "[] = \n{";
		for (std::list<std::pair<std::string,std::string> >::iterator iter = includedFiles.begin();iter != includedFiles.end();++iter){
			out << "\t\"" << iter->first << "\",\n";
		}
		out << "\t0\n};\n";
		size_t pos = 0;
		std::list<size_t> sizes;
		for (std::list<std::pair<std::string,std::string> >::iterator iter = includedFiles.begin();iter != includedFiles.end();++iter){
			out << "const char " << dataarray << "_" << +(pos++) << "[] = {";
			{
				std::ifstream fin;
				fin.open(iter->second.c_str());
				if (!fin.is_open()){
					std::cerr << "ERROR: could not open file " << iter->second << std::endl;
					return pos+1;
				} else {
					if (liout.is_open()){
						liout << iter->first << "," << iter->second << std::endl;
					}
				}
				sizes.push_back(writeData(out,fin));
				fin.close();
			}
			out << "};\n";
		}
		pos = 0;
		out << "const char * const " << dataarray << "[] = \n{";
		for (std::list<std::pair<std::string,std::string> >::iterator iter = includedFiles.begin();iter != includedFiles.end();++iter){
			out << "\t" << dataarray << "_" << +(pos++) << ",\n";
		}
		out << "\t0\n};\n";

		out << "const size_t " << sizearray << "[] = \n{";
		for (std::list<size_t>::iterator iter = sizes.begin();iter != sizes.end();++iter){
			out << "\t" << *iter << ",\n";
		}
		out << "\t0\n};\n";

		for (std::list<std::string>::iterator iter = namespaces.begin();iter != namespaces.end();++iter){
			out << "} //" << *iter <<"\n";
		}

		out.flush();
		out.close();
		if (liout.is_open()){
			liout.flush();
			liout.close();
		}
	}

    // copy files to destination if the content changed
    if (!equalFileContent(destFile_h,outputFile_h))
        copyFile(outputFile_h,destFile_h);
    if (!equalFileContent(destFile_cpp,outputFile_cpp))
        copyFile(outputFile_cpp,destFile_cpp);

	return 0;


}
