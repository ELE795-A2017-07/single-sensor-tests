#include "gas_sensor_o3.h"

float gas_ppm_from_vgas(const float vgas, const float vref, const float voffset, target_gas_t gas, const float sens_code) {
	/*Per datasheet, this should be calibrated in a clean room,
	 * for each sensor, but 0 is a good first approximation */
	float vgas0 = vref + voffset;
	float M = sens_code * GAS_TIA_GAIN_ARR[gas] * 1E-9 * 1E3;
	float cx = 1 / M * (vgas - vgas0);
	return cx;
}
