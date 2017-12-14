#ifndef DHT22_H
#define DHT22_H

class Dht22 {
	int _pin;

	int readbit();

public:
	Dht22(int pin);
	~Dht22(void);
	int wait(int bit, int us_delay);
	int64_t read();
	static int check_data(int64_t data);
	static void format_data(int64_t data, float& temp, float& relhum);
	static void print(float temp, float relhum);
};

#endif /* Guard */
