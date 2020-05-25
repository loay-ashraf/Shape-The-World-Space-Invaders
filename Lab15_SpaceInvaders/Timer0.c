// Timer0.c
// Runs on LM4F120 or TM4C123, 
// edX lab 15 
// Implementation of the Timer0 device driver
// Loay Ashraf
// Mars 10, 2019

#include "Timer0.h"

static void (*g_HandlerFun) (void);

void Timer0_Init(void (*HandlerFun) (void), unsigned long period){
	
	unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate timer0
  delay = SYSCTL_RCGCTIMER_R;
  TIMER0_CTL_R = 0x00000000;    // 1) disable timer0A during setup
  TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER0_TAILR_R = period-1;    // 4) reload value
  TIMER0_TAPR_R = 0;            // 5) bus clock resolution
  TIMER0_ICR_R = 0x00000001;    // 6) clear timer0A timeout flag
  TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI4_R = (NVIC_PRI4_R&0x0FFFFFFF)|0xA0000000; // 8) priority 5
// interrupts enabled in the main program after all devices initialized
//	NVIC_EN0_R = 1<<19;
//	TIMER0_CTL_R = 0x00000001;
	g_HandlerFun = HandlerFun;

}	

void Timer0A_Handler(void){ 
	
	TIMER0_ICR_R = 0x00000001;   // acknowledge timer0A timeout 
	g_HandlerFun();
	
}	
