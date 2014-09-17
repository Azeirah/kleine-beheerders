void initClockTimer();
void configurePR(unsigned int configuration);
void initIR();
void TIMER16_0_IRQHandler();
void countUp();
void printClock(int sec, int min, int hour);
