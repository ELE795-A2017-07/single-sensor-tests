#include <iostream>

#include <wiringPi.h>

#include "hwconfig.h"
#include "adc.h"
#include "soil_rh.h"

using namespace std;

int main(void) {
	wiringPiSetup();
	Adc _adc = Adc(ADC_CS_PIN, ADC_DIN_PIN, ADC_DOUT_PIN, ADC_CLK_PIN, true);

	for (int j = 0; j < 50; j++) {
		int16_t out = _adc.read(true, SOIL_RH_CH);
		float val = out * (5/1024.);
		cout << "Soil RH = " << hex << out << " which is about " << dec << val << "V" << endl;
		Soil_Rh::soil_rh_t rh_type = Soil_Rh::rh_from_voltage(val);

		switch (rh_type) {
		case Soil_Rh::VERY_WET:
			cout << "  Very wet" << endl;
			break;
		case Soil_Rh::WET:
			cout << "  Wet" << endl;
			break;
		case Soil_Rh::DRY:
			cout << "  Dry" << endl;
			break;
		default:
			cout << "  ??" << endl;
		}
	}

	return 0;
}
