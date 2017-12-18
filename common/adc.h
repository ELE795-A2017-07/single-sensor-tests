#ifndef ADC_H
#define ADC_H

#include <cstdint>

typedef enum {
	DUST_CH = 0,
	UNUSED_1,
	O3_CH,
	O3_REF_CH,
	SOIL_RH_CH,
	TEST_CH = 7
} adc_ch_t;


const float MAX_VOLT = 5.;
const int LSB = 1024;


class Adc {
	int cs;
	int din;
	int dout;
	int clk;
	bool _on;

public:
	Adc(int cs_pin, int din_pin, int dout_pin, int clk_pin, bool on);
	~Adc(void);
	bool is_on(void);
	void on(void);
	void off(void);
	float read(bool single, uint8_t channel);
	int16_t read_raw(bool single, uint8_t channel);
};

#endif
