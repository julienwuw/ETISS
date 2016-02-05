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

@date March 15, 2015

@version 0.1
*/
#include "ARMv6MArch.h"

using namespace etiss ;
using namespace etiss::instr ;

ARMv6MArch::ARMv6MArch():CPUArch("ARMv6M") {}

const std::set<std::string> & ARMv6MArch::getListenerSupportedRegisters()
{
    return listenerSupportedRegisters_;
}

// etiss::Plugin * newTimer(ETISS_CPU * cpu){}
// void deleteTimer(etiss::Plugin * timer){}

ETISS_CPU * ARMv6MArch::newCPU()
{
    ETISS_CPU * ret = (ETISS_CPU *) new ARMv6M() ;
    resetCPU (ret, 0);
    return ret;
}

void ARMv6MArch::resetCPU(ETISS_CPU * cpu,etiss::uint64 * startpointer)
{
    memset (cpu, 0, sizeof(ARMv6M));
    ARMv6M * armv6mcpu = (ARMv6M *) cpu;


    if (startpointer) cpu->instructionPointer = *startpointer;
    else cpu->instructionPointer =0;//  reference to manual
    cpu->mode = 1;
    cpu->cpuTime_ps = 0;
    cpu->cpuCycleTime_ps = 10000;
    //cpu->_timer_last_ps = 0;



    armv6mcpu->SP = armv6mcpu->R[13];
    //armv6mcpu->APSR = &(armv6mcpu->SPR[0]);
    //armv6mcpu->EPSR = &(armv6mcpu->SPR[1]);


}
void ARMv6MArch::deleteCPU(ETISS_CPU *cpu)
{
    delete (ARMv6M *) cpu ;
}
std::shared_ptr<etiss::VirtualStruct> ARMv6MArch::getVirtualStruct(ETISS_CPU * cpu)
{
    return etiss::VirtualStruct::allocate(cpu, [](etiss::VirtualStruct::Field*f)
    {
        delete f;
    });
}



/**
	@return 8 (jump instruction + instruction of delay slot)
*/
unsigned ARMv6MArch::getMaximumInstructionSizeInBytes()
{
    return 4;
}
/**
	@return 4
*/
unsigned ARMv6MArch::getInstructionSizeInBytes()
{
    return 2;
}
/**
	@brief required headers (OR1K.h)
*/
const std::set<std::string> & ARMv6MArch::getHeaders() const
{
    return headers_ ;
}
etiss::int32 ARMv6MArch::handleException(etiss::int32 code,ETISS_CPU * cpu)
{
    return code;    //
}


void ARMv6MArch::initCodeBlock(etiss::CodeBlock & cb) const
{
    cb.fileglobalCode().insert("#include \"Arch/ARMv6M.h\"\n");
}



etiss::instr::InstructionGroup Thumb("Thumb",16);
etiss::instr::InstructionGroup Thumb2("Thumb2",32);
etiss::instr::InstructionClass ThumbClass(1,"Thumb",16,Thumb); // since there is only one mode
etiss::instr::InstructionClass Thumb2Class(1,"Thumb2",32, Thumb2); // since there is only one mode

etiss::instr::InstructionCollection CortexM0("CortexM0",ThumbClass,Thumb2Class);

const char * registerName []= { "R0", "R1" , "R2", "R3" ,"R4", "R5","R6", "R7","R8", "R9","R10", "R11", "R12", "R13","R14", "R15" } ;

//--/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////--//
//-----------------------------------------------------------Alphabetical-order-16-bits-------------------------------------------------------------------------------



