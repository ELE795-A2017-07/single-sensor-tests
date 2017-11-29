#include "arduPi.h"

int main(void) {
	SerialPi uart;
	uart.begin(9600);

	return 0;
}
