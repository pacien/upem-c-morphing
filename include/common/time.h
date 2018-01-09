#ifndef UPEM_MORPHING_TIME
#define UPEM_MORPHING_TIME

/**
 * File: time.h
 * > Who can say where the road goes...
 * > Where the day flows, only time...
 * -- Enya
 *
 * Author:
 *   Pacien TRAN-GIRARD
 */

#include "common/geom.h"

/**
 * Constants: Time vectors
 *
 * TIME_ORIGIN - the origin of times
 * TIME_UNIT   - a unit time vector
 */
#define TIME_ORIGIN ((TimeVector) 0)
#define TIME_UNIT ((TimeVector) 1)

/**
 * Type: TimeVector
 * An abstract time vector.
 */
typedef RealVector TimeVector;

#endif
