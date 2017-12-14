#ifndef GAS_SENSOR_O3_H
#define GAS_SENSOR_O3_H

/* Values taken from the table in ULPSM-03-968-005 datasheet */
typedef enum {
	GAS_CO, //Carbon monoxide
	GAS_H2S, //Hydrogen sulfide
	GAS_NO2, //Nitrogen dioxide
	GAS_SO2, //Sulfur dioxide
	GAS_O3, //Ozone
	GAS_ETHANOL, //Ethanol (C2H5OH)
	GAS_INAIR, //Indoor Air Quality
	GAS_RESP_IRRITANTS, //Respiratory irritants
	/* Add items here */
	GAS_NB_ITEMS //Should always be the last element, used for loops
} target_gas_t;

const float GAS_TIA_GAIN_ARR[] = {
	100,  //GAS_CO
	49.9, //GAS_H2S
	499,  //GAS_NO2
	100,  //GAS_SO2
	499,  //GAS_O3
	249,  //GAS_ETHANOL
	100,  //GAS_INAIR
	499   //GAS_RESP_IRRITANTS
};

const float GAS_VOFFSET = 0;

/* Returns the gas concentration, in PPM
 * Vgas is the value (in Volts) of the sensor Vgas output
 * Vref is the value (in Volts) of the sensor Vref output
 * voffset is the offset value (in Volts) due to the background current in the sensor (see datasheet). Use GAS_VOFFSET if unknown.
 * gas is the name of the gas, used to index into the GAS_TIA_GAIN_ARR array
 * sens_code is the sensor-specific sensitivity code (in nA/ppm) that is written on the sensor itself.
 *   It is the last number in the list, see datasheet for more info. For our test O3 sensor, the value is -83.36
 */
float gas_ppm_from_vgas(const float vgas,
		const float vref,
		const float voffset,
		target_gas_t gas,
		const float sens_code);

#endif
