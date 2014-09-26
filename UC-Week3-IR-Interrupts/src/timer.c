# define SYSAHBCLKCTRL (*(unsigned int*) 0x40048080)
# define TMR16B0TCR    (*(unsigned int*) 0x4000C004)
# define TMR16B0TC     (*(unsigned int*) 0x4000C008)
# define TMR16B0PR     (*(unsigned int*) 0x4000C00C)

# define TMR16B0MR0    (*(unsigned int*) 0x4000C018) // Match register# define ISER1 		   (*(unsigned int*) 0xE000E104) // Enable IRQ# define TMR16B0MCR    (*(unsigned int*) 0x4000C014) // Match Control# define TMR16B0IR 	   (*(unsigned int*) 0x4000C000) // Interrupt Flag Register

#define TIME_PER_TICK 1 // time in usec per timer0 tick
#define PRESCALER_VALUE TIME_PER_TICK*12-1

void initTimer() {
	// enable timer clock in component clocks register
	SYSAHBCLKCTRL |= 1 << 7;

	// enable timer counter
	TMR16B0TCR |= 1;
	// ensure reset is off
	TMR16B0TCR &= ~2;

	// timer is configured to tick once per uSec
	TMR16B0PR = PRESCALER_VALUE;
//
//	// timer match value
//	TMR16B0MR0 |= 5;
//
//	//enable IRQ
//	ISER1 |= 0x200;
//	TMR16B0MCR |= 0x3;
}

unsigned short timerRead() {
	return TMR16B0TC;
}

void resetTimer() {
	// reset the timer
	TMR16B0TCR |= 0x2;
	__asm("nop");
	__asm("nop");
	// timer will remain stationary until reset flag is turned off
	TMR16B0TCR &= ~0x2;
}

//void TIMER16_0_IRQHandler() {
//	usecs += 5;
//	TMR16B0IR |= 1;
//}

void delay(unsigned int usec) {
	resetTimer();
	usec /= TIME_PER_TICK;
	while (timerRead() < usec) {
		__asm volatile("nop");
	}
}
// laatste lijn! :D
