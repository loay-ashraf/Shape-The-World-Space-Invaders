

#include "LED.h"
#include "..//tm4c123gh6pm.h"

void LED_Init(void){
	unsigned long volatile delay;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
  delay = SYSCTL_RCGC2_R;    					// allow time to finish activating
  GPIO_PORTB_AMSEL_R &= ~0x30;      // no analog 
  GPIO_PORTB_PCTL_R &= ~0x00FF0000; // regular function
	GPIO_PORTB_DR8R_R |= 0x30;			// 8mA drive
  GPIO_PORTB_DIR_R |= 0x30;      // make PB5-4 out
  GPIO_PORTB_AFSEL_R &= ~0x30;   // disable alt funct on PB5-4
  GPIO_PORTB_DEN_R |= 0x30;      // enable digital I/O on PB5-4
}

void LED_ON(int led){
	GPIO_PORTB_DATA_R |= 1<<(led+4);
}

void LED_OFF(int led){
	GPIO_PORTB_DATA_R &= ~(1<<(led+4));
}

