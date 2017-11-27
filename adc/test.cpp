#include <iostream>

#include <wiringPi.h>

#include "adc.h"

using namespace std;

#define ADC_CS_PIN   16 //BCM 15
#define ADC_DIN_PIN  12 //BCM 10
#define ADC_DOUT_PIN 13 //BCM 9
#define ADC_CLK_PIN  14 //BCM 11

int main(void) {
	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);
	digitalWrite(10, HIGH);

	int16_t data = _adc.read(true, 0);
	cout << "data = " << hex << data << endl;

	return 0;
}
