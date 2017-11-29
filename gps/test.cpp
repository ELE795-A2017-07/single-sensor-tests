#include <iostream>

#include "arduPi.h"
#include "TinyGPS.h"

using namespace std;

int main(void) {
	bool valid = false;
	SerialPi uart;
	TinyGPS gps;
	uart.begin(9600);

	while (!valid) {
		if (uart.available() > 0) {
			char c = uart.read();
			valid = gps.encode(c);
		} else {
			usleep(50);
		}
	}

	return 0;
}
