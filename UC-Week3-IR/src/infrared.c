/*
 * infrared.c
 *
 *  Created on: 17 Sep 2014
 *      Author: MB
 */
#define GPIO0DATA  (* (unsigned int*) 0x50003FFC)
#define GPIO0DIR   (* (unsigned int*) 0x50008000)

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#include "leds.h"
#include "timer.h"
#include "util.h"

#define BITTIME 1778

void initInfrared() {
	// placebo init function, doesn't do anything, but it's there for developers so they can be
	// sure the infrared functionality is properly initialized :')
	GPIO0DIR &= ~(1 << 8);
}

unsigned char readIRBit() {
	return CHECK_BIT(~GPIO0DATA, 8) >> 8;
}

void blockUntilMessage() {
	while (readIRBit() == 0) {
		delay(5);
	}
}

unsigned short readInfraredMessage() {

	// ???
	// lees 14 bits
	// de afstandsbediening stuurt er 28 met een tussenpoos van 24.9/28 milli seconden
	// --00 0000 0000 0000
	// --11 ---- ---- ---- altijd hoog
	// ---- x--- ---- ---- toggle bit, als de knop ingedrukt blijft wordt deze om-en-om hoog naar laag naar hoog naar ...
	// ---- -xxx xx-- ---- adres, aangezien wij maar met een apparaat werken is dit altijd hetzelfde en hoeven we er niet naar te kijken
	// ---- ---- --xx xxxx ingedrukte knop
	unsigned short message = 0x3000;
	blockUntilMessage();
	delay(BITTIME*2);
	for (char i = 12; i > 0; i--) {
		message |= readIRBit() << i;
		delay(BITTIME);
	}
	return message;
}

unsigned char getCommand(unsigned short message) {
	return message & 0x3F;
}
