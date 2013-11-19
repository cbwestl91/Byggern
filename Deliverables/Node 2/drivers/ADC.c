/*
 * ADC.c
 *
 * Created: 12.11.2013 11:39:22
 *  Author: raymondd
 */ 

#include <avr/io.h>
#include "ADC.h"

void ADC_init(){
	DDRF &= ~(1 << PF0);
	
	ADMUX |= (1 << REFS0);
	
	ADCSRA |= (1 << ADEN) | (1 << ADPS0);
	
}

int ADC_read(){
	ADCSRA |= (1 << ADSC);
	
	while(!(ADIF)){
		//Wait for completion
	}
	ADCSRA |= (1 << ADIF);
	
	int result = ADC;
	
	//printf("ADC read as: %d\n", result);
	
	return result;
}

int ADC_check_goal(){
	if(ADC_read() < goal_trigger){
		return 1;
	}
	return 0;
}