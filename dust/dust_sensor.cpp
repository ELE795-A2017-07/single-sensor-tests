#include <wiringPi.h>

#include "utils.h"
#include "dust_sensor.h"

/* Returns the concentration of dust particles detected by the sensor based
 * on the value of voltage. The calculations are based on piecewise linear
 * approximations from the graph in the datasheet (figure 3, sensor Sharp GP2Y1010AU0F)
 *
 * The function extrapolates the value for voltages above the known maximum, but
 * returns -1 for voltages under the 0ug/m^3 (minimum) threshold.
 */
float Dust_sensor::dust_mgperm3_from_voltage(float voltage) {
	if (voltage < 0.589625) {
		//The curve hits 0 mg/m^3 at 0.589625V, so...
		return -1;
	} else if (voltage <= 1.983375) {
		return 0.177404*voltage - 0.103140;
	} else if (voltage <= 2.934375) {
		return 0.161099*voltage - 0.070802;
	} else if (voltage <= 3.15) {
		return 0.127834*voltage + 0.026812;
	} else if (voltage <= 3.440625) {
		return 0.187483*voltage - 0.161084;
	} else if (voltage <= 3.590625) {
		return 0.282051*voltage - 0.486458;
	} else if (voltage <= 3.634375) {
		return 1.450549*voltage - 4.682097;
	} else if (voltage <= 3.65625) {
		return 4.864469*voltage - 17.08956;
	} else {
		//The curve has no point for V > 3.65625
		//return std::numeric_limits<float>::infinity();
		return 0.6961538462;
	}
}


Dust_sensor::Dust_sensor(Adc *p_adc, int led_pin, int channel) {
	this->p_adc = p_adc;
	this->led_pin = led_pin;
	this->channel = channel;

	pullUpDnControl(this->led_pin, PUD_UP);
	pinMode(this->led_pin, OUTPUT);
}


Dust_sensor::~Dust_sensor() {
	digitalWrite(this->led_pin, HIGH);
}


float Dust_sensor::read_voltage() {
	digitalWrite(this->led_pin, HIGH);
	digitalWrite(this->led_pin, LOW);
	busywait(280); //per datasheet, I_LED must be maintained for at least 280us

	float voltage = (this->p_adc)->read(false, this->channel);
	return voltage;
}


float Dust_sensor::read() {
	float voltage = read_voltage();
	return dust_mgperm3_from_voltage(voltage);
}
