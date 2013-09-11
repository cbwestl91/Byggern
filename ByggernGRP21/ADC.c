/*
 * adc.c
 *
 * Created: 11.09.2013 12:43:56
 *  Author: chriwes
 */ 
#include <avr/io.h>

void ADCTest(){
	volatile char *ext_adc = (char *) 0x1400;
	
	uint16_t i, werrors, rerrors;
	werrors = 0;
	rerrors = 0;
	unsigned char testvalue;

	printf("Starting ADC test...\r\n");

	for (i = 0; i < 0x800; i++) {
		testvalue = ~(i % 256);
		ext_adc[i] = testvalue;
	}
	printf("ADC test completed");
	
}

// 