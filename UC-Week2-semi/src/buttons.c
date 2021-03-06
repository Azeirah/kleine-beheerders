#include <stdint.h>
// Direction, Input/Output
#define GPIO_3_DIR ((unsigned int*) 0x50038000)
// State of pins, High/Low
#define GPIO_3_DATA ((unsigned int*) 0x50033FFC)

void initButtons() {
	// the default direction is actually input, but let's assign the buttons
	// a nice zero regardless.
	unsigned int *dir = GPIO_3_DIR;
	*dir = 0x0;
}

unsigned char readButtons() {
	unsigned int *data = GPIO_3_DATA;
	unsigned char buttons = *data & 0xF;
	return ~buttons;
}
