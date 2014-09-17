# include <stdio.h>
# include "leds.h"
# include "UC-Week2-semi.h"

# define SYSAHBCLKCTRL (* (unsigned int *) 0x40048080) // Enable timer clock in component clocks register
# define TMR16B0TCR    (* (unsigned int* ) 0x4000C004) // Enable timer
# define TMR16B0TC     (* (unsigned int* ) 0x4000C008)
# define TMR16B0PR     (* (unsigned int* ) 0x4000C00C)
# define PRESC_VALUE	1000

# define TMR16B0MR0 	(* (unsigned int* )0x4000C018) // Match register
# define ISER1 			(* (unsigned int* )0xE000E104) // Enable IRQ
# define TMR16B0MCR 	(* (unsigned int* )0x4000C014) // Match Control
# define TMR16B0IR 		(* (unsigned int* )0x4000C000) // Interrupt Flag Register
# define TIMER_MATCH_VALUE	12000

static int SEC = 0;
static int MIN = 0;
static int HOURS = 0;

void initClockTimer(){
	// enable timer clock in component clocks register
	SYSAHBCLKCTRL |= 1 << 7;

	// enable timer counter
	TMR16B0TCR |= 1;
	// ensure reset is off
	TMR16B0TCR &= ~2;

	configurePR(PRESC_VALUE);
}

void configurePR(unsigned int configuration) {
	TMR16B0PR = configuration;
	// is 16-bit, dus max 65,536 clock pulsen per timer counter increment
}
void initIR(){

	TMR16B0MR0 |= TIMER_MATCH_VALUE;

	//enable IRQ
	ISER1 |= 0x200;


	TMR16B0MCR |= 3;

	// welke waarde moet het matchregister hebben
	// is deze gelijk aan de prescaler of Wanneer bit 15 hoog is.
	// Moet dan TC ook gebruikt worden, lijkt me niet want dan krijg je dezelfde code.
}

void binaryCount () {


	switch (timerDisplayState) {
	case 0:
		setLeds(SEC);
		break;
	case 1:
		setLeds(MIN);
		break;
	case 2:
		setLeds(HOURS);
		break;
	}
//	if (timerDisplayState == 0) {
//		setLeds(SEC);
//	} else if (timerDisplayState == 1) {
//		setLeds(MIN);
//	} else if (timerDisplayState == 2) {
//		setLeds(HOURS);
//	}
}

void TIMER16_0_IRQHandler(){
	countUp();
	binaryCount();
	// reset interrupt flag
	TMR16B0IR |= 1;
}

void countUp(){

	if(SEC < 59){
		SEC = SEC + 1;
	}else if(HOURS == 23 && MIN == 59 && SEC == 59){
		HOURS = 0;
		MIN = 0;
		SEC = 0;
	}else if(MIN == 59 && SEC == 59){
	HOURS = HOURS + 1;
	MIN = 0;
	SEC = 0;
	}else if(SEC == 59){
		MIN = MIN + 1;
		SEC = 0;
	}

	printClock(SEC, MIN, HOURS);


}

void printClock(int sec, int min, int hour){

	printf("%02d:%02d:%02d\n", hour, min, sec);

}
