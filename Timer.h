//Timer.h
//Connor Lewis and Taiyi Ouyang

void Timer0A_Init60HzInt(void);
void Timer0A_Handler(void);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts