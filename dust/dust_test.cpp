#include <iostream>

#include <wiringPi.h>

#include "hwconfig.h"
#include "utils.h"
#include "adc.h"

using namespace std;


/* Returns the concentration of dust particles detected by the sensor based
 * on the value of voltage. The calculations are based on piecewise linear
 * approximations from the graph in the datasheet (figure 3, sensor Sharp GP2Y1010AU0F)
 *
 * The function extrapolates the value for voltages above the known maximum, but
 * returns -1 for voltages under the 0ug/m^3 (minimum) threshold.
 */
float dust_mgperm3_from_voltage(float voltage) {
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


int main(void) {
	wiringPiSetup();
	pullUpDnControl(DUST_LED_PIN, PUD_UP);
	pinMode(DUST_LED_PIN, OUTPUT);

	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);
	float data;

	for (int j = 0; j < 10; j++) {
		data = _adc.read(true, TEST_CH);
		cout << "Ch " << dec << TEST_CH << ": data = " << data << "V" << endl;
	}

	digitalWrite(DUST_LED_PIN, HIGH);
	digitalWrite(DUST_LED_PIN, LOW);
	busywait(280); //per datasheet, I_LED must be maintained for at least 280us

	float voltage = _adc.read(false, DUST_CH);
	cout << "Dust data = " << voltage << "V" << endl;
	cout << "Which should be about " << dust_mgperm3_from_voltage(voltage) << " mg/m^3 of dust" << endl;

	digitalWrite(DUST_LED_PIN, HIGH);

	return 0;
}
