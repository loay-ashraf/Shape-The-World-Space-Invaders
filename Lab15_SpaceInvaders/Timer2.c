// Timer2.c
// Runs on LM4F120 or TM4C123, 
// edX lab 15 
// Implementation of the Timer2 device driver
// Loay Ashraf
// Mars 10, 2019

#include "Timer2.h"
#include "..//tm4c123gh6pm.h"

static void (*g_HandlerFun) (void);

void Timer2_Init(void (*HandlerFun) (void), unsigned long period){ 
	
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  delay = SYSCTL_RCGCTIMER_R;
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
	g_HandlerFun = HandlerFun;
	
}
void Timer2A_Handler(void){ 
	
  TIMER2_ICR_R = 0x00000001;   // acknowledge timer2A timeout
	g_HandlerFun();
	
}

