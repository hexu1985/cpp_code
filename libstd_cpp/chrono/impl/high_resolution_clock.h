// -*- C++ -*-
// HeXu's
// 2013 Aug

#ifndef HX_CHRONO_HIGH_RESOLUTION_CLOCK_H
#define HX_CHRONO_HIGH_RESOLUTION_CLOCK_H

#include "steady_clock.h"

namespace Hx {

namespace chrono {

/**
 * High resolution clock
 * The members of clock classes provide access to the current time_point.
 * high_resolution_clock is the clock with the shortest tick period. 
 * It may be a synonym for system_clock or steady_clock.
 */
typedef steady_clock high_resolution_clock;

}	// namespace chrono

}	// namespace Hx

#endif

