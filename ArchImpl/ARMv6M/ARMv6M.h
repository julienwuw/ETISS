#ifndef ETISS_ARMv6Arch_ARMv6M_H_
#define ETISS_ARMv6Arch_ARMv6M_H_
#include "etiss/jit/CPU.h"
#ifdef __cplusplus
extern "C" {
#endif
#pragma pack(push, 1) // important!
struct ARMv6M {
ETISS_CPU cpu; // original cpu struct must be defined as the first field of the new structure. this allows to cast X * to ETISS_CPU * and vice versa

etiss_uint32 R[16];
etiss_uint32 SPR[20];

//etiss_uint32 *MSP;
//etiss_uint32 *PSP;
etiss_uint32 SP;//R[13]

etiss_uint32 *PRIMASK;
etiss_uint32 *CONTROL;
etiss_uint32 *PSR;


//-------------------------- SYSTEM CONTROL REGISTERS-----------------------------------
//---------REGISTERS WHICH NEED SysTick timer------------------
	etiss_uint32 *SYST_CSR;
	etiss_uint32 *SYST_RVR;
	etiss_uint32 *SYST_CVR;
	etiss_uint32 *SYST_CALIB;
//--------------------------------------------------------------

etiss_uint32 *CPUID;
etiss_uint32 *ICSR; //interrupt control state register
etiss_uint32 *AIRCR; //Application interrupt and reset control register
etiss_uint32 *CCR; // configuration and control register
etiss_uint32 *SHPR2;//System handler priority register 2
etiss_uint32 *SHPR3; //System handler priority register 3
etiss_uint32 *SHCSR; //System handler control and state register
etiss_uint32 *VTOR; // vector tabel ofset register


//------------------------------------------Program Status Registers---------------------

etiss_uint32 APSR;  // bit 31= N, bit 30= Z, bit 29= C, bit 28=  V these flags should be
etiss_uint32 IPSR;
etiss_uint32 EPSR;

};




#pragma pack(pop) // undo changes
typedef struct ARMv6M ARMv6M; // convenient use of X instead of struct X in generated C code
#ifdef __cplusplus
} // extern "C"
#endif
#endif

