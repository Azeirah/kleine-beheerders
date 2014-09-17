/*
===============================================================================
 Name        : UC-Week2-V0.2.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include <cr_section_macros.h>
#include <stdio.h>

#include "timer.h"
#include "leds.h"
#include "clock.h"
#include "buttons.h"
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int timerDisplayState = 0;

int main(void) {
	char buttons;
	initLeds();
	initClockTimer();
	initIR();
	initButtons();

	ledsWriteRGB(0x001);

    while(1) {

    	buttons = readButtons();
    	if (CHECK_BIT(buttons, 0) || CHECK_BIT(buttons, 1) || CHECK_BIT(buttons, 2)) {
    		if (CHECK_BIT(buttons, 0)) {
    		    timerDisplayState = 0;
    		    ledsWriteRGB(0x001);
    		} else if (CHECK_BIT(buttons, 1)) {
    		    timerDisplayState = 1;
    		    ledsWriteRGB(0x002);
    		} else if (CHECK_BIT(buttons, 2)) {
    			timerDisplayState = 2;
    			ledsWriteRGB(0x004);
    		}
    	}

    }
    return 0 ;
}
