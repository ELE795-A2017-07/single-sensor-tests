#ifndef DS18B20_H
#define DS18B20_H

#include <array>

class DS18b20 {
	std::array<uint8_t, 9> _scratchpad;
	int _pin;
	bool _conv_done;
	bool _conv_in_progress;
	bool _valid;

	void _conversion();

public:
	DS18b20(int pin);
	~DS18b20();
	float read_temperature();
	bool is_conversion_done();
	void start_conversion();
	uint64_t read_rom_code();
	float read_new_temperature();
};

#endif
