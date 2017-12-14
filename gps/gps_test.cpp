#include <iostream>

#include <wiringPi.h>

#include "hwconfig.h"
#include "arduPi.h"
#include "TinyGPS.h"

using namespace std;

int main(void) {
	bool valid = false;
	SerialPi uart;
	TinyGPS gps;

	wiringPiSetup();
	pinMode(GPS_EN_PIN, OUTPUT);
	digitalWrite(GPS_EN_PIN, HIGH);

	uart.begin(9600);

	while (!valid) {
		char c = uart.read();
		valid = gps.encode(c);
		cout << "read character " << hex << int(c) << " (" << c << ") valid?" << valid << endl;
	}

	return 0;
}
