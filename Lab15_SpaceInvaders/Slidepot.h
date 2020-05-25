// Slidepot.h
// Runs on LM4F120 or TM4C123, 
// edX lab 15 
// Header file for Slidepot interface
// Loay Ashraf
// Mars 10, 2019

extern volatile unsigned long SlidepotPosition;
extern volatile int SlidepotPositionFlag;

void Slidepot_Init(void);
int Slidepot_Adjust(void);

