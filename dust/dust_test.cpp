#include <iostream>

#include <wiringPi.h>

#include "hwconfig.h"
#include "utils.h"
#include "adc.h"
#include "dust_sensor.h"

using namespace std;


int main(void) {
	wiringPiSetup();

	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);
	Dust_sensor ds(&_adc, DUST_LED_PIN, DUST_CH);
	float data;

	for (int j = 0; j < 10; j++) {
		data = _adc.read(true, TEST_CH);
		cout << "Ch " << dec << TEST_CH << ": data = " << data << "V" << endl;
	}

	float voltage = ds.read_voltage();
	cout << "Dust data = " << voltage << "V" << endl;
	cout << "Which should be about " << ds.dust_mgperm3_from_voltage(voltage) << " mg/m^3 of dust" << endl;

	return 0;
}
