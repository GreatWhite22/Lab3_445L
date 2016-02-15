//Timer.C
//Connor Lewis and Taiyi Ouyang
//Interrupts every second and updates the clock values

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

#include <stdint.h>
#include "PLL.h"
#include "tm4c123gh6pm.h"
#include "Display.h"

#define PF2             (*((volatile uint32_t *)0x40025010))
#define PF1             (*((volatile uint32_t *)0x40025008))
#define CLOCK_SPEED			80000000

	uint8_t clockSeconds;
	uint8_t clockMinutes;
	uint8_t clockHours;

	uint8_t alarmSeconds;
	uint8_t alarmMinutes;
	uint8_t alarmHours;

void Timer0A_Init60HzInt(void){
  volatile uint32_t delay;
  //DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD; //x02
  TIMER0_TAILR_R = (CLOCK_SPEED / 60) - 1; // start value for 60 Hz interrupts subtract one because we count down to 0
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt, x01
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag, x01
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts, x01
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
  NVIC_EN0_R |= 1<<19;              // enable interrupt 19 in NVIC
}
void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
	clockSeconds += 1;
	if(clockSeconds == 60){
		clockSeconds = 0;
		clockMinutes += 1;
		if(clockMinutes == 60){
			clockMinutes = 0;
			clockHours += 1;
		}
		if(clockHours == 13){
			clockHours = 1;
		}
	}
	drawClockHands(clockHours, clockMinutes, 1);
	if(alarmHours == clockHours && alarmMinutes == clockMinutes){
		
	}
	 PF2 ^= 0x04;                   // profile
	
	
}
