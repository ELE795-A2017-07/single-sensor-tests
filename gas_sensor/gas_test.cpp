#include <iostream>

#include <wiringPi.h>

#include "adc.h"
#include "gas_sensor_o3.h"

using namespace std;

const int ADC_CS_PIN   = 22; //BCM 6
const int ADC_CLK_PIN  =  0; //BCM 17
const int ADC_DOUT_PIN =  2; //BCM 27
const int ADC_DIN_PIN  =  3; //BCM 22

int main(void) {
	wiringPiSetup();
	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);

	long vgastot = 0;
	for (int j = 0; j < 50; j++) {
		int16_t out = _adc.read(false, O3_CH);
		cout << "O3 diff = " << hex << out << " which is about " << dec << out * (5/1024.) << "V" << endl;
		vgastot += out;
		//int16_t ref = _adc.read(true, O3_REF_CH);
		//float o3_ppm = gas_ppm_from_vgas(out * (5/1024.)., ref * (5/1024.), GAS_VOFFSET, GAS_O3, -83.36);
		//cout << "O3 ref data = " << hex << ref << " which should be about " << dec << ref * (5/1024.) << "V" << endl;
		//cout << "O3     data = " << hex << out << " which should be about " << dec << out * (5/1024.) << "V" << endl;
		//cout << "PPM = " << o3_ppm << endl;
	}
	float vgasmoy = (vgastot / 50.) * (5/1024.);
	float o3_ppm = gas_ppm_from_vgas(vgasmoy, 0, GAS_VOFFSET, GAS_O3, -83.36);
	cout << dec << o3_ppm << " ppm" << endl;

	return 0;
}
