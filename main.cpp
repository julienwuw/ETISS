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

@date July 29, 2014

@version 0.1

*/
/**
	@file

	@brief

	@detail




*/


#include <map>
#include <iostream>
#include <memory>

#include "etiss/ETISS.h"
#include "etiss/DebugSystem.h"


#include <cstring>

#include <sstream>

using namespace etiss;


#include "etiss/Instruction.h"

#include <ctime>


int main( int argc, const char* argv[] ) {
{

	etiss::Initializer initializer(argc,argv,"-fno-sigint-console");

	// create memory device
	DebugSystem dsys;
	// load image to memory
	dsys.load(0,"../SW/test_ARMv6M/code.bin");

	// can be used to write a small assembler programm beginning at address 0
	if (false){
		std::list<etiss::uint32> instructions;
		//OR1K
		{
//		    instructions.push_back(0x80dd70dd);
//		    instructions.push_back(0xb0f36080);// this is for the ISB instruction
//		    instructions.push_back(0x82468746);//little endioan this is to test the MOV instruction
//		    instructions.push_back(0x82438743);// this is for the ORRS instruction
//			instructions.push_back(0x85449544);//ADD SP plus reg, T2 Rm=0,2
//			instructions.push_back(0x68446944);//ADD SP plus reg, T1 Rdm=0,1
//			instructions.push_back(0x13b07fb0);//ADD SP plus imm, T2 imm=0x13,ff
//			instructions.push_back(0x13a8ffa8);//ADD SP plus imm, T1 imm=0x13,ff
//			instructions.push_back(0xb61ddb1c);//ADD imm, T1 imm3=6,3 Rn=6,3 Rd=6,3
//			instructions.push_back(0x8d19e718);//ADD reg, T1, rm=6,3 rn= 1,4 rd=5,7
//			instructions.push_back(0x87336934);//ADD imm, T2 imm8=0x87,0x69 Rdn=3,4
//			instructions.push_back(0x58443744);//ADD reg, T2, rm=b,6 rn= 0,7 rd=0,7
//			instructions.push_back(0x72415f41);//ADCS, rdn=2,7 rm = 6,3
//			instructions.push_back(0xf8a5f4a4);//ADR rd=5,4 imm=0xf8, 0xf4
//			instructions.push_back(0x2b401e40);//ANDS rm = 5,3 rn=3,6
//			instructions.push_back(0xAE15AD13);//ASR_imm imm5 = 0x16, 0xE   rm = 5,5 rd = 6, 5
//			instructions.push_back(0x16412d41);//ASR_reg rm = 2,5 rd = 6, 5
//			instructions.push_back(0xACD2FFD3);//B_T1 cond = 2,3 imm8 = 0xac.0xff
//			instructions.push_back(0xFFE0FFE7);//B_T2 imm11 = 0xff,0xeff
//			instructions.push_back(0xA943BA43);//BIC rm = 5,7 rdn = 1,2
//			instructions.push_back(0xFFF7DFD6);//BL s=1 imm10=0x3ff J1 = 0 J2 = 0 imm = 0x6df
//			instructions.push_back(0xE8479847);//BLX rm = 13,3
//			instructions.push_back(0x20472847);//BX rm = 4, 5
//			instructions.push_back(0x7f454c46);
//			instructions.push_back(0x01010100);
//			instructions.push_back(0x02002800);
//			instructions.push_back(0xa5803400);
//			instructions.push_back(0x02c804c8);
//			instructions.push_back(0x02680468);
//			instructions.push_back(0x01480348);
//			instructions.push_back(0x01580258);
//			instructions.push_back(0x02780478);
//			instructions.push_back(0x025d045d);
//			instructions.push_back(0x02880488);
//			instructions.push_back(0x035a015a);
//			instructions.push_back(0x03560456);
//			instructions.push_back(0x035e065e);
//			instructions.push_back(0x00000000);
//			instructions.push_back(0x81408340);
//			instructions.push_back(0x04080308);
//			instructions.push_back(0x0140c340);
//			instructions.push_back(0x04200321);
//			instructions.push_back(0x03460146);
//			instructions.push_back(0x00010002);
//			instructions.push_back(0x42434143);
//			instructions.push_back(0xc443c543); //instruction number 47 on note book
//			instructions.push_back(0xbf00bf00);//intruction 49--- nop
//			instructions.push_back(0x01430243);
//			instructions.push_back(0x02b804b8);
//			instructions.push_back(0x02b403b4);
//			instructions.push_back(0x02ba03ba);
//			instructions.push_back(0x41ba44ba);
//			instructions.push_back(0xc1bac2ba);
//			instructions.push_back(0xc241c341);
//			instructions.push_back(0x45424142);
//			instructions.push_back(0x82418341);
//			instructions.push_back(0x43bf42bf);
//			instructions.push_back(0x02c004c0);
//			instructions.push_back(0x03600460);
//			instructions.push_back(0x03900490);
//			instructions.push_back(0x30504050);
//			instructions.push_back(0x02700370);//instruciton number 64-- strb instruction
//			instructions.push_back(0x02540354);
//			instructions.push_back(0x03800480);
//			instructions.push_back(0x04520352);
//			instructions.push_back(0x021e041e);
//			instructions.push_back(0x04380238);
//			instructions.push_back(0x041a031a);
//			instructions.push_back(0x82b084b0);
//			instructions.push_back(0x06df05df);
//			instructions.push_back(0x43b244b2);
//			instructions.push_back(0x03b204b2);
//			instructions.push_back(0x03420442);
//			instructions.push_back(0x02de03de);
//			instructions.push_back(0xc1b2c3b2);
//			instructions.push_back(0x81b284b2);
//			instructions.push_back(0x23bf24bf);
//			instructions.push_back(0x34bf32bf);// the last instruction -- instructino number 81-- WFI instruction.
//			//--/////////////////////--32-bit-instruction-testing--/////////////////--//
//			instructions.push_back(0xb0f36080);
//			instructions.push_back(0xbff0508f);
//			instructions.push_back(0xbff3408f);
//			instructions.push_back(0xeff30080);
//			instructions.push_back(0x80f30088);
//			instructions.push_back(0xf0f700a6);//the 32 bit udf.w instruction f7f0a600
//			instructions.push_back(0xE0200803);
//			instructions.push_back(0x03FFFFF6);
//			instructions.push_back(0xE0200803);
    instructions.push_back(0x424100bf);//ADCS_Rdn_Rm_
    instructions.push_back(0xf91c00bf);//ADDS_Rd_Rn_imm3_
    instructions.push_back(0xca3700bf);//ADDS_Rdn_imm8_
    instructions.push_back(0xc81800bf);//ADDS_Rd_Rn_Rm_
    instructions.push_back(0x384400bf);//ADD_Rdn_Rm_
    instructions.push_back(0x58ab00bf);//ADD_Rd_SP_imm8_
    instructions.push_back(0x34b000bf);//ADD_SP_SP_imm7_
    instructions.push_back(0xe64400bf);//ADD_Rdm_SP_Rdm_
    instructions.push_back(0xe14400bf);//ADD_SP_Rm_
    instructions.push_back(0xd5a000bf);//ADR_Rd_label_
    instructions.push_back(0x224000bf);//ANDS_Rdn_Rm_
    instructions.push_back(0x481700bf);//ASRS_Rd_Rm_imm5_
    instructions.push_back(0x304100bf);//ASRS_Rdn_Rm_
    instructions.push_back(0x39d000bf);//BEQ_label_
    instructions.push_back(0x0dd100bf);//BNE_label_
    instructions.push_back(0x2bd200bf);//BCS_label_
    instructions.push_back(0x83d300bf);//BCC_label_
    instructions.push_back(0xa2d400bf);//BMI_label_
    instructions.push_back(0x07d500bf);//BPL_label_
    instructions.push_back(0xb3d600bf);//BVS_label_
    instructions.push_back(0x8fd700bf);//BVC_label_
    instructions.push_back(0x3ad800bf);//BHI_label_
    instructions.push_back(0x86d900bf);//BLS_label_
    instructions.push_back(0x74da00bf);//BGE_label_
    instructions.push_back(0x8cdb00bf);//BLT_label_
    instructions.push_back(0xd7dc00bf);//BGT_label_
    instructions.push_back(0x9edd00bf);//BLE_label_
    instructions.push_back(0xe9e400bf);//BAL_label_
    instructions.push_back(0xb34300bf);//BICS_Rdn_Rm_
    instructions.push_back(0xf6be00bf);//BKPT_imm8_
    instructions.push_back(0xe6f120f7);//BL_label_
    instructions.push_back(0xda4700bf);//BLX_Rm_
    instructions.push_back(0x724700bf);//BX_Rm_
    instructions.push_back(0xce4200bf);//CMN_Rn_Rm_
    instructions.push_back(0x0e2d00bf);//CMP_Rn_imm8_
    instructions.push_back(0xb74200bf);//CMP_Rn_Rm_
    instructions.push_back(0xab4500bf);//CMP_Rn_Rm_
    instructions.push_back(0xb6f358a4);//DMB_option_
    instructions.push_back(0xb5f34d8e);//DSB_option_
    instructions.push_back(0x614000bf);//EORS_Rdn_Rm_
    instructions.push_back(0xb9f36cae);//ISB_option_
    instructions.push_back(0xccc800bf);//LDM_Rn_registers_
    instructions.push_back(0x956f00bf);//LDR_Rt_Rn_imm5_
    instructions.push_back(0xfd9800bf);//LDR_Rt_[SP{_imm8_
    instructions.push_back(0x0a4b00bf);//LDR_Rt_label_
    instructions.push_back(0x575800bf);//LDR_Rt_Rn_Rm_
    instructions.push_back(0xf17c00bf);//LDRB_Rt_Rn_imm5_
    instructions.push_back(0x805d00bf);//LDRB_Rt_Rn_Rm_
    instructions.push_back(0x3a8d00bf);//LDRH_Rt_Rn_imm5_
    instructions.push_back(0x945b00bf);//LDRH_Rt_Rn_Rm_
    instructions.push_back(0x185700bf);//LDRSB_Rt_Rn_Rm_
    instructions.push_back(0x615f00bf);//LDRSH_Rt_Rn_Rm_
    instructions.push_back(0xa60400bf);//LSLS_Rd_Rm_imm5_
    instructions.push_back(0xb84000bf);//LSLS_Rdn_Rm_
    instructions.push_back(0x130a00bf);//LSRS_Rd_Rm_imm5_
    instructions.push_back(0xfb4000bf);//LSRS_Rdn_Rm_
    instructions.push_back(0x0b2300bf);//MOVS_Rd_imm8_
    instructions.push_back(0xee4600bf);//MOV_Rd_Rm_
    instructions.push_back(0x010000bf);//MOVS_Rd_Rm_
    instructions.push_back(0x494300bf);//MULS_Rdm_Rn_Rdm_
    instructions.push_back(0xf94300bf);//MVNS_Rd_Rm_
    instructions.push_back(0x00bf00bf);//NOP_
    instructions.push_back(0x0e4300bf);//ORRS_Rdn_Rm_
    instructions.push_back(0xe0bd00bf);//POP_registers_
    instructions.push_back(0xa1b400bf);//PUSH_registers_
    instructions.push_back(0x23ba00bf);//REV_Rd_Rm_
    instructions.push_back(0x65ba00bf);//REV16_Rd_Rm_
    instructions.push_back(0xd7ba00bf);//REVSH_Rd_Rm_
    instructions.push_back(0xdb4100bf);//RORS_Rdn_Rm_
    instructions.push_back(0x4d4200bf);//RSBS_Rd_Rn_#0_
    instructions.push_back(0x894100bf);//SBCS_Rdn_Rm_
    instructions.push_back(0x40bf00bf);//SEV_
    instructions.push_back(0x38c700bf);//STM_Rn_registers_
    instructions.push_back(0xf36200bf);//STR_Rt_Rn_imm5_
    instructions.push_back(0x229300bf);//STR_Rt_[SP_imm8_
    instructions.push_back(0xe55000bf);//STR_Rt_Rn_Rm_
    instructions.push_back(0x4e7300bf);//STRB_Rt_Rn_imm5_
    instructions.push_back(0x3a5400bf);//STRB_Rt_Rn_Rm_
    instructions.push_back(0xe88700bf);//STRH_Rt_Rn_imm5_
    instructions.push_back(0x925200bf);//STRH_Rt_Rn_Rm_
    instructions.push_back(0xb01f00bf);//SUBS_Rd_Rn_imm3_
    instructions.push_back(0x743e00bf);//SUBS_Rdn_imm8_
    instructions.push_back(0x131a00bf);//SUBS_Rd_Rn_Rm_
    instructions.push_back(0xa8b000bf);//SUB_SP_SP_imm7_
    instructions.push_back(0xbbdf00bf);//SVC_imm8_
    instructions.push_back(0x7ab200bf);//SXTB_Rd_Rm_
    instructions.push_back(0x3db200bf);//SXTH_Rd_Rm_
    instructions.push_back(0x364200bf);//TST_Rn_Rm_
    instructions.push_back(0xa5de00bf);//UDF_imm8_
    instructions.push_back(0xf5f71ba9);//UDF.W_imm16_
    instructions.push_back(0xc7b200bf);//UXTB_Rd_Rm_
    instructions.push_back(0x95b200bf);//UXTH_Rd_Rm_
    instructions.push_back(0x20bf00bf);//WFE_
    instructions.push_back(0x30bf00bf);//WFI_
    instructions.push_back(0x10bf00bf);//YIELD_


		}

		unsigned pos = 0;
		for (std::list<etiss::uint32>::iterator iter = instructions.begin();iter != instructions.end();iter++){
			etiss::uint8 buf[4];
			buf[0] = *iter>>24;
			buf[1] = *iter>>16;
			buf[2] = *iter>>8;
			buf[3] = *iter;
			dsys.dbg_write(pos,buf,4);
			pos += 4;
		}
	}


	std::map<std::string,std::string> options;

	options.clear();
	std::shared_ptr<etiss::CPUCore> cpu = etiss::CPUCore::create("ARMv6M","core0",options);

	if (!cpu){
		etiss::log(etiss::ERROR,"failed to create cpu core");
		return -1;
	}

	cpu->setTimer(false);

	VirtualStruct::root()->mountStruct("core0",cpu->getStruct());

	cpu->set(getJIT("GCCJIT"));

	etiss::uint64 sa = 0;
	//cpu->reset(&sa); // optional reset with start address


	options.clear();
	//cpu->addPlugin(etiss::getPlugin("PrintInstruction",options));	// a plugin that prints the instruction and its address when it is executed

	options.clear();
	options["port"] = "2222"; // define port (default: 2222)
	//cpu->addPlugin(etiss::getPlugin("gdbserver",options)); // adds a gdb debug server (connect with "target remote localhost:2222")

	options.clear();
	options["logaddr"] = "0x80000000";
	options["logmask"] = "0xF0000000";
	cpu->addPlugin(etiss::getPlugin("Logger",options)); // simple logger write to logaddr to print a character.


        etiss_int32 exception = cpu->execute(dsys);

	std::cout << "CPU exited with exception: 0x" <<std::hex << exception << std::dec << ": " << etiss::RETURNCODE::getErrorMessages()[exception] << std::endl;

	cpu.reset(); // delete cpu
}

	//quick_exit( 0 );

}

