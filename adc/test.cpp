#include <iostream>

#include <wiringPi.h>

#include "adc.h"

using namespace std;

#define ADC_CS_PIN   22 //BCM 6
#define ADC_CLK_PIN   0 //BCM 17
#define ADC_DOUT_PIN  2 //BCM 27
#define ADC_DIN_PIN   3 //BCM 22

int main(void) {
	wiringPiSetup();
	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);

	int16_t data;

	for (int i = 0; i < 10; i++) {
		data = _adc.read(true, 1);
		cout << "data = " << hex << data << " which should be about " << dec << data * (5/1024.) << "V" << endl;
	}

	return 0;
}
