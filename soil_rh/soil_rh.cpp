#include "soil_rh.h"

namespace Soil_Rh {

soil_rh_t rh_from_voltage(float voltage) {
	if (voltage < Soil_Rh::WATER_VAL) {
		return Soil_Rh::INVALID;
	} else if (voltage < Soil_Rh::WATER_VAL + Soil_Rh::INTERVALS) {
		return Soil_Rh::VERY_WET;
	} else if (voltage < Soil_Rh::AIR_VAL - Soil_Rh::INTERVALS) {
		return Soil_Rh::WET;
	} else if (voltage <= Soil_Rh::AIR_VAL) {
		return Soil_Rh::DRY;
	}

	return Soil_Rh::INVALID;
}

};
