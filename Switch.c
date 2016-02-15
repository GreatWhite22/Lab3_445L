#include <stdint.h>
#include "tm4c123gh6pm.h"

#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define PF0                     (*((volatile uint32_t *)0x40025004))
#define PF4                     (*((volatile uint32_t *)0x40025040))
#define PORTF                     GPIO_PORTF_DATA_R
#define SWITCHES                (*((volatile uint32_t *)0x40025044))
#define SW1       0x10                      // on the left side of the Launchpad board
#define SW2       0x01                      // on the right side of the Launchpad board


void Switch_Init(void){ 
  SYSCTL_RCGCGPIO_R |= 0x00000020;     // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R&0x01) == 0){};// ready?
	GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlock Port F
	GPIO_PORTF_CR_R = 0x1F;
  GPIO_PORTF_AMSEL_R &= ~0xF;      // 3) disable analog on PA5,PA4,PA3,PA2
  GPIO_PORTF_PCTL_R &= 0x00000000; // 4) PCTL GPIO on PA5
  GPIO_PORTF_DIR_R &= ~0xF;        // 5) direction PA5,PA4,PA3,PA2 input
  GPIO_PORTF_AFSEL_R &= ~0xF;      // 6) PA5,PA4,PA3,PA2 regular port function
  GPIO_PORTF_DEN_R |= 0xF;         // 7) enable PA5,PA4,PA3,PA2 digital port
}

//
//PF3 is 0x8
//PF2 is 0x4
//PF1 is 0x2
//PF0 is 0x1
//
uint32_t portF_Input (void){
	uint32_t input = 0;
	if(PORTF && 0x01 == 0x01){
		return input;
	}
	else if(PORTF && 0x02 == 0x02){
		return input;
	}
	else if(PORTF && 0x04 == 0x04){
		return input;
	}
	else if(PORTF && 0x08 == 0x08){
		return input;
	}
	return input;
}

