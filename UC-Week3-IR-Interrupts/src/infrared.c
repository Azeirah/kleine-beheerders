/*
 * infrared.c
 *
 *  Created on: 17 Sep 2014
 *      Author: MB
 */
#define GPIO0DATA  (* (unsigned int*) 0x50003FFC)
#define GPIO0DIR   (* (unsigned int*) 0x50008000)

#define ISER0      (* (unsigned int*) 0xE000E100) // interrupt enable
#define ISER1      (* (unsigned int*) 0xE000E104)
#define GPIO0IS    (* (unsigned int*) 0x50008004) // interrupt sense register
#define GPIO0IEV   (* (unsigned int*) 0x5000800C) // interrupt event register
#define GPIO0IE    (* (unsigned int*) 0x50008010)
#define GPIO0IC    (* (unsigned int*) 0x5000801C)
#define GPIO0IBE   (* (unsigned int*) 0x50008008)

#define PIO0_8 0x0100;

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#include "leds.h"
#include "timer.h"
#include "leds.h"

static short message         = 0x0000;
static char  RC5rising       = 0;
static char  RC5middle       = 1;
static int   messageLocation = 13;

void initInfrared() {
	GPIO0DIR &= ~(1 << 8);

	// enables the intterupt line for PIOINT0_IRQHandler, via interrupts of PIO0_8
	GPIO0IE |= PIO0_8;

	// sets PIO0_8 interrupt to be edge sensitive (instead of level sensitive)
	GPIO0IS &= ~PIO0_8;

	// sets PIO0_8 to interrupt on both rising and falling edges
	GPIO0IBE |= PIO0_8;
	ISER1   |= 0x1000000;
}

unsigned char readIRBit() {
	return CHECK_BIT(~GPIO0DATA, 8) >> 8;
}

unsigned char getCommand(unsigned short message) {
	return message & 0x3F;
}

void PIOINT0_IRQHandler() {
	int timer = timerRead();

	RC5rising = !RC5rising;

	// timer around 889 uSec
	if (timer > 700 && timer < 1100 && messageLocation != 13) {
		RC5middle = !RC5middle;
	}

	if (RC5rising && RC5middle) {
		message |= 1 << messageLocation--;
	} else if (!RC5rising && RC5middle) {
		message &= ~(1 << messageLocation--);
	}

	if (messageLocation == -1) {
		// invert message since IR receiver is inverted
		int command = getCommand(message) - 1;
		setLeds(1 << command);
		delay(50000);
		messageLocation = 13;
		RC5rising       = 0;
		RC5middle       = 1;
		message         = 0x0000;

	}

	//# reset interrupt
	GPIO0IC |= PIO0_8;
	__asm("nop");
	__asm("nop");
	//# end reset
	resetTimer();
}
