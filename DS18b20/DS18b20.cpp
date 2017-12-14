#include "onewire.h"
#include "DS18b20.h"


#define NB_REG_BITS 12


DS18b20::DS18b20(int pin) {
	_pin = pin;
	_conv_done = false;
	_conv_in_progress = false;
	OneWire::init(_pin);
}

DS18b20::~DS18b20() {
}


uint64_t DS18b20::read_rom_code() {
	return OneWire::read_rom_code();
}


void DS18b20::start_conversion() {
	_conv_done = false;
	_conv_in_progress = true;

	_conversion();
}


bool DS18b20::is_conversion_done() {
	_conversion();
	return _conv_done;
}


void DS18b20::_conversion() {
	bool ret = false;

	if (_conv_in_progress) {
		ret = OneWire::convert_t(nullptr);
	}

	if (ret) {
		_conv_in_progress = false;
		_conv_done = true;
		_scratchpad = OneWire::read_scratchpad(nullptr);
	}
}


float DS18b20::read_temperature() {
	_conversion();

	if (!_conv_done) {
		return std::numeric_limits<float>::quiet_NaN();
	}

	_valid = OneWire::scratch_crc_check(_scratchpad);
	if (!_valid) {
		return std::numeric_limits<float>::quiet_NaN();
	}

	int16_t temp_val = (_scratchpad[1] << 8) | _scratchpad[0];
	int m = 1U << (NB_REG_BITS - 1);
	int mask = (1 << NB_REG_BITS) - 1;
	int tmp_temp = ((temp_val & mask) ^ m) - m;
	float temp = tmp_temp / 16.;

	return temp;
}


float DS18b20::read_new_temperature() {
	start_conversion();

	while (!is_conversion_done()) { }

	return read_temperature();
}
