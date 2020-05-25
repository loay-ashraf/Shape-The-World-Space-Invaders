

#include "SysTick.h"
#include "..//tm4c123gh6pm.h"

static void (*g_HandlerFun) (void);

void SysTick_Init(void (*HandlerFun) (void), unsigned long period){

	NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
  NVIC_ST_RELOAD_R = period-1;// reload value
  NVIC_ST_CURRENT_R = 0;      // any write to current clears it
  NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1      
  NVIC_ST_CTRL_R = 0x0007;  // enable SysTick with core clock and interrupts
	
	g_HandlerFun = HandlerFun;
}

void SysTick_Handler(void){  // runs at frequency of SysTick interrupts
	
	g_HandlerFun();

}

