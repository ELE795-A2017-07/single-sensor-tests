#ifndef SOIL_RH_H
#define SOIL_RH_H

namespace Soil_Rh {

typedef enum {
	INVALID,
	VERY_WET,
	WET,
	DRY,
	/* Add items here */
	NB_ITEMS //Should always be the last element, used for loops
} soil_rh_t;

/* Based on experimental calibration, the offsets are to allow for
 * some noise since these are taken as boundary values */
const float WATER_VAL = 1.37695 - 0.03; //0x11a
const float AIR_VAL = 2.52441 + 0.03; //0x205

const float INTERVALS = (AIR_VAL - WATER_VAL)/3;

soil_rh_t rh_from_voltage(float voltage);

};

#endif
