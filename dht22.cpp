#include <array>
#include <iostream>
#include <wiringPi.h>
#include <chrono>
#include <execinfo.h>

#include "utils.h"

using namespace std;

const int TRIGGER_PIN = 7;
int bit_idx = 0;
int nb_zero_bits = 0;
int nb_one_bits = 0;


void dht22_init(const int pin) {
	pullUpDnControl(pin, PUD_UP);
	pinMode(pin, OUTPUT);
	digitalWrite(pin, 1);

	pinMode(TRIGGER_PIN, OUTPUT);
	//digitalWrite(TRIGGER_PIN, 1);
	//busywait(50);
	digitalWrite(TRIGGER_PIN, 0);
}

int dht22_wait(int pin, int bit, int us_delay) {
	static int i = 0;
	auto t1 = get_time_point(us_delay);

	while (digitalRead(pin) == !bit) {
		if (t1 <= std::chrono::system_clock::now()) {
			void *buffer[5];
			char **strings;
			int nptrs = backtrace(buffer, 5);
			cout << "dht22_wait failed after " << i << " calls while expecting bit " << bit << " (reading bit_idx " << bit_idx << "):" << endl << "  1s: " << nb_one_bits << " 0s:" << nb_zero_bits << endl;
			strings = backtrace_symbols(buffer, nptrs);
			for (int j = 0; strings != NULL && j < nptrs; j++) {
				cout << strings[j] << endl;
			}
			free(strings);
			i++;
			return -1;
		}
	}
	i++;
	return 0;
}

/* Returns -1 on error, 0 or 1 on success */
int dht22_readbit(const int pin) {
	int bit;

	//Wait for the line to go low (if not already), as it does before every bit
	if (dht22_wait(pin, 0, 100)) {
		return -1;
	}

	//while (!digitalRead(pin)) {}
	if (dht22_wait(pin, 1, 70)) {
		return -1;
	}
	busywait(35);

	digitalWrite(TRIGGER_PIN, 1);
	bit = digitalRead(pin);
	busywait(10);
	digitalWrite(TRIGGER_PIN, 0);
	if (bit) {
		nb_one_bits++;
	} else {
		nb_zero_bits++;
	}

	return bit;
}

/* Returns -1 on error, otherwise return the data in the 40 LSb as such:
 *   Field Name:         RHd       RHf      Td      Tf     Checksum
 *   Bit index range: [39, 32] [31, 24] [23, 16] [15, 8]    [7, 0]
 */
int64_t dht22_read(const int pin) {
	int64_t data = 0;
	bit_idx = 0;

	pinMode(pin, OUTPUT);
	digitalWrite(pin, 0);
	usleep(1000);

	digitalWrite(pin, 1);
	busywait(30);

	pinMode(pin, INPUT);
	//while (digitalRead(pin)) {}

	//Hopefully it doesn't take more than 10us for the sensor to pull the line low
	if (dht22_wait(pin, 0, 10)) {
		return -1;
	}

	//busywait(60);
	//while (!digitalRead(pin)) {}
	if (dht22_wait(pin, 1, 100)) {
		return -1;
	}

	//digitalWrite(TRIGGER_PIN, 1);
	//busywait(60);
	//while (digitalRead(pin)) {}
	//digitalWrite(TRIGGER_PIN, 0);

	int MAX_BITS = 8*5;
	for (int i = MAX_BITS - 1; i > -1; i--) {
		bit_idx = MAX_BITS - i;
		int bit = dht22_readbit(pin);
		if (bit < 0) {
			return -1;
		}
		data |= (int64_t(bit) << i);

		//if (bit && i > 0) {
		//	if (bit_idx == 40) {
		//		cout << "How did we get here?! i == " << dec << i << endl;
		//	}
		//	if (dht22_wait(pin, 0, 100)) {
		//		return -1;
		//	}
		//}
	}

	return data;
}

int check_data(int64_t data) {
	int rhi = (data >> 8*4) & 0xFF;
	int rhf = (data >> 8*3) & 0xFF;
	int ti  = (data >> 8*2) & 0xFF;
	int tf  = (data >> 8*1) & 0xFF;
	int chksum = data & 0xFF;

	return chksum == ((rhi + rhf + ti + tf) & 0xFF);
}

void format_data(int64_t data) {
	int rh = (data >> 8*3) & 0xFFFF;
	int t  = (data >> 8) & 0xFFFF;

	float temp = t * 0.10;
	float relhum = rh * 0.10;

	cout << dec << "Temperature is " << temp << "°C, humidity is " << relhum << "%" << endl;
}

int main(void) {
	const int DHT_PIN = 8; //BCM GPIO 3
	wiringPiSetup();

	dht22_init(DHT_PIN);
	int64_t data;
	bool first = true;
	do {
		if (first) {
			first = false;
		} else {
			cout << "fail" << endl;
			sleep(1);
		}
		data = dht22_read(DHT_PIN);
	} while (data < 0 || !check_data(data));
	cout << hex << data << endl;
	//cout << "checksum " << (check_data(data) ? "succeeded" : "failed") << endl;
	format_data(data);

	pinMode(DHT_PIN, INPUT);
	return 0;
}
