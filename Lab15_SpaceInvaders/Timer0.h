// Timer0.h
// Runs on LM4F120 or TM4C123, 
// edX lab 15 
// Header file for the Timer0 device driver
// Loay Ashraf
// Mars 10, 2019

#include "..//tm4c123gh6pm.h"

void Timer0_Init(void (*HandlerFun) (void), unsigned long period);
