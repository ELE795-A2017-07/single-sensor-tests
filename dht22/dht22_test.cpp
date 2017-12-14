#include <array>
#include <iostream>
#include <wiringPi.h>
#include <chrono>
#include <execinfo.h>

#include "hwconfig.h"
#include "utils.h"
#include "dht22.h"

using namespace std;

int main(void) {
	wiringPiSetup();
	Dht22 dht22(DHT_PIN);

	int64_t data;
	float temp, relhum;
	bool first = true;
	do {
		if (first) {
			first = false;
		} else {
			cout << "fail" << endl;
			sleep(1);
		}
		data = dht22.read();
	} while (data < 0 || !Dht22::check_data(data));
	cout << hex << data << endl;
	//cout << "checksum " << (check_data(data) ? "succeeded" : "failed") << endl;
	Dht22::format_data(data, temp, relhum);
	Dht22::print(temp, relhum);

	return 0;
}