static InstructionDefinition ADCS_Rdn_Rm_(
	Thumb,
    "ADCS",
    (uint16_t)0x4140,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 n= Rdn.read(ba);
	etiss_uint16 d= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADCS\n")+
        "NULL;\n"
        "etiss_uint32 R_m:32;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C:32;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted:32;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint32 R_n:32;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result:32;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)shifted + APSR_C;\n"
        "etiss_uint64 unsigned_sum = R_n + shifted + APSR_C;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract:32;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit:32;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ADDS_Rd_Rn_imm3_(
	Thumb,
    "ADDS",
    (uint16_t)0x1c00,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Imm3 (8,6);
	etiss_uint16 imm3= Imm3.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADDS\n")+
        "etiss_uint32 R_n:32;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 imm32:32 = " + toString(imm3) + ";\n"
        "etiss_uint32 result:32;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)imm32 + 0;\n"
        "etiss_uint64 unsigned_sum = R_n + " + toString(n) + " + 0;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract:32;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit:32;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ADDS_Rdn_imm8_(
	Thumb,
    "ADDS",
    (uint16_t)0x3000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (10,8);
	etiss_uint16 n= Rdn.read(ba);
	etiss_uint16 d= Rdn.read(ba);
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADDS\n")+
        "etiss_uint32 R_n:32;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 imm32 = " + toString(imm8) + ";\n"
        "etiss_uint32 result:32;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)imm32 + 0;\n"
        "etiss_uint64 unsigned_sum = R_n + imm32 + 0;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract:32;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit:32;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ADDS_Rd_Rn_Rm_(
	Thumb,
    "ADDS",
    (uint16_t)0x1800,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADDS\n")+
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m:32;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C:32;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted:32;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n:32;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result:32;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)shifted + 0;\n"
        "etiss_uint64 unsigned_sum = R_n + shifted + 0;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "if(d == 15)\n"
        "{\n"
            "result &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
            "cpu->instructionPointer = result;\n"
        "}\n"
        "else\n"
        "{\n"
            "etiss_uint8 d:8;\n"
            "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
                    "if(setflags == 1)\n"
                    "{\n"
                        "etiss_uint32 field_store_from_bitextract:32;\n"
                        "unsigned long r = 0;\n"
                        "for (unsigned i=31; i<=31; i++){\n"
                        "		r |= 1 << i;\n"
                        "		}\n"
                        "field_store_from_bitextract = (r & result)>>31;\n"
                        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
                        "etiss_uint32 field_store_from_IsZeroBit:32;\n"
                        "unsigned flag = 0;\n"
                        "unsigned bit = 0;\n"
                        "for(unsigned i=0; i<=32-1; i++){\n"
                        "bit = (result >> i) & 1;\n"
                        "if (bit==1){\n"
                        "	flag = 1;\n"
                        "	break;\n"
                        "	}\n"
                        "}\n"
                        "if (flag==0)\n"
                        "field_store_from_IsZeroBit = 1;\n"
                        "else\n"
                        "field_store_from_IsZeroBit = 0;\n"
                        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
                        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
                        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)
                    "}\n"
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ADD_Rdn_Rm_(
	Thumb,
    "ADD",
    (uint16_t)0x4400,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange DN (7,7);
	etiss_uint16 dn= DN.read(ba);
    static BitArrayRange Rm (6,3);
	etiss_uint16 m= Rm.read(ba);
    static BitArrayRange Rdn (2,0);
	etiss_uint16 rdn= Rdn.read(ba);
    etiss_uint16 d = (dn<<3 ) + rdn;
    etiss_uint16 n = (dn<<3 ) + rdn;
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADD\n")+
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m:32;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C:32;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted:32;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n:32;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result:32;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)shifted + 0;\n"
        "etiss_uint64 unsigned_sum = R_n + shifted + 0;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "if(d == 15)\n"
        "{\n"
            "result &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
            "cpu->instructionPointer = result;\n"
        "}\n"
        "else\n"
        "{\n"
            "etiss_uint8 d:8;\n"
            "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
                    "if(setflags == 1)\n"
                    "{\n"
                        "etiss_uint32 field_store_from_bitextract:32;\n"
                        "unsigned long r = 0;\n"
                        "for (unsigned i=31; i<=31; i++){\n"
                        "		r |= 1 << i;\n"
                        "		}\n"
                        "field_store_from_bitextract = (r & result)>>31;\n"
                        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
                        "etiss_uint32 field_store_from_IsZeroBit:32;\n"
                        "unsigned flag = 0;\n"
                        "unsigned bit = 0;\n"
                        "for(unsigned i=0; i<=32-1; i++){\n"
                        "bit = (result >> i) & 1;\n"
                        "if (bit==1){\n"
                        "	flag = 1;\n"
                        "	break;\n"
                        "	}\n"
                        "}\n"
                        "if (flag==0)\n"
                        "field_store_from_IsZeroBit = 1;\n"
                        "else\n"
                        "field_store_from_IsZeroBit = 0;\n"
                        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
                        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
                        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)
                    "}\n"
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ADD_Rd_SP_imm8_(
	Thumb,
    "ADD",
    (uint16_t)0xa800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (10,8);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADD\n")+
        "NULL;\n"
        "etiss_uint32 SP:32;\n"
        "etiss_uint32 imm32 = " + toString(imm8) + ";\n"
        "etiss_uint32 result:32;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)SP + (etiss_int32)imm32 + 0;\n"
        "etiss_uint64 unsigned_sum = SP + imm32 + 0;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ADD_SP_SP_imm7_(
	Thumb,
    "ADD",
    (uint16_t)0xb000,
    (uint16_t)0xff80,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Imm7 (6,0);
	etiss_uint16 imm7= Imm7.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADD\n")+
        "NULL;\n"
        "etiss_uint32 SP:32;\n"
        "etiss_uint32 imm32= " + toString(imm7) + ";\n"
        "etiss_uint32 result:32;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)SP + (etiss_int32)imm32 + 0;\n"
        "etiss_uint64 unsigned_sum = SP + imm32 + 0;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[13]= result;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ADD_Rdm_SP_Rdm_(
	Thumb,
    "ADD",
    (uint16_t)0x4440,
    (uint16_t)0xff40,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange DM (7,7);
	etiss_uint16 dm= DM.read(ba);
    static BitArrayRange Rdm (2,0);
	etiss_uint16 rdm= Rdm.read(ba);
	etiss_uint16 d = dm<<3 + rdm;
	etiss_uint16 m = dm<<3 + rdm;
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADD\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint32 SP;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)SP + (etiss_int32)shifted + 0;\n"
        "etiss_uint64 unsigned_sum = SP + shifted + 0;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "if(d == 15)\n"
        "{\n"
            "result &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
            "cpu->instructionPointer = result;\n"
        "}\n"
        "else\n"
        "{\n"
            "etiss_uint8 d:8;\n"
            "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ADD_SP_Rm_(
	Thumb,
    "ADD",
    (uint16_t)0x4480,
    (uint16_t)0xff80,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rm (6,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADD\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)cpu->SP + (etiss_int32)shifted + 0;\n"
        "etiss_uint64 unsigned_sum = cpu->SP + shifted + 0;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "if(d == 15)\n"
        "{\n"
            "result &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
            "cpu->instructionPointer = result;\n"
        "}\n"
        "else\n"
        "{\n"
            "((ARMv6M*)cpu)->R[13]= result;\n"
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ADR_Rd_label_(
	Thumb,
    "ADR",
    (uint16_t)0xa000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (10,8);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ADR\n")+
        "NULL;\n"
        "if(add == 1)\n"
        "{\n"
            "cpu->instructionPointer &= ~(4)+1;\n"
            "etiss_int32 imm32=" + toString(label) + ";\n"
            "etiss_int32 result;\n"
            "result = cpu->instructionPointer + imm32;\n"
        "}\n"
        "else\n"
        "{\n"
            "cpu->instructionPointer &= ~(4)+1;\n"
            "result = cpu->instructionPointer - imm32;\n"
        "}\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ANDS_Rdn_Rm_(
	Thumb,
    "ANDS",
    (uint16_t)0x4000,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 n= Rdn.read(ba);
	etiss_uint16 d= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ANDS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "result = R_n & shifted;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ASRS_Rd_Rm_imm5_(
	Thumb,
    "ASRS",
    (uint16_t)0x1000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
    static BitArrayRange Imm5 (10,6);
	etiss_uint16 imm5= Imm5.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ASRS\n")+
        "NULL;\n"

        "etiss_uint32 shift_n;\n"
        " shift_n = " + toString(imm5) + ";\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "if (shift_n==0){\n"
        "result = R_m;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (shift_n>0);\n"
        "unsigned sign_bit = (R_m >> (32-1)) & 1;\n"
        "unsigned long mask = 0;\n"
        "for (unsigned i=32; i<=shift_n+32-1; i++){\n"
        "		mask |= 1 << sign_bit;\n"
        "		}\n"
        "etiss_uint64 extended_x = R_m | mask;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=shift_n; i<=shift_n+32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = r & extended_x;\n"
        "unsigned long t = 0;\n"
        "for (unsigned i=shift_n-1; i<=shift_n-1; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ASRS_Rdn_Rm_(
	Thumb,
    "ASRS",
    (uint16_t)0x4100,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 d= Rdn.read(ba);
	etiss_uint16 n= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ASRS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 R_m_7_0;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "R_m_7_0 = (r & R_m)>>0;\n"
        "etiss_uint32 shift_n;\n"
        "shift_n = R_m_7_0;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "if (shift_n==0){\n"
        "result = R_n;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (shift_n>0);\n"
        "unsigned sign_bit = (R_n >> (32-1)) & 1;\n"
        "unsigned long mask = 0;\n"
        "for (unsigned i=32; i<=shift_n+32-1; i++){\n"
        "		mask |= 1 << sign_bit;\n"
        "		}\n"
        "etiss_uint64 extended_x = R_n | mask;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=shift_n; i<=shift_n+32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = r & extended_x;\n"
        "unsigned long t = 0;\n"
        "for (unsigned i=shift_n-1; i<=shift_n-1; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract_1;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract_1 = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract_1 ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BEQ_label_(
	Thumb,
    "BEQ",
    (uint16_t)0xd000,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BNE_label_(
	Thumb,
    "BNE",
    (uint16_t)0xd100,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BCS_label_(
	Thumb,
    "BCS",
    (uint16_t)0xd200,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BCC_label_(
	Thumb,
    "BCC",
    (uint16_t)0xd300,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
   static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BMI_label_(
	Thumb,
    "BMI",
    (uint16_t)0xd400,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BPL_label_(
	Thumb,
    "BPL",
    (uint16_t)0xd500,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BVS_label_(
	Thumb,
    "BVS",
    (uint16_t)0xd600,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BVC_label_(
	Thumb,
    "BVC",
    (uint16_t)0xd700,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
   static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BHI_label_(
	Thumb,
    "BHI",
    (uint16_t)0xd800,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BLS_label_(
	Thumb,
    "BLS",
    (uint16_t)0xd900,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BGE_label_(
	Thumb,
    "BGE",
    (uint16_t)0xda00,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BLT_label_(
	Thumb,
    "BLT",
    (uint16_t)0xdb00,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BGT_label_(
	Thumb,
    "BGT",
    (uint16_t)0xdc00,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BLE_label_(
	Thumb,
    "BLE",
    (uint16_t)0xdd00,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
   static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BAL_label_(
	Thumb,
    "BAL",
    (uint16_t)0xe000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//B\n")+
        "etiss_int32 PC;\n"
        "etiss_int32 imm32 = " + toString(label) + "\n"
        "etiss_int32 ADD_;\n"
        "ADD_ = PC + imm32;\n"
        " static BitArrayRange cond(11,8);\n"
        " etiss_uint8 condition= rdn.read(cond);\n"
        " condition &= ~(1 << 0);\n"
        "etiss_uint8 APSR_N = (((ARMv6M*)cpu)->APSR >>31) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_Z = (((ARMv6M*)cpu)->APSR >>30) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_C = (((ARMv6M*)cpu)->APSR >>29) & 1;\n"//(number >> x) & 1
        "etiss_uint8 APSR_V = (((ARMv6M*)cpu)->APSR >>28) & 1;\n"//(number >> x) & 1
        " switch(condition){\n"
        " case 0:	if (APSR_Z == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 2:	if (APSR_C == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 4:	if (APSR_N == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 6:	if (APSR_V == 1)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 8:	if (APSR_C == 1 && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 10:	if (APSR_N == APSR_V)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 12:	if (APSR_N == APSR_V && APSR_Z == 0)\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " case 14:\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"
        " }\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BICS_Rdn_Rm_(
	Thumb,
    "BICS",
    (uint16_t)0x4380,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 d= Rdn.read(ba);
	etiss_uint16 n= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//BICS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 NOT_;\n"
        "NOT_ = ~shifted;\n"
        "etiss_uint32 result;\n"
        "result = R_n & NOT_;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BKPT_imm8_(
	Thumb,
    "BKPT",
    (uint16_t)0xbe00,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//BKPT\n")
;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BL_label_(
	Thumb,
    "BL",
    (uint32_t)0xf000d000,
    (uint32_t)0xf800d000,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Label (25,16);
	etiss_uint16 imm10= Label.read(ba);
    static BitArrayRange Label_2 (10,0);
	etiss_uint16 imm11= Label_2.read(ba);
	static BitArrayRange S (26,26);
	etiss_uint8 s= S.read(ba);
    static BitArrayRange J1 (13,13);
	etiss_uint8 j1= J1.read(ba);
    static BitArrayRange J2 (11,11);
	etiss_uint8 j2= J2.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//BL\n")+
        "etiss_uint32 EOR_;\n"
        "EOR_ = " + toString(j1) + " ^ " + toString(s) + ";\n"
        "etiss_uint32 I1;\n"
        "I1 = ~EOR_;\n"
        "etiss_uint32 EOR_1_;\n"
        "EOR_1_ = " + toString(j2) + " ^ " + toString(s) + ";\n"
        "etiss_uint32 I2;\n"
        "I2 = ~EOR_1_;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(s) + "<<24+I1<<23+I2<<22+" + toString(imm10) + "<<12+" + toString(imm11) + "<<1;\n"
        "NULL;\n"
        "etiss_uint8 PC:8;\n"
        "etiss_uint32 next_instr_addr;\n"
        " next_instr_addr = PC;\n"
        "etiss_uint32 next_instr_addr_31_1;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=1; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "next_instr_addr_31_1 = (r & next_instr_addr)>>1;\n"
//CONCAT!!
        "etiss_int32 ADD_;\n"
        "ADD_ = cpu->instructionPointer + imm32;\n"
        "ADD_ &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
        "cpu->instructionPointer = ADD_;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BLX_Rm_(
	Thumb,
    "BLX",
    (uint16_t)0x4780,
    (uint16_t)0xff80,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rm (6,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//BLX\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 target;\n"
        " target = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_int32 PC;\n"
        "etiss_int32 next_instr_addr;\n"
        "next_instr_addr = PC - 2;\n"
        "etiss_uint32 next_instr_addr_31_1;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=1; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "next_instr_addr_31_1 = (r & next_instr_addr)>>1;\n"
//CONCAT!!
        "etiss_int8 x = (target) & 1;\n"
        "((ARMv6M*)cpu)-> EPSR ^= (-x ^ (((ARMv6M*)cpu)-> EPSR)) & (1 << 24);\n"//EPSR.T = address<0>;
        "target &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);\n"
        "cpu->instructionPointer = target;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition BX_Rm_(
	Thumb,
    "BX",
    (uint16_t)0x4700,
    (uint16_t)0xff80,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rm (6,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//BX\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_int8 x = (R_m) & 1;\n"
        "((ARMv6M*)cpu)-> EPSR ^= (-x ^ (((ARMv6M*)cpu)-> EPSR)) & (1 << 24);\n"//EPSR.T = address<0>;
        "R_m &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);\n"
        "cpu->instructionPointer = R_m;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition CMN_Rn_Rm_(
	Thumb,
    "CMN",
    (uint16_t)0x42c0,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rn (2,0);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//CMN\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)shifted + 0;\n"
        "etiss_uint64 unsigned_sum = R_n + shifted + 0;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition CMP_Rn_imm8_(
	Thumb,
    "CMP",
    (uint16_t)0x2800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rn (10,8);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//CMP\n")+
        "NULL;\n"
        "etiss_uint32 imm32=" + toString(imm8) + "\n"
        "etiss_uint32 N_imm32;\n"
        "N_imm32 = ~imm32;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)N_imm32 + 1;\n"
        "etiss_uint64 unsigned_sum = R_n + N_imm32 + 1;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition CMP_Rn_Rm_(
	Thumb,
    "CMP",
    (uint16_t)0x4280,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rn (2,0);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//CMP\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint32 N_shifted;\n"
        "N_shifted = ~shifted;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)N_shifted + 1;\n"
        "etiss_uint64 unsigned_sum = R_n + N_shifted + 1;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition CMP_Rn_Rm_2(
	Thumb,
    "CMP",
    (uint16_t)0x4580,
    (uint16_t)0xff80,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange N (7,7);
	etiss_uint16 n_= N.read(ba);
    static BitArrayRange Rn (2,0);
	etiss_uint16 rn= Rn.read(ba);
    static BitArrayRange Rm (6,3);
	etiss_uint16 m= Rm.read(ba);
	etiss_uint16 n = n_<<3 + rn;
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//CMP\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint32 N_shifted;\n"
        "N_shifted = ~shifted;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)N_shifted + 1;\n"
        "etiss_uint64 unsigned_sum = R_n + N_shifted + 1;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition DMB_option_(
	Thumb,
    "DMB",
    (uint32_t)0xf3b08050,
    (uint32_t)0xfff0d0f0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Option (3,0);
	etiss_uint16 option= Option.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//DMB\n")

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition DSB_option_(
	Thumb,
    "DSB",
    (uint32_t)0xf3b08040,
    (uint32_t)0xfff0d0f0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Option (3,0);
	etiss_uint16 option= Option.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//DSB\n")

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition EORS_Rdn_Rm_(
	Thumb,
    "EORS",
    (uint16_t)0x4040,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 n= Rdn.read(ba);
	etiss_uint16 d= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//EORS\n")+
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "result = R_n ^ {b};\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ISB_option_(
	Thumb,
    "ISB",
    (uint32_t)0xf3b08060,
    (uint32_t)0xfff0d0f0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Option (3,0);
	etiss_uint16 option= Option.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ISB\n")

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDM_Rn_registers_(
	Thumb,
    "LDM",
    (uint16_t)0xc800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rn (10,8);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Registers (7,0);
	etiss_uint16 registers= Registers.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDM\n")+
        "NULL;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 address;\n"
        " address = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint8 i;\n"
        "for(i=0;i<=7;i=i+1)\n"
        "{\n"
		"etiss_uint32 registers_i;\n"
		"unsigned long r = 0;\n"
		"for (unsigned j=i; j<=i; j++){\n"
		"		r |= 1 << j;\n"
		"		}\n"
		"registers_i = (r & " + toString(registers) + ")>>i;\n"
		"if(registers_i == 1)\n"
                    "{\n"
                    "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[i];\n"
                    "etiss_int32 reg_store_from_MemA = (*(system->dread))(system->handle,cpu,address,buf,4);\n"
                    "((ARMv6M*)cpu)->R[i]= reg_store_from_MemA;\n"
                    "address = address + 4;\n"
                    "}\n"
        "}\n"
        "unsigned long r = 0;\n"
        "for (unsigned j=n; j<=n; j++){\n"
        "		r |= 1 << j;\n"
        "		}\n"
        "registers_n = (r & " + toString(registers) + ")>>n;\n"
        "if(registers_n == 0)\n"
        "{\n"
            "etiss_uint32 R_n;\n"
            " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
            "etiss_int32 ADD_1_;\n"
            "ADD_1_ = R_n + 4;\n"
            "etiss_uint8 BitCount_:8;\n"
            "for(BitCount_=0;" + toString(registers) + "!=0;" + toString(registers) + ">>=1)\n"
            "{\n"
            "if (" + toString(registers) + " & 01)\n"
            "	BitCount_++;\n"
            "}\n"
            "etiss_int32 reg_store_from_MUL;\n"
            "reg_store_from_MUL = ADD_1_ * BitCount_;\n"
            "((ARMv6M*)cpu)->R[" + toString(n) + "]= reg_store_from_MUL;\n"
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDR_Rt_Rn_imm5_(
	Thumb,
    "LDR",
    (uint16_t)0x6800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Imm5 (10,6);
	etiss_uint16 imm5= Imm5.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDR\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm5) + " ;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + imm32;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_int32 reg_store_from_MemU = (*(system->dread))(system->handle,cpu,address,buf,4);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_MemU;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDR_Rt_SP_imm8_(
	Thumb,
    "LDR",
    (uint16_t)0x9800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (10,8);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDR\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm8) + " ;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[13];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + imm32;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_int32 reg_store_from_MemU = (*(system->dread))(system->handle,cpu,address,buf,4);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_MemU;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDR_Rt_label_(
	Thumb,
    "LDR",
    (uint16_t)0x4800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (10,8);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Label (7,0);
	etiss_uint16 label= Label.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDR\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(label) + " ;\n"
        "cpu->instructionPointer &= ~(4)+1;\n"
        "etiss_int32 base;\n"
        "etiss_int32 address;\n"
        "address = base + imm32;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_int32 reg_store_from_MemU = (*(system->dread))(system->handle,cpu,address,buf,4);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_MemU;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDR_Rt_Rn_Rm_(
	Thumb,
    "LDR",
    (uint16_t)0x5800,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDR\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 offset;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "offset = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "offset = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + offset;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint32 reg_store_from_MemU = (*(system->dread))(system->handle,cpu,address,buf,4);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_MemU;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDRB_Rt_Rn_imm5_(
	Thumb,
    "LDRB",
    (uint16_t)0x7800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Imm5 (10,6);
	etiss_uint16 imm5= Imm5.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDRB\n")+
        "NULL;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 imm32 = " + toString(imm5) + ";\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + imm32;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint32 reg_store_from_ZeroExtend = (*(system->dread))(system->handle,cpu,address,buf,1);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_ZeroExtend;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDRB_Rt_Rn_Rm_(
	Thumb,
    "LDRB",
    (uint16_t)0x5c00,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDRB\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 offset;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "offset = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "offset = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + offset;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint32 reg_store_from_ZeroExtend = (*(system->dread))(system->handle,cpu,address,buf,1);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_ZeroExtend;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDRH_Rt_Rn_imm5_(
	Thumb,
    "LDRH",
    (uint16_t)0x8800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Imm5 (10,6);
	etiss_uint16 imm5= Imm5.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDRH\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm5) + " ;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + imm32;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint32 reg_store_from_ZeroExtend_1 = (*(system->dread))(system->handle,cpu,address,buf,2);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_ZeroExtend_1;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDRH_Rt_Rn_Rm_(
	Thumb,
    "LDRH",
    (uint16_t)0x5a00,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDRH\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 offset;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "offset = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "offset = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + offset;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint32 reg_store_from_ZeroExtend = (*(system->dread))(system->handle,cpu,address,buf,2);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_ZeroExtend;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDRSB_Rt_Rn_Rm_(
	Thumb,
    "LDRSB",
    (uint16_t)0x5600,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDRSB\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 offset;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "offset = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "offset = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + offset;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_int32 reg_store_from_SignExtend = (*(system->dread))(system->handle,cpu,address,buf,1);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_SignExtend;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LDRSH_Rt_Rn_Rm_(
	Thumb,
    "LDRSH",
    (uint16_t)0x5e00,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LDRSH\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 offset;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "offset = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "offset = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + offset;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_int32 reg_store_from_SignExtend = (*(system->dread))(system->handle,cpu,address,buf,2);\n"
        "((ARMv6M*)cpu)->R[" + toString(t) + "]= reg_store_from_SignExtend;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LSLS_Rd_Rm_imm5_(
	Thumb,
    "LSLS",
    (uint16_t)0x0,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
    static BitArrayRange Imm5 (10,6);
	etiss_uint16 imm5= Imm5.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LSLS\n")+
        "NULL;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "if (" + toString(imm5) + "==0){\n"
        "result = R_m;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (" + toString(imm5) + ">0);\n"
        "etiss_uint64 extended_x = R_m<<" + toString(imm5) + ";\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LSLS_Rdn_Rm_(
	Thumb,
    "LSLS",
    (uint16_t)0x4080,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 n= Rdn.read(ba);
	etiss_uint16 d= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LSLS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 R_m_7_0;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "R_m_7_0 = (r & R_m)>>0;\n"
        "etiss_uint32 shift_n;\n"
        "shift_n = R_m_7_0;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "if (shift_n==0){\n"
        "result = R_n;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (shift_n>0);\n"
        "etiss_uint64 extended_x = R_n<<shift_n;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract_1;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract_1 = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract_1 ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LSRS_Rd_Rm_imm5_(
	Thumb,
    "LSRS",
    (uint16_t)0x800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
    static BitArrayRange Imm5 (10,6);
	etiss_uint16 imm5= Imm5.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LSRS\n")+
        "NULL;\n"
        "if(" + toString(imm5) + " == 00000)\n"
        "{\n"
            "etiss_uint32 shift_n;\n"
            " shift_n = 32;\n"
        "}\n"
        "else\n"
        "{\n"
            " shift_n = " + toString(imm5) + ";\n"
        "}\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "if (shift_n==0){\n"
        "result = R_m;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
		"assert (shift_n>0);\n"
        "etiss_uint64 extended_x = R_m;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=shift_n; i<=shift_n+32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = r & extended_x;\n"
        "unsigned long t = 0;\n"
        "for (unsigned i=shift_n-1; i<=shift_n-1; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition LSRS_Rdn_Rm_(
	Thumb,
    "LSRS",
    (uint16_t)0x40c0,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 d= Rdn.read(ba);
	etiss_uint16 n= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//LSRS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 R_m_7_0;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "R_m_7_0 = (r & R_m)>>0;\n"
        "etiss_uint32 shift_n;\n"
        "shift_n = R_m_7_0;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "if (shift_n==0){\n"
        "result = R_n;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
		"assert (shift_n>0);\n"
        "etiss_uint64 extended_x = R_n;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=shift_n; i<=shift_n+32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = r & extended_x;\n"
        "unsigned long t = 0;\n"
        "for (unsigned i=shift_n-1; i<=shift_n-1; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract_1;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract_1 = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract_1 ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition MOVS_Rd_imm8_(
	Thumb,
    "MOVS",
    (uint16_t)0x2000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (10,8);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//MOVS\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm8) + " ;\n"
        "etiss_uint32 carry;\n"
        "carry = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result;\n"
        " result = imm32;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition MOV_Rd_Rm_(
	Thumb,
    "MOV",
    (uint16_t)0x4600,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange D (7,7);
	etiss_uint16 d_= D.read(ba);
    static BitArrayRange Rd (2,0);
	etiss_uint16 rd= Rd.read(ba);
    static BitArrayRange Rm (6,3);
	etiss_uint16 m= Rm.read(ba);
	etiss_uint16 d= d_<<3 + rd;
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//MOVS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 result;\n"
        " result = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "if(d == 15)\n"
        "{\n"
            "result &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
            "cpu->instructionPointer = result;\n"
        "}\n"
        "else\n"
        "{\n"
            "etiss_uint8 d:8;\n"
            "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
            "etiss_uint32 field_store_from_bitextract;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition MOVS_Rd_Rm_(
	Thumb,
    "MOVS",
    (uint16_t)0x0,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//MOV\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 result;\n"
        " result = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "if(d == 15)\n"
        "{\n"
            "result &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);
            "cpu->instructionPointer = result;\n"
        "}\n"
        "else\n"
        "{\n"
            "etiss_uint8 d:8;\n"
            "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition MULS_Rdm_Rn_Rdm_(
	Thumb,
    "MULS",
    (uint16_t)0x4340,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdm (2,0);
	etiss_uint16 m= Rdm.read(ba);
	etiss_uint16 d= Rdm.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//MULS\n")+
        "NULL;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 operand1;\n"
        "operand1 = R_n;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_int32 operand2;\n"
        "operand2 = R_m;\n"
        "etiss_int32 result;\n"
        "result = operand1 * operand2;\n"
        "etiss_uint32 reg_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "reg_store_from_bitextract = (r & result)>>0;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= reg_store_from_bitextract;\n"
        "etiss_uint32 field_store_from_bitextract_1;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract_1 = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract_1 ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition MVNS_Rd_Rm_(
	Thumb,
    "MVNS",
    (uint16_t)0x43c0,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//MVNS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint32 result;\n"
        "result = ~shifted;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition NOP_(
	Thumb,
    "NOP",
    (uint16_t)0xbf00,
    (uint16_t)0xffff,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
	    CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//NOP\n")+
        "NULL;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition ORRS_Rdn_Rm_(
	Thumb,
    "ORRS",
    (uint16_t)0x4300,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 d= Rdn.read(ba);
	etiss_uint16 n= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//ORRS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "result = R_n | {b};\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition POP_registers_(
	Thumb,
    "POP",
    (uint16_t)0xbc00,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Registers (7,0);
	etiss_uint16 registers= Registers.read(ba);
    static BitArrayRange P (8,8);
	etiss_uint16 p= P.read(ba);

	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//POP\n")+
        "NULL;\n"
        "etiss_uint32 registers = " + toString(p) + "<<15+" + toString(registers) + ";\n"
        "etiss_uint32 address;\n"
        " address = ((ARMv6M*)cpu)->SP;\n"
        "for(i=0;i<=7;i=i+1)\n"
        "{\n"
		"etiss_uint8 i:1;\n"
		"etiss_uint32 registers_i;\n"
		"unsigned long r = 0;\n"
		"for (unsigned j=i; j<=i; j++){\n"
		"		r |= 1 << j;\n"
		"		}\n"
		"registers_i = (r & registers)>>i;\n"
		"if(registers_i == 1)\n"
                    "{\n"
                        "etiss_uint8 * buf = (etiss_uint8 *)&((ARMv6M*)cpu)->R[i];\n"
                        "etiss_int32 reg_store_from_MemA = (*(system->dread))(system->handle,cpu,address,buf,4);\n"
                        "((ARMv6M*)cpu)->R[i]= reg_store_from_MemA;\n"
                        "address = address + 4;\n"
                    "}\n"
        "}\n"
		"unsigned long r = 0;\n"
		"for (unsigned i=15; i<=15; i++){\n"
		"		r |= 1 << i;\n"
		"		}\n"
		"registers_15 = (r & registers)>>15;\n"
		"if(registers_15 == 1)\n"
        "{\n"
            "etiss_uint8 * buf = (etiss_uint8 *)&cpu->instructionPointer;\n"
            "etiss_int32 Mem_address = (*(system->dread))(system->handle,cpu,address,buf,4);\n"
            "etiss_int8 x = (Mem_address) & 1;\n"
            "((ARMv6M*)cpu)-> EPSR ^= (-x ^ (((ARMv6M*)cpu)-> EPSR)) & (1 << 24);\n"//EPSR.T = address<0>;
            "Mem_address &= ~(1 << 0);\n"//BranchTo(address<31:1>:’0’);\n"
            "cpu->instructionPointer = Mem_address;\n"
        "}\n"
        "etiss_int32 ADD_1_;\n"
        "ADD_1_ = SP + 4;\n"
        "etiss_uint8 BitCount_:8;\n"
        "for(BitCount_=0;registers!=0;registers>>=1)\n"
        "{\n"
        "if (registers & 01)\n"
        "	BitCount_++;\n"
        "}\n"
        "((ARMv6M*)cpu)->SP = ADD_1_ * BitCount_;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition PUSH_registers_(
	Thumb,
    "PUSH",
    (uint16_t)0xb400,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Registers (7,0);
	etiss_uint16 registers= Registers.read(ba);
	static BitArrayRange M (8,8);
	etiss_uint16 m= M.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//PUSH\n")+
        "NULL;\n"
        "etiss_uint32 registers = " + toString(m) + "<<14+" + toString(registers) + ";\n"
        "etiss_uint8 BitCount_:8;\n"
        "for(BitCount_=0;registers!=0;registers>>=1)\n"
        "{\n"
        "if (registers & 01)\n"
        "	BitCount_++;\n"
        "}\n"
        "etiss_int32 address;\n"
        "address = ((ARMv6M*)cpu)->SP - 4* BitCount_;\n"
        "etiss_uint8 i;\n"
        "for(i=0;i<=14;i=i+1)\n"
        "{\n"
		"etiss_uint32 registers_i;\n"
		"unsigned long r = 0;\n"
		"for (unsigned j=i; j<=i; j++){\n"
		"		r |= 1 << j;\n"
		"		}\n"
		"registers_i = (r & registers)>>i;\n"
		"if(registers_i == 1)\n"
                    "{\n"
                        "etiss_uint32 mem_fetch_from_regfetch;\n"
                        " mem_fetch_from_regfetch = ((ARMv6M*)cpu)->R[i];\n"
                        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_regfetch;\n"
                        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,4);\n"
                        "address = address + 4;\n"
                    "}\n"
        "}\n"
        "for(BitCount_=0;registers!=0;registers>>=1)\n"
        "{\n"
        "if (registers & 01)\n"
        "	BitCount_++;\n"
        "}\n"
        "SP = SP - 4 * BitCount_;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition REV_Rd_Rm_(
	Thumb,
    "REV",
    (uint16_t)0xba00,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//REV\n")+
        "NULL;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = (r & R_m)>>0;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=24; i<=31; i++){\n"
        "		bit = (result >> (i - 24)) & 1;\n"
        "		result &= ~(1 << (i - 24));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=8; i<=15; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = (r & R_m)>>8;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=16; i<=23; i++){\n"
        "		bit = (result >> (i - 16)) & 1;\n"
        "		result &= ~(1 << (i - 16));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=16; i<=23; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = (r & R_m)>>16;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=8; i<=15; i++){\n"
        "		bit = (result >> (i - 8)) & 1;\n"
        "		result &= ~(1 << (i - 8));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=24; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = (r & R_m)>>24;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		bit = (result >> (i - 0)) & 1;\n"
        "		result &= ~(1 << (i - 0));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition REV16_Rd_Rm_(
	Thumb,
    "REV16",
    (uint16_t)0xba40,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//REV16\n")+
        "NULL;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=16; i<=23; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = (r & R_m)>>16;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=24; i<=31; i++){\n"
        "		bit = (result >> (i - 24)) & 1;\n"
        "		result &= ~(1 << (i - 24));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=24; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = (r & R_m)>>24;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=16; i<=23; i++){\n"
        "		bit = (result >> (i - 16)) & 1;\n"
        "		result &= ~(1 << (i - 16));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = (r & R_m)>>0;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=8; i<=15; i++){\n"
        "		bit = (result >> (i - 8)) & 1;\n"
        "		result &= ~(1 << (i - 8));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=8; i<=15; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = (r & R_m)>>8;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		bit = (result >> (i - 0)) & 1;\n"
        "		result &= ~(1 << (i - 0));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition REVSH_Rd_Rm_(
	Thumb,
    "REVSH",
    (uint16_t)0xbac0,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//REVSH\n")+
        "NULL;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 R_m_7_0;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "R_m_7_0 = (r & R_m)>>0;\n"
        "result = R_m_7_0 ;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=8; i<=31; i++){\n"
        "		bit = (result >> (i - 8)) & 1;\n"
        "		result &= ~(1 << (i - 8));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=8; i<=15; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result = (r & R_m)>>8;\n"
        "unsigned short bit:1;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		bit = (result >> (i - 0)) & 1;\n"
        "		result &= ~(1 << (i - 0));\n"
        "		result ^= (-bit ^ result) & (1 << i);\n"
        "		}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition RORS_Rdn_Rm_(
	Thumb,
    "RORS",
    (uint16_t)0x41c0,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 n= Rdn.read(ba);
	etiss_uint16 d= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//RORS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 R_m_7_0;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "R_m_7_0 = (r & R_m)>>0;\n"
        "etiss_uint32 shift_n;\n"
        "shift_n = R_m_7_0;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "if (shift_n==0){\n"
        "result = R_n;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (shift_n!=0);\n"
        "int m = shift_n%32;\n"
        "etiss_uint64 extended_x_0 = R_n;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=m; i<=m+32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result_0 = r & extended_x_0;\n"
        "etiss_uint64 extended_x_1 = R_n<<(32-m);\n"
        "unsigned t = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "result_1 = t & extended_x_1;\n"
        "result = result_0 | result_1;\n"
        "unsigned long s = 0;\n"
        "for (unsigned i=32-1; i<=32-1; i++){\n"
        "		s |= 1 << i;\n"
        "		}\n"
        "carry = s & result;\n"
        "}\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "if(setflags == 1)\n"
        "{\n"
            "etiss_uint32 field_store_from_bitextract_1;\n"
            "unsigned long r = 0;\n"
            "for (unsigned i=31; i<=31; i++){\n"
            "		r |= 1 << i;\n"
            "		}\n"
            "field_store_from_bitextract_1 = (r & result)>>31;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract_1 ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
            "etiss_uint32 field_store_from_IsZeroBit;\n"
            "unsigned flag = 0;\n"
            "unsigned bit = 0;\n"
            "for(unsigned i=0; i<=32-1; i++){\n"
            "bit = (result >> i) & 1;\n"
            "if (bit==1){\n"
            "	flag = 1;\n"
            "	break;\n"
            "	}\n"
            "}\n"
            "if (flag==0)\n"
            "field_store_from_IsZeroBit = 1;\n"
            "else\n"
            "field_store_from_IsZeroBit = 0;\n"
            "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
            "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition RSBS_Rd_Rn_0_(
	Thumb,
    "RSBS",
    (uint16_t)0x4240,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//RSBS\n")+
        "NULL;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 N_R_n;\n"
        "N_R_n = ~R_n;\n"
        "etiss_uint32 imm32;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)N_R_n + (etiss_int32)imm32 + 1;\n"
        "etiss_uint64 unsigned_sum = N_R_n + imm32 + 1;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition SBCS_Rdn_Rm_(
	Thumb,
    "SBCS",
    (uint16_t)0x4180,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (2,0);
	etiss_uint16 n= Rdn.read(ba);
	etiss_uint16 d= Rdn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//SBCS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint32 N_shifted;\n"
        "N_shifted = ~shifted;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)N_shifted + APSR_C;\n"
        "etiss_uint64 unsigned_sum = R_n + N_shifted + APSR_C;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition SEV_(
	Thumb,
    "SEV",
    (uint16_t)0xbf40,
    (uint16_t)0xffff,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
	    CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//SEV\n")

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition STM_Rn_registers_(
	Thumb,
    "STM",
    (uint16_t)0xc000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rn (10,8);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Registers (7,0);
	etiss_uint16 registers= Registers.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//STM\n")+
        "NULL;\n"
        "etiss_uint16 registers= " + toString(registers) + ";\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 address;\n"
        " address = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint8 i;\n"
        "for(i=0;i<=14;i=i+1)\n"
        "{\n"
			"etiss_uint32 registers_i;\n"
			"unsigned long r = 0;\n"
			"for (unsigned j=i; j<=i; j++){\n"
			"		r |= 1 << j;\n"
			"		}\n"
			"registers_i = (r & registers)>>i;\n"
			"if(registers_i == 1)\n"
                    "{\n"
                        "etiss_uint8 k:8;\n"
                        "if(registers == 0){\n"
                        "	k = 32;\n"
                        "}\n"
                        "while (!(registers & 1))\n"
                        "{\n"
                        "     registers >>= 1;\n"
                        "     ++k;\n"
                        "}\n"
                "if(i != k && i == " + toString(n) + ")\n"
                        "{\n"
                            "etiss_uint32 mem_fetch_from_bits;\n"
                        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_bits;\n"
                        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,4);\n"
                        "}\n"
                        "else\n"
                        "{\n"
                            "etiss_uint32 mem_fetch_from_regfetch_1;\n"
                            " mem_fetch_from_regfetch_1 = ((ARMv6M*)cpu)->R[i];\n"
                        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_regfetch_1;\n"
                        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,4);\n"
                        "}\n"
                        "address = address + 4;\n"
                    "}\n"
        "}\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 ADD_1_;\n"
        "ADD_1_ = R_n + 4;\n"
        "etiss_uint8 BitCount_:8;\n"
        "for(BitCount_=0;registers!=0;registers>>=1)\n"
        "{\n"
        "if (registers & 01)\n"
        "	BitCount_++;\n"
        "}\n"
        "etiss_int32 reg_store_from_MUL;\n"
        "reg_store_from_MUL = ADD_1_ * BitCount_;\n"
        "((ARMv6M*)cpu)->R[" + toString(n) + "]= reg_store_from_MUL;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition STR_Rt_Rn_imm5_(
	Thumb,
    "STR",
    (uint16_t)0x6000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Imm5 (10,6);
	etiss_uint16 imm5= Imm5.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//STR\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm5) + " ;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + imm32;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 t:8;\n"
        "etiss_uint32 mem_fetch_from_regfetch_1;\n"
        " mem_fetch_from_regfetch_1 = ((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_regfetch_1;\n"
        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,4);\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition STR_Rt_SP_imm8_(
	Thumb,
    "STR",
    (uint16_t)0x9000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (10,8);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//STR\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm8) + " ;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[13];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + imm32;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 t:8;\n"
        "etiss_uint32 mem_fetch_from_regfetch_1;\n"
        " mem_fetch_from_regfetch_1 = ((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_regfetch_1;\n"
        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,4);\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition STR_Rt_Rn_Rm_(
	Thumb,
    "STR",
    (uint16_t)0x5000,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//STR\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 offset;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "offset = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "offset = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 address;\n"
        "address = R_n + offset;\n"
        "etiss_uint8 t:8;\n"
        "etiss_uint32 mem_fetch_from_regfetch_2;\n"
        " mem_fetch_from_regfetch_2 = ((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_regfetch_2;\n"
        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,4);\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition STRB_Rt_Rn_imm5_(
	Thumb,
    "STRB",
    (uint16_t)0x7000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Imm5 (10,6);
	etiss_uint16 imm5= Imm5.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//STRB\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm5) + " ;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + imm32;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 t:8;\n"
        "etiss_uint32 R_t;\n"
        " R_t = ((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint32 mem_fetch_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "mem_fetch_from_bitextract = (r & R_t)>>0;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_bitextract;\n"
        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,1);\n"
        "if(wback == 1)\n"
        "{\n"
            "((ARMv6M*)cpu)->R[" + toString(n) + "]= offset_addr;\n"
        "}\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition STRB_Rt_Rn_Rm_(
	Thumb,
    "STRB",
    (uint16_t)0x5400,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//STRB\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 offset;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "offset = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "offset = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 address;\n"
        "address = R_n + offset;\n"
        "etiss_uint8 t:8;\n"
        "etiss_uint32 R_t;\n"
        " R_t = ((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint32 mem_fetch_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "mem_fetch_from_bitextract = (r & R_t)>>0;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_bitextract;\n"
        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,1);\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition STRH_Rt_Rn_imm5_(
	Thumb,
    "STRH",
    (uint16_t)0x8000,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Imm5 (10,6);
	etiss_uint16 imm5= Imm5.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//STRH\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm5) + " ;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 offset_addr;\n"
        "offset_addr = R_n + imm32;\n"
        "etiss_uint32 address;\n"
        " address = offset_addr;\n"
        "etiss_uint8 t:8;\n"
        "etiss_uint32 R_t;\n"
        " R_t = ((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint32 mem_fetch_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=15; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "mem_fetch_from_bitextract = (r & R_t)>>0;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_bitextract;\n"
        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,2);\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition STRH_Rt_Rn_Rm_(
	Thumb,
    "STRH",
    (uint16_t)0x5200,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rt (2,0);
	etiss_uint16 t= Rt.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//STRH\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 offset;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "offset = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "offset = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_int32 address;\n"
        "address = R_n + offset;\n"
        "etiss_uint8 t:8;\n"
        "etiss_uint32 R_t;\n"
        " R_t = ((ARMv6M*)cpu)->R[" + toString(t) + "];\n"
        "etiss_uint32 mem_fetch_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=15; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "mem_fetch_from_bitextract = (r & R_t)>>0;\n"
        "etiss_uint8 * buf = (etiss_uint8 *)&mem_fetch_from_bitextract;\n"
        "etiss_int32 Mem_address = (*(system->dwrite))(system->handle,cpu,address,buf,2);\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition SUBS_Rd_Rn_imm3_(
	Thumb,
    "SUBS",
    (uint16_t)0x1e00,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Imm3 (8,6);
	etiss_uint16 imm3= Imm3.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//SUBS\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm3) + " ;\n"
        "etiss_uint32 N_imm32;\n"
        "N_imm32 = ~imm32;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)N_imm32 + 1;\n"
        "etiss_uint64 unsigned_sum = R_n + N_imm32 + 1;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition SUBS_Rdn_imm8_(
	Thumb,
    "SUBS",
    (uint16_t)0x3800,
    (uint16_t)0xf800,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rdn (10,8);
	etiss_uint16 n= Rdn.read(ba);
    etiss_uint16 d= Rdn.read(ba);
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//SUBS\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm8) + " ;\n"
        "etiss_uint32 N_imm32;\n"
        "N_imm32 = ~imm32;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)N_imm32 + 1;\n"
        "etiss_uint64 unsigned_sum = R_n + N_imm32 + 1;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition SUBS_Rd_Rn_Rm_(
	Thumb,
    "SUBS",
    (uint16_t)0x1a00,
    (uint16_t)0xfe00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rn (5,3);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (8,6);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//SUBS\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry_out:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry_out = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry_out = t & extended_x;\n"
        "}\n"
        "etiss_uint32 N_shifted;\n"
        "N_shifted = ~shifted;\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)R_n + (etiss_int32)N_shifted + 1;\n"
        "etiss_uint64 unsigned_sum = R_n + N_shifted + 1;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= result;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -overflow ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 28);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition SUB_SP_SP_imm7_(
	Thumb,
    "SUB",
    (uint16_t)0xb080,
    (uint16_t)0xff80,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Imm7 (6,0);
	etiss_uint16 imm7= Imm7.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//SUB\n")+
        "NULL;\n"
        "etiss_uint32 imm32;\n"
        "imm32 = " + toString(imm7) + " ;\n"
        "etiss_uint32 N_imm32;\n"
        "N_imm32 = ~imm32;\n"
        "etiss_uint32 SP;\n"
        "etiss_uint32 result;\n"
        "etiss_uint8 carry:1;\n"
        "etiss_uint8 overflow:1;\n"
        "etiss_int64 signed_sum = (etiss_int32)SP + (etiss_int32)N_imm32 + 1;\n"
        "etiss_uint64 unsigned_sum = SP + N_imm32 + 1;\n"
        "etiss_uint64 tempLong = ((unsigned_sum >> 32) << 32);\n" //shift it right then left N bits, which zeroes the lower half of the long
        "etiss_uint32 unsigned_result = (etiss_uint32)(unsigned_sum - tempLong);\n"
        "etiss_int64 tempLong = ((signed_sum >> 32) << 32);\n"
        "etiss_int32 signed_result = (etiss_int32)(signed_sum - tempLong);\n"
        "if(unsigned_result == unsigned_sum)\n"
        "	carry = 0;\n"
        "else\n"
        "	carry = 1;\n"
        "if(signed_result == signed_sum)\n"
        "	overflow= 0;\n"
        "else\n"
        "	overflow = 1;\n"
        "result = unsigned_result;\n"
        "((ARMv6M*)cpu)->R[13]= result;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition SVC_imm8_(
	Thumb,
    "SVC",
    (uint16_t)0xdf00,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//SVC\n")

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition SXTB_Rd_Rm_(
	Thumb,
    "SXTB",
    (uint16_t)0xb240,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//SXTB\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "assert (0!=0);\n"
        "int m = 0%32;\n"
        "etiss_uint64 extended_x_0 = R_m;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=m; i<=m+32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result_0 = r & extended_x_0;\n"
        "etiss_uint64 extended_x_1 = R_m<<(32-m);\n"
        "unsigned t = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "result_1 = t & extended_x_1;\n"
        "rotated = result_0 | result_1;\n"
        "etiss_uint32 rotated;\n"
        "etiss_uint32 rotated_0_7;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "rotated_0_7 = (r & rotated)>>0;\n"
        "etiss_int32 reg_store_from_SignExtend;\n"
        "reg_store_from_SignExtend = rotated_0_7 ;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= reg_store_from_SignExtend;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition SXTH_Rd_Rm_(
	Thumb,
    "SXTH",
    (uint16_t)0xb200,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//SXTH\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "assert (0!=0);\n"
        "int m = 0%32;\n"
        "etiss_uint64 extended_x_0 = R_m;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=m; i<=m+32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result_0 = r & extended_x_0;\n"
        "etiss_uint64 extended_x_1 = R_m<<(32-m);\n"
        "unsigned t = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "result_1 = t & extended_x_1;\n"
        "rotated = result_0 | result_1;\n"
        "etiss_uint32 rotated;\n"
        "etiss_uint32 rotated_0_15;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=15; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "rotated_0_15 = (r & rotated)>>0;\n"
        "etiss_int32 reg_store_from_SignExtend;\n"
        "reg_store_from_SignExtend = rotated_0_15 ;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= reg_store_from_SignExtend;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition TST_Rn_Rm_(
	Thumb,
    "TST",
    (uint16_t)0x4200,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rn (2,0);
	etiss_uint16 n= Rn.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//TST\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "etiss_uint32 APSR_C;\n"
        "APSR_C = (((ARMv6M *) cpu )->APSR) >> 29 & 1 ;\n"//(number >> x) & 1;\n"
        "etiss_uint32 shifted;\n"
        "etiss_uint8 carry:1;\n"
        "if (0==0){\n"
        "shifted = R_m;\n"
        "carry = APSR_C;\n"
        "}\n"
        "else{\n"
        "assert (0>0);\n"
        "etiss_uint64 extended_x = R_m<<0;\n"
        "unsigned r = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "shifted = r & extended_x;\n"
        "unsigned t = 0;\n"
        "for (unsigned i=32; i<=32; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "carry = t & extended_x;\n"
        "}\n"
        "etiss_uint8 n:8;\n"
        "etiss_uint32 R_n;\n"
        " R_n = ((ARMv6M*)cpu)->R[" + toString(n) + "];\n"
        "etiss_uint32 result;\n"
        "result = R_n & shifted;\n"
        "etiss_uint32 field_store_from_bitextract;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=31; i<=31; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "field_store_from_bitextract = (r & result)>>31;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_bitextract ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 31);\n"//number ^= (-x ^ number) & (1 << n)
        "etiss_uint32 field_store_from_IsZeroBit;\n"
        "unsigned flag = 0;\n"
        "unsigned bit = 0;\n"
        "for(unsigned i=0; i<=32-1; i++){\n"
        "bit = (result >> i) & 1;\n"
        "if (bit==1){\n"
        "	flag = 1;\n"
        "	break;\n"
        "	}\n"
        "}\n"
        "if (flag==0)\n"
        "field_store_from_IsZeroBit = 1;\n"
        "else\n"
        "field_store_from_IsZeroBit = 0;\n"
        "((ARMv6M*)cpu)-> APSR ^= ( -field_store_from_IsZeroBit ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 30);\n"//number ^= (-x ^ number) & (1 << n)
        "((ARMv6M*)cpu)-> APSR ^= ( -carry ^ ((ARMv6M*)cpu)-> APSR ) & (1 << 29);\n"//number ^= (-x ^ number) & (1 << n)

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition UDF_imm8_(
	Thumb,
    "UDF",
    (uint16_t)0xde00,
    (uint16_t)0xff00,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Imm8 (7,0);
	etiss_uint16 imm8= Imm8.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//UDF\n")+
        "NULL;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition UDF_W_imm16_(
	Thumb,
    "UDF.W",
    (uint32_t)0xf7f0a000,
    (uint32_t)0xfff0f000,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Imm4 (19,16);
	etiss_uint16 imm4= Imm4.read(ba);
    static BitArrayRange Imm12 (11,0);
	etiss_uint16 imm12= Imm12.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//UDFW\n")+
        "NULL;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition UXTB_Rd_Rm_(
	Thumb,
    "UXTB",
    (uint16_t)0xb2c0,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//UXTB\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "assert (0!=0);\n"
        "int m = 0%32;\n"
        "etiss_uint64 extended_x_0 = R_m;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=m; i<=m+32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result_0 = r & extended_x_0;\n"
        "etiss_uint64 extended_x_1 = R_m<<(32-m);\n"
        "unsigned t = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "result_1 = t & extended_x_1;\n"
        "rotated = result_0 | result_1;\n"
        "etiss_uint32 rotated;\n"
        "etiss_uint32 rotated_0_7;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=7; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "rotated_0_7 = (r & rotated)>>0;\n"
        "etiss_uint32 reg_store_from_ZeroExtend;\n"
        "reg_store_from_ZeroExtend = rotated_0_7 ;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= reg_store_from_ZeroExtend;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition UXTH_Rd_Rm_(
	Thumb,
    "UXTH",
    (uint16_t)0xb280,
    (uint16_t)0xffc0,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
    static BitArrayRange Rd (2,0);
	etiss_uint16 d= Rd.read(ba);
    static BitArrayRange Rm (5,3);
	etiss_uint16 m= Rm.read(ba);
	CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("//UXTH\n")+
        "NULL;\n"
        "etiss_uint8 m:8;\n"
        "etiss_uint32 R_m;\n"
        " R_m = ((ARMv6M*)cpu)->R[" + toString(m) + "];\n"
        "assert (0!=0);\n"
        "int m = 0%32;\n"
        "etiss_uint64 extended_x_0 = R_m;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=m; i<=m+32-1; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "result_0 = r & extended_x_0;\n"
        "etiss_uint64 extended_x_1 = R_m<<(32-m);\n"
        "unsigned t = 0;\n"
        "for (unsigned i=0; i<=32-1; i++){\n"
        "		t |= 1 << i;\n"
        "		}\n"
        "result_1 = t & extended_x_1;\n"
        "rotated = result_0 | result_1;\n"
        "etiss_uint32 rotated;\n"
        "etiss_uint32 rotated_0_15;\n"
        "unsigned long r = 0;\n"
        "for (unsigned i=0; i<=15; i++){\n"
        "		r |= 1 << i;\n"
        "		}\n"
        "rotated_0_15 = (r & rotated)>>0;\n"
        "etiss_uint32 reg_store_from_ZeroExtend;\n"
        "reg_store_from_ZeroExtend = rotated_0_15 ;\n"
        "etiss_uint8 d:8;\n"
        "((ARMv6M*)cpu)->R[" + toString(d) + "]= reg_store_from_ZeroExtend;\n"

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition WFE_(
	Thumb,
    "WFE",
    (uint16_t)0xbf20,
    (uint16_t)0xffff,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
	    CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("// WFE\n")

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition WFI_(
	Thumb,
    "WFI",
    (uint16_t)0xbf30,
    (uint16_t)0xffff,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
	    CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("// WFI\n")

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);
static InstructionDefinition YIELD_(
	Thumb,
    "YIELD",
    (uint16_t)0xbf10,
    (uint16_t)0xffff,
    [] (BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
	{
	    CodePart & partInit = cs.append(CodePart::INITIALREQUIRED);
partInit.code() = std::string("// YIELD\n")

;
	CodePart & part2 = cs.append(CodePart::APPENDEDREQUIRED); // add a code container
	part2.getAffectedRegisters().add("instructionPointer",32);
	part2.code() = "cpu->instructionPointer = " +toString((uint32_t)(ic.current_address_+2))+"ULL;";
    return true;
},
0,
nullptr
);

