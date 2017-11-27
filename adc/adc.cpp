#include <iostream>

#include <wiringPi.h>

#include "adc.h"

Adc::Adc(int cs_pin, int din_pin, int dout_pin, int clk_pin, bool on) {
	this->_on = false;

	this->cs   = cs_pin;
	this->din  = din_pin;
	this->dout = dout_pin;
	this->clk  = clk_pin;

	if (on) {
		this->on();
	}
}

Adc::~Adc(void) {
	this->off();
}

void Adc::on(void) {
	/* If the
	 * device was powered up with the CS pin low, it must be
	 * brought high and back low to initiate communication.
	 */
	digitalWrite(this->cs, HIGH);
	digitalWrite(this->cs, LOW);
	digitalWrite(this->clk, LOW);

	this->_on = true;
}

void Adc::off(void) {
	digitalWrite(this->cs, HIGH);
	this->_on = false;
}

bool Adc::is_on(void) {
	return this->_on;
}

int16_t Adc::read(bool single, uint8_t channel) {
	int16_t data = 0;

	if (channel > 7) {
		return -1;
	}

	if (!this->is_on()) {
		this->on();
	}

	//Start bit
	digitalWrite(this->din, HIGH);
	digitalWrite(this->clk, HIGH);
	digitalWrite(this->clk, LOW);

	// SGL or ¬DIFF
	digitalWrite(this->din, int(single));
	digitalWrite(this->clk, HIGH);
	digitalWrite(this->clk, LOW);

	//D2
	digitalWrite(this->din, !!(channel & 0x4));
	digitalWrite(this->clk, HIGH);
	digitalWrite(this->clk, LOW);

	//D1
	digitalWrite(this->din, !!(channel & 0x2));
	digitalWrite(this->clk, HIGH);
	digitalWrite(this->clk, LOW);

	//D0
	digitalWrite(this->din, !!(channel & 0x1));
	digitalWrite(this->clk, HIGH);
	digitalWrite(this->clk, LOW);

	//transition
	digitalWrite(this->clk, HIGH);
	digitalWrite(this->clk, LOW);

	//NULL BIT
	digitalWrite(this->clk, HIGH);
	//digitalRead(this->dout) should give 0

	digitalWrite(this->clk, LOW);
	for (int i = 9; i > -1; i--) {
		digitalWrite(this->clk, HIGH);

		int bit = digitalRead(this->dout);
		data |= bit << i;
		digitalWrite(this->clk, LOW);
	}

	return data;
}
