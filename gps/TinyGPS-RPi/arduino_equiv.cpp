#include <chrono>
#include "arduino_equiv.h"

unsigned long millis(void) {
	auto n = std::chrono::system_clock::now();
	return n.time_since_epoch().count();
}
