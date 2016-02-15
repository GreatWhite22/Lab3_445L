#include <stdint.h>
#include "tm4c123gh6pm.h"

#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define PF0                     (*((volatile uint32_t *)0x40025004))
#define PF4                     (*((volatile uint32_t *)0x40025040))
#define PORTA                     (*((volatile uint32_t *)0x40004080))
#define SWITCHES                (*((volatile uint32_t *)0x40025044))
#define SW1       0x10                      // on the left side of the Launchpad board
#define SW2       0x01                      // on the right side of the Launchpad board


void Switch_Init(void){ 
  SYSCTL_RCGCGPIO_R |= 0x00000001;     // 1) activate clock for Port A
  while((SYSCTL_PRGPIO_R&0x01) == 0){};// ready?
  GPIO_PORTA_AMSEL_R &= ~0x38;      // 3) disable analog on PA5,PA4,PA3
  GPIO_PORTA_PCTL_R &= ~0x00F00000; // 4) PCTL GPIO on PA5
  GPIO_PORTA_DIR_R &= ~0x38;        // 5) direction PA5,PA4,PA3 input
  GPIO_PORTA_AFSEL_R &= ~0x38;      // 6) PA5,PA4,PA3 regular port function
  GPIO_PORTA_DEN_R |= 0x38;         // 7) enable PA5,PA4,PA3 digital port
}

//
//PA5 is 0x20
//PA4 is 0x80
//PA3 is 0x40
//
uint32_t PortA_Input (void){
	return PORTA;
}

