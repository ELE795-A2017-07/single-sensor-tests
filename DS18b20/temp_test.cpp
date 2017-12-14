#include <iostream>
#include <fstream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <array>
#include <thread>
#include <sstream>
#include <iomanip>

#include <wiringPi.h>

#include "hwconfig.h"
#include "DS18b20.h"
#include "onewire.h"

using namespace std;


int main (void) {
	uint64_t rom_code;

	wiringPiSetup();
	DS18b20 temp_sensor(TEMP_SENSOR_PIN);

	if (DEBUG) {
		while (rom_code == 0) {
			rom_code = temp_sensor.read_rom_code();
		}

		if (rom_code == 0) {
			cout << "Sensor didn't respond" << endl;
		} else {
			cout << "Sensor responded" << endl << "rom code is " << hex << rom_code << endl;
		}
	}

	for (int i = 0; i < 10; i++) {
		float temp = temp_sensor.read_new_temperature();
		cout << dec << i << ". Temperature is around " << temp << endl;
	}

	return 0;
}
