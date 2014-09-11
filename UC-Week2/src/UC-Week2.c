/*
===============================================================================
 Name        : UC-Week2.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include "timer.h"
#include "leds.h"
#include <cr_section_macros.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {
	unsigned short timerValue;

	initLeds();
	initTimer();

    while(1) {
    	timerValue = timerRead();
    	if (CHECK_BIT(timerValue, 15)) {
    		setLeds(0xFF);
    	} else {
    		setLeds(0x00);
    	}
    }
    return 0 ;
}
