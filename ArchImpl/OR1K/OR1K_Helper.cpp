
#include "OR1K.h"

etiss_int32 OR1KArch_mul32(OR1K * cpu,etiss_uint8 rDindex, etiss_uint32 ra, etiss_uint32 rb){
	etiss_uint64 ret;
	etiss_uint32 high, cy;

	ret = ((etiss_uint64)ra) * ((etiss_uint64)rb);

	high = (etiss_uint32)(ret >> 32);
	cy = (etiss_uint32)(ret >> (31));

	if ((cy & 0x1) == 0x0) {
		if (high == 0x0) {

			return 0;
		}
	}

	if ((cy & 0x1) == 0x1) {
		if (high == 0xffffffff) {
			return 0;
		}
	}

	*cpu->SR |= (1<<11 | 1<<10);
	if (*cpu->SR & 1<<12) {
		return OR1K_RANGEEXCEPTION;
	}

	return 0;
}
