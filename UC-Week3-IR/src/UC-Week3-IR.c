/*
===============================================================================
 Name        : UC-Week3-IR.c
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
#include "leds.h"
#include "infrared.h"
#include "timer.h"

int main(void) {
	int count = 0;
	initTimer();
	initLeds();
	initInfrared();

    while(1) {
    	// ik weet niet waarom, maar het bericht van de afstandsbediening staat een plek te ver naar links
    	// shiften dus!
    	setLeds(getCommand(readInfraredMessage()) >> 1);
//    	delay(500000);
    }
    return 0;
}
