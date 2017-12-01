#include <iostream>

#include <wiringPi.h>

#include "adc.h"
#include "gas_sensor_o3.h"

using namespace std;

const int ADC_CS_PIN   = 22; //BCM 6
const int ADC_CLK_PIN  =  0; //BCM 17
const int ADC_DOUT_PIN =  2; //BCM 27
const int ADC_DIN_PIN  =  3; //BCM 22

typedef enum {
	DUST_CH = 0,
	UNUSED_1,
	O3_CH,
	O3_REF_CH,
	SOIL_RH_CH,
	TEST_CH = 7
} adc_ch_t;

int main(void) {
	wiringPiSetup();
	int test_in[] = {TEST_CH, O3_CH, O3_REF_CH, -1};
	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);

	int16_t data;

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
		cout << "Ch " << dec << TEST_CH << ": data = " << hex << data << " which should be about " << dec << data * (5/1024.) << "V" << endl;
	}

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
#endif

	return 0;
}
