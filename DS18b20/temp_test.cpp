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

#include "onewire.h"

using namespace std;


const int TEMP_SENSOR_PIN = 26; //BCM 26


void init(void) {
	wiringPiSetup();
	OneWire::init(TEMP_SENSOR_PIN);
}


int main (void) {
	uint64_t rom_code;
	array<uint8_t, 9> scratchpad;
	int temp_ready = -2;

	cout << "Temp started" << endl;
	init();

	if (DEBUG) {
		OneWire::oscope_trigger();

		while (rom_code == 0) {
			rom_code = OneWire::read_rom_code();
		}

		if (rom_code == 0) {
			cout << "Sensor didn't respond" << endl;
		} else {
			cout << "Sensor responded" << endl << "rom code is " << hex << rom_code << endl;
		}
	}

	uint16_t last_temp = OneWire::E_INVALID_SCRATCH;
	uint16_t temp_val;
	for (int i = 0; i < 10; i++) {
		bool do_print = true;
		bool is_valid = false;
		temp_ready = OneWire::convert_t(nullptr);
		scratchpad = OneWire::read_scratchpad(nullptr);
		temp_val = (scratchpad[1] << 8) | scratchpad[0];

		if (temp_ready < 1) {
			do_print = false;
		} else if (!OneWire::scratch_crc_check(scratchpad)) {
			cout << "next is bogus:" << endl;
			//digitalWrite(TRIGGER_PIN, HIGH);
		} else {
			is_valid = true;
			//digitalWrite(TRIGGER_PIN, LOW);
			if (temp_val == last_temp) {
				//do_print = false;
			}
		}

		if (do_print || is_valid) {
			#define NB_REG_BITS 12
			int m = 1U << (NB_REG_BITS - 1);
			int mask = (1 << NB_REG_BITS) - 1;
			#undef NB_REG_BITS
			int tmp_temp = ((temp_val & mask) ^ m) - m;
			float temp = tmp_temp / 16.;

			//cout << "Temperature is ready? " << dec << temp_ready << endl;
			if (do_print) {
				last_temp = temp_val;
				cout << "Scratch = 0x";
				for (int i = 8; i >= 0; i--) {
					printf("%02x", scratchpad[i]);
				}
				cout << endl;
				cout << "Temperature is around " << dec << temp << endl;
			}
			if (is_valid) {
				//std::this_thread::sleep_for(SAMPLE_INTERVAL);
			}
		}
	}

	//pinMode(TEMP_SENSOR_PIN, INPUT);
	cout << "Exiting....." << endl;
	return 0;
}
