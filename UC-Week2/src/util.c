/*
 * util.c
 *
 *  Created on: 5 sep. 2014
 *      Author: Martijn
 */


void delay(int noops)
{
	int i;
	for (i = 0; i < noops; i++) {
		__asm("nop");
	}
}
