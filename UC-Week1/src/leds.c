#include <stdint.h>
// Direction, Input/Output
#define GPIO_2_DIR ((unsigned int*)0x50028000 )
// State of pins, High/Low
#define GPIO_2_DATA ((unsigned int*)0x50023FFC)

#include "util.h"

void initLeds()
{
    // setting led pins as outputs
	unsigned int *dir = GPIO_2_DIR;
	unsigned int *data = GPIO_2_DATA;
	*dir = 0xFFF;
	*data &= ~1;
}

void setLeds(unsigned char ledMask)
{
	/*
	 * Takes an 8-bit ledMask for leds 0-7
	 * 8765 4321
	 * 0000 0000
	 *
	 */
	unsigned int *data = GPIO_2_DATA;
	*data = ~(ledMask << 1) & ~1;
}

void ledsWriteRGB(unsigned char rgb) {
	unsigned int *data = GPIO_2_DATA;
	*data = ~(rgb << 9) & ~1;
}

void toggleRGB(char rgb)
{
	unsigned int *data = GPIO_2_DATA;
	// permissions to write to 0000 1110 0000 0000
	*data ^= 0x0E00 & (rgb << 9);
}

void incrementLeds(char direction, char *currentLed)
{
	// vergeef me voor de redundancy Thijs
	unsigned int *data = GPIO_2_DATA;
	*data |= 0x01FE;
	if (direction == 0) {
		*data &= ~(1 << *currentLed) << 1;
		*currentLed = *currentLed - 1;
	} else if (direction == 1) {
		*data &= ~(1 << *currentLed) << 1;
		*currentLed = *currentLed + 1;
	}
}

void toggleLeds(char leds, char direction)
{
	unsigned int *data = GPIO_2_DATA;
	// permissions to write to 0000 0001 1111 1110
	*data ^= 0x01FE & (leds << 1);
}

void kitt()
{
	char i;
	unsigned char delayTime = 1000000;
	for (i = 0; i < 8; i++) {
		setLeds(i);
		delay(delayTime);
	}
	for (i = 1; i < 7; i++) {
		setLeds(0x80 >> i);
		delay(delayTime);
	}
}

void shineOnMe()
{
	unsigned int *data = GPIO_2_DATA;
	*data = ~0xFFF;
}
