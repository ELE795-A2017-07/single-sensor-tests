#include <iostream>

#include <wiringPi.h>

#include "hwconfig.h"
#include "adc.h"

using namespace std;

int main(void) {
	wiringPiSetup();
	int test_in[] = {TEST_CH, O3_CH, O3_REF_CH, -1};
	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);
	float data;

#if 0

	for (int j = 0; test_in[j] > -1; j++) {
		for (int i = 0; i < 10; i++) {
			data = _adc.read(true, test_in[j]);
			switch (test_in[j]) {
			case TEST_CH:
			case O3_CH:
			case O3_REF_CH:
				cout << "Ch " << dec << test_in[j] << ": data = " << hex << data << " which should be about " << dec << data * (5/1024.) << "V" << endl;
				break;
			default:
				cout << "unhandled channel " << test_in[j] << " selected" << endl;
				break;
			}
		}
	}
#else
	for (int j = 0; j < 10; j++) {
		data = _adc.read(true, TEST_CH);
		cout << "Ch " << dec << TEST_CH << ": data = " << data << "V" << endl;
	}
#endif

	return 0;
}
