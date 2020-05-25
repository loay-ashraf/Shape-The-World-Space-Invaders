// Slidepot.c
// Runs on LM4F120 or TM4C123, 
// edX lab 15 
// Implementation of Slidepot interface
// Loay Ashraf
// Mars 10, 2019

#include "Slidepot.h"
#include "ADC.h"
#include "Timer2.h"

void Scan(void){
	
	unsigned long result;
	result = (ADC0_In()/4095.0)*66;
	
	if(SlidepotPosition != result && SlidepotPositionFlag == 0){
		
		if(result > SlidepotPosition)
			
			SlidepotPosition += 1;
		
		else if(result < SlidepotPosition)
			
			SlidepotPosition -= 1;
		
		SlidepotPositionFlag = 1;
		
	}

}	

void Slidepot_Init(void){
	
	SlidepotPosition = 32;
	ADC0_Init();
	Timer2_Init(&Scan, 80000000/1000);		// 1 kHz
	
}

int Slidepot_Adjust(void){
	
	unsigned long result;
	result = (ADC0_In()/4095.0)*66;
	
	return (result > 26 && result < 38);

}

