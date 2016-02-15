//Timer.h
//Connor Lewis and Taiyi Ouyang

#include <stdint.h>

extern	uint8_t clockSeconds;
extern	uint8_t clockMinutes;
extern	uint8_t clockHours;

extern	uint8_t alarmSeconds;
extern	uint8_t alarmMinutes;
extern	uint8_t alarmHours;

void Timer0A_Init60HzInt(void);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
