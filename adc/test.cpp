#include <iostream>

#include <wiringPi.h>

#include "adc.h"

using namespace std;

const int ADC_CS_PIN   = 22; //BCM 6
const int ADC_CLK_PIN  =  0; //BCM 17
const int ADC_DOUT_PIN =  2; //BCM 27
const int ADC_DIN_PIN  =  3; //BCM 22

int main(void) {
	wiringPiSetup();
	int test_in[] = {TEST_CH, O3_CH, O3_REF_CH, -1};
	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);


#if 0
	int16_t data;

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
		cout << "Ch " << dec << TEST_CH << ": data = " << hex << data << " which should be about " << dec << data * (5/1024.) << "V" << endl;
	}
#endif

	return 0;
}
