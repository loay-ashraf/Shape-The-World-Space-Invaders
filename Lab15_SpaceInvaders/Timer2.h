// Timer2.h
// Runs on LM4F120 or TM4C123, 
// edX lab 15 
// Header file for the Timer2 device driver
// Loay Ashraf
// Mars 10, 2019

void Timer2_Init(void (*HandlerFun) (void), unsigned long period);

