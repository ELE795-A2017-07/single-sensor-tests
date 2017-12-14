#include <array>
#include <iostream>
#include <chrono>
#include <execinfo.h>

#include <wiringPi.h>

#include "utils.h"
#include "dht22.h"


Dht22::Dht22(int pin) {
	_pin = pin;
	pullUpDnControl(_pin, PUD_UP);
	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, 1);
}


Dht22::~Dht22() {
	digitalWrite(_pin, 0);
	pinMode(_pin, INPUT);
}


int Dht22::wait(int bit, int us_delay) {
	auto t1 = get_time_point(us_delay);

	while (digitalRead(_pin) == !bit) {
		if (t1 <= std::chrono::system_clock::now()) {
			return -1;
		}
	}
	return 0;
}

/* Returns -1 on error, 0 or 1 on success */
int Dht22::readbit() {
	int bit;

	//Wait for the line to go low (if not already), as it does before every bit
	if (wait(0, 100)) {
		return -1;
	}

	//while (!digitalRead(pin)) {}
	if (wait(1, 70)) {
		return -1;
	}
	busywait(35);

	bit = digitalRead(_pin);
	busywait(10);

	return bit;
}

/* Returns -1 on error, otherwise return the data in the 40 LSb as such:
 *   Field Name:         RHd       RHf      Td      Tf     Checksum
 *   Bit index range: [39, 32] [31, 24] [23, 16] [15, 8]    [7, 0]
 */
int64_t Dht22::read() {
	int64_t data = 0;

	pinMode(_pin, OUTPUT);
	digitalWrite(_pin, 0);
	usleep(1000);

	digitalWrite(_pin, 1);
	busywait(30);

	pinMode(_pin, INPUT);
	//while (digitalRead(pin)) {}

	//Hopefully it doesn't take more than 10us for the sensor to pull the line low
	if (wait(0, 10)) {
		return -1;
	}

	//busywait(60);
	//while (!digitalRead(pin)) {}
	if (wait(1, 100)) {
		return -1;
	}

	int MAX_BITS = 8*5;
	for (int i = MAX_BITS - 1; i > -1; i--) {
		int bit = readbit();
		if (bit < 0) {
			return -1;
		}
		data |= (int64_t(bit) << i);
	}

	return data;
}

int Dht22::check_data(int64_t data) {
	int rhi = (data >> 8*4) & 0xFF;
	int rhf = (data >> 8*3) & 0xFF;
	int ti  = (data >> 8*2) & 0xFF;
	int tf  = (data >> 8*1) & 0xFF;
	int chksum = data & 0xFF;

	return chksum == ((rhi + rhf + ti + tf) & 0xFF);
}

void Dht22::format_data(int64_t data, float& temp, float& relhum) {
	int rh = (data >> 8*3) & 0xFFFF;
	int t  = (data >> 8) & 0xFFFF;

	temp = t * 0.10;
	relhum = rh * 0.10;
}


void Dht22::print(float temp, float relhum) {
	std::cout << std::dec << "Temperature is " << temp << "°C, humidity is " << relhum << "%" << std::endl;
}
