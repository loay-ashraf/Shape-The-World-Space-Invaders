// Timer1.c
// Runs on LM4F120 or TM4C123, 
// edX lab 15 
// Implementation of the Timer2 device driver
// Loay Ashraf
// Mars 10, 2019

#include "Timer1.h"
#include "..//tm4c123gh6pm.h"

static void (*g_HandlerFun) (void);

void Timer1_Init(void (*HandlerFun) (void), unsigned long period){ 
	
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate timer1
  delay = SYSCTL_RCGCTIMER_R;
  TIMER1_CTL_R = 0x00000000;    // 1) disable timer1A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = period-1;    // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_ICR_R = 0x00000001;    // 6) clear timer1A timeout flag
  TIMER1_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF)|0x00006000; // 8) priority 3
// interrupts enabled in the main program after all devices initialized
// vector number 37, interrupt number 21
  NVIC_EN0_R = 1<<21;           // 9) enable IRQ 21 in NVIC
  TIMER1_CTL_R = 0x00000001;    // 10) enable timer1A
	g_HandlerFun = HandlerFun;
	
}
void Timer1A_Handler(void){ 
	
  TIMER1_ICR_R = 0x00000001;   // acknowledge timer1A timeout
	g_HandlerFun();
	
}
