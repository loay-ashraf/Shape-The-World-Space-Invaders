// Button.c
// Runs on LM4F120 or TM4C123, 
// edX lab 15 
// Implementation of the Button device driver
// Loay Ashraf
// Mars 10, 2019

#include "Button.h"
#include "LED.h"
#include "Sound.h"
#include "Sprite.h"
#include "..//tm4c123gh6pm.h"

void Button_Init(void){
	
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= 0x00000010; // (a) activate clock for port E
	delay = SYSCTL_RCGC2_R;
  GPIO_PORTE_DIR_R &= ~0x03;    // (b) make PF4 in (built-in button)
  GPIO_PORTE_AFSEL_R &= ~0x03;  //     disable alt funct on PE0,PE1
  GPIO_PORTE_DEN_R |= 0x03;     //     enable digital I/O on PE0,PE1
  GPIO_PORTE_PCTL_R &= ~0x000000FF; //  configure PF4 as GPIO
  GPIO_PORTE_AMSEL_R &= ~0x03;  //    disable analog functionality on PE0,PE1
  GPIO_PORTE_PUR_R |= 0x03;     //     enable weak pull-up on PE0,PE1
  GPIO_PORTE_IS_R &= ~0x03;     // (c) PE0,PE1 is edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x03;    //     PE0,PE1 is not both edges
  GPIO_PORTE_IEV_R &= ~0x03;    //     PE0,PE1 falling edge event
  GPIO_PORTE_ICR_R = 0x03;      // (d) clear flag0,1
  GPIO_PORTE_IM_R |= 0x03;      // (e) arm interrupt on PE0,PE1
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x00000060; // (g) priority 3
  NVIC_EN0_R = 1<<4;      // (f) enable interrupt 4 in NVIC
	
}

void GPIOPortE_Handler(void){
	
	if(GPIO_PORTE_RIS_R & 0x01){
		GPIO_PORTE_ICR_R = 0x01; 	// acknowledge flag0
		Sprite_MissileAttack();		// ordinary missile attack
		LED_ON(1);
	}else if(GPIO_PORTE_RIS_R & 0x02){
		GPIO_PORTE_ICR_R = 0x02; 				// acknowledge flag1
		Sprite_SpecialMissileAttack();  // special missile attack
		LED_ON(1);
	}	
	Sound_Shoot();	// output shooting sound
}

