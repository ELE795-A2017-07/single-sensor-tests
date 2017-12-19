#ifndef DUST_SENSOR_H
#define DUST_SENSOR_H

#include "adc.h"

class Dust_sensor {
	Adc *p_adc;
	int led_pin;
	int channel;

public:
	float dust_mgperm3_from_voltage(float voltage);
	Dust_sensor(Adc *p_adc, int led_pin, int channel);
	~Dust_sensor();
	float read_voltage();
	float read();
};

#endif /* Guard */
