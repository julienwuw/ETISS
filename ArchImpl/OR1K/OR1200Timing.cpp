#include "etiss/Timing.h"


etiss::Plugin * getOR1200Timing(etiss::Configuration & cfg)
{

    etiss::DataSheetAccurateTiming * ret = new etiss::DataSheetAccurateTiming(
        "or1200::datasheettiming",
        make_tuple(std::regex(".*"),std::regex("32"),std::regex("l\\.(?!((div)|(mul))).*"),&etiss::DataSheetAccurateTiming::handleMatch_cycles<1,true>), // all l.XXX instruction need 1 cycle except div and mul instructions
        make_tuple(std::regex(".*"),std::regex("32"),std::regex("l\\.mul.*"),&etiss::DataSheetAccurateTiming::handleMatch_cycles<3,true>), // multiplication takes 3 cycles
        make_tuple(std::regex(".*"),std::regex("32"),std::regex("l\\.div.*"),&etiss::DataSheetAccurateTiming::handleMatch_cycles<32,true>), // division takes 32 cycles
        make_tuple(std::regex(".*"),std::regex("32"),std::regex("lf\\.((add)|(sub))\\..*"),&etiss::DataSheetAccurateTiming::handleMatch_cycles<10,true>), // float add/sub takes 10 cycles
        make_tuple(std::regex(".*"),std::regex("32"),std::regex("lf\\.mul\\..*"),&etiss::DataSheetAccurateTiming::handleMatch_cycles<38,true>), // float mul takes 38 cycles
        make_tuple(std::regex(".*"),std::regex("32"),std::regex("lf\\.madd\\..*"),&etiss::DataSheetAccurateTiming::handleMatch_cycles<38+10,true>), // float mul and add is assumed to take 38+10 cycles (not explicitly in the OR1200 timing table)
        make_tuple(std::regex(".*"),std::regex("32"),std::regex("lf\\.div\\..*"),&etiss::DataSheetAccurateTiming::handleMatch_cycles<37,true>), // float div takes 37 cycles
        make_tuple(std::regex(".*"),std::regex("32"),std::regex("lf\\.sf.*"),&etiss::DataSheetAccurateTiming::handleMatch_cycles<2,true>), // float compare takes 2 cycles
        make_tuple(std::regex(".*"),std::regex("32"),std::regex("lf\\..to.\\..*"),&etiss::DataSheetAccurateTiming::handleMatch_cycles<7,true>) // float conversion takes 7 cycles
    );

    // ther are additional cycles pre instruction due to stalls (cache, bus etc.)
    int ifStallCycles = cfg.get<int>("ifStallCycles",0);
    if (ifStallCycles > 0)
    {
        std::string code = std::string("cpu->cpuTime_ps += ") + etiss::toString(ifStallCycles) + " * cpu->cpuCycleTime_ps; //additional stalls per instruction\n";
        ret->addRule(make_tuple(std::regex(".*"),std::regex(".*"),std::regex(".*"),
                                std::function<void (etiss::instr::Instruction &)> ([code](etiss::instr::Instruction & instr)
        {
            instr.addCallback(
                [code](etiss::instr::BitArray & ba,etiss::CodeSet & cs,etiss::instr::InstructionContext & ic)
            {
                etiss::CodePart & cp = cs.prepend(etiss::CodePart::INITIALREQUIRED);
                cp.getAffectedRegisters().add("cpuTime_ps",64);
                cp.code() = code;

                return true;
            },
            0
            );
        }
                                                                                  )
                               )
                    );
    }

    return ret;

}




