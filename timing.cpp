#include <iostream>
#include <chrono>

using namespace std;

std::chrono::time_point<std::chrono::system_clock> get_time_point(int us_delay) {
	return std::chrono::system_clock::now() + std::chrono::microseconds(us_delay);
}

void busywait_until(std::chrono::time_point<std::chrono::system_clock> end_tp) {
	while (std::chrono::system_clock::now() < end_tp) {
		//Busywait, do nothing
	}
}

void busywait(int us_delay) {
	busywait_until(get_time_point(us_delay));
}


int main(void) {
	auto t0 = std::chrono::system_clock::now();
	for (int i = 0; i < 10; i++) {
		auto t1 = std::chrono::system_clock::now();
		busywait(100);
		auto t2 = std::chrono::system_clock::now();

		cout << "time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << endl;
	}
	auto te = std::chrono::system_clock::now();
	cout << "time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(te - t0).count() << endl;
	return 0;
}
