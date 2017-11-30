#include <iostream>

#include <wiringPi.h>

#include "adc.h"

using namespace std;

#define ADC_CS_PIN   22 //BCM 6
#define ADC_DIN_PIN  12 //BCM 10
#define ADC_DOUT_PIN 13 //BCM 9
#define ADC_CLK_PIN  14 //BCM 11

int main(void) {
	wiringPiSetup();
	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);

	pinMode(10, OUTPUT);
	digitalWrite(10, HIGH);

	int16_t data;

	for (int i = 0; i < 10; i++) {
		data = _adc.read(true, 1);
		cout << "data = " << hex << data << " which should be about " << dec << data * (5/1024.) << "V" << endl;
	}

	return 0;
}
