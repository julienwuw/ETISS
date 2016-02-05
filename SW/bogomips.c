#include "print.h"

float bogomips (void) {
  if (_cust_time_us() != (unsigned)-1) {
    unsigned loops = 1;
    while ((loops <<= 1)) {
      unsigned ticks, ii;
      ticks = _cust_time_us();
      for (ii = loops; ii > 0; ii--);
      ticks = _cust_time_us() - ticks;
      if (ticks >= 10000000)
        return (1.0 * loops / ticks) * (10000000 / 500000.0);
    }
  }
  return -1.0;
}
