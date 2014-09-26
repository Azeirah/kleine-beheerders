/*
===============================================================================
 Name        : UC-Week3-IR-Interrupts.c
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

#include "infrared.h"
#include "leds.h"
#include "timer.h"

int main(void) {
	initLeds();
	initTimer();
	initInfrared();
    while(1) {

    }
    return 0 ;
}
