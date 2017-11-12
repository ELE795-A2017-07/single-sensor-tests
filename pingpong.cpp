/*
 *  simple ping-pong test by requesting an ACK from the gateway
 *
 *  Copyright (C) 2016 Congduc Pham, University of Pau, France
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with the program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************
 * last update: Nov. 16th by C. Pham
 */
#include <iostream>
// Include the SX1272
#include "SX1272.h"

// edit this file to the right configuration parameters
#include "config.h"
#include "lora.h"

///////////////////////////////////////////////////////////////////
// CHANGE HERE THE LORA MODE, NODE ADDRESS
#define LORAMODE  1
#define node_addr 8
//////////////////////////////////////////////////////////////////

#define DEFAULT_DEST_ADDR 1

uint8_t message[100];

int loraMode=LORAMODE;

void setup()
{
	int e;

	// Print a start message
	std::cout << "Simple LoRa ping-pong with the gateway\n";

	// Power ON the module
	sx1272.ON();

	// Set transmission mode and print the result
	e = sx1272.setMode(loraMode);
	std::cout << "Setting Mode: state ";
	std::cout << e;
	std::cout << std::endl;

	// enable carrier sense
	sx1272._enableCarrierSense=true;

	// Select frequency channel
	e = sx1272.setChannel(DEFAULT_CHANNEL);
	std::cout << "Setting Channel: state ";
	std::cout << e;
	std::cout << std::endl;

	// Select amplifier line; PABOOST or RFO
#ifdef PABOOST
	sx1272._needPABOOST=true;
	// previous way for setting output power
	// powerLevel='x';
#else
	// previous way for setting output power
	// powerLevel='M';
#endif

	// previous way for setting output power
	// e = sx1272.setPower(powerLevel);

	e = sx1272.setPowerDBM((uint8_t)MAX_DBM);
	std::cout << "Setting Power: state ";
	std::cout << e;
	std::cout << std::endl;

	// Set the node address and print the result
	e = sx1272.setNodeAddress(node_addr);
	std::cout << "Setting node addr: state ";
	std::cout << e;
	std::cout << std::endl;

	// Print a success message
	std::cout << "SX1272 successfully configured\n";

	delay(500);
}


void loop(void)
{
	uint8_t r_size;
	int e;

	sx1272.CarrierSense();

	sx1272.setPacketType(PKT_TYPE_DATA);

	r_size=sprintf((char*)message, "Ping");

	while (1) {

			std::cout << "Sending Ping";
			std::cout << std::endl;

			e = sx1272.sendPacketTimeoutACK(DEFAULT_DEST_ADDR, message, r_size);

			// this is the no-ack version
			// e = sx1272.sendPacketTimeout(DEFAULT_DEST_ADDR, message, r_size);

			std::cout << "Packet sent, state ";
			std::cout << e;
			std::cout << std::endl;

			if (e==3)
					std::cout << "No Pong!";

			if (e==0)
					std::cout << "Pong received from gateway!";

			std::cout << std::endl;

			delay(10000);
	}
}

int main(void) {
	setup();
	while (true) {
		loop();
	}
	return 0;
}
