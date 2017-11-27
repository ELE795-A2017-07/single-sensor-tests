#ifndef ADC_H
#define ADC_H

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
	int16_t read(bool single, uint8_t channel);
};

#endif
