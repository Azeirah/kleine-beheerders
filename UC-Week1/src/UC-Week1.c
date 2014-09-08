/*
===============================================================================
 Name        : UC-Week1.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC13xx.h"
#endif

#include <stdint.h>
#include "leds.h"
#include "buttons.h"
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

#include <cr_section_macros.h>

int main(void) {
	initLeds();
	initButtons();

	char direction = 1;
	char currentLed = 0;
	char buttons = readButtons();

    while(1) {
    	buttons = readButtons();
    	toggleRGB(buttons & 0x0F);
    	if (CHECK_BIT(buttons, 3)) {
    		direction = direction == 1 ? 0 : 1;
    	}
    	if (direction == 1 && currentLed == 7) {
    		direction = 0;
    	} else if (direction == 0 && currentLed == 0) {
    		direction = 1;
    	}
    	incrementLeds(direction, &currentLed);
    	delay(200000);
    }
    return 0 ;
}
