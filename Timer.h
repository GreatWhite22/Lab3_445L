//Timer.h
//Connor Lewis and Taiyi Ouyang

#include <stdint.h>

//static struct Clock {
//	uint8_t seconds;
//	uint8_t minutes;
//	uint8_t hours;
//}Clock;

void Timer0A_Init60HzInt(void);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
