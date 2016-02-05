
#include "OR1KCommonLocal.hpp"

InstructionGroup ORFPX32("ORFPX32",32);

static InstructionDefinition l_add(
    ORFPX32,

    "lf.*",

    parse_i32("6x32 26x0"),

    parse_i32("6xFF 26x0"),

    [](BitArray & ba,etiss::CodeSet & cs,InstructionContext & ic)
{

	BitArrayRange all(31,0);
	uint32_t instr = all.read(ba);
    	translate_fpu(instr,cs);
    	update_pc<false,false>(ba,cs,ic);
    	return true;
},

0,

or1k_asm_print_rDAB

);

