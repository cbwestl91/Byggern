/*
 * adc.c
 *
 * Created: 11.09.2013 12:43:56
 *  Author: chriwes
 */ 
#include <avr/io.h>
#include <util/delay.h>

void ADCTest(){
	
	// THIS DOESN'T REALLY TEST ANYTHING
	// only used for checking voltage response of output pins
	volatile char *ext_adc = (char *) 0x1400;
	
	uint16_t i;
	unsigned char testvalue;

	printf("Starting ADC test...\r\n");

	for (i = 0; i < 0x800; i++) {
		testvalue = ~(i % 256);
		ext_adc[i] = testvalue;
	}
	printf("ADC test completed");
}


char ADC_read(int channel){
	volatile char *ADCmem = (char *)0x1400;


	ADCmem[0] = 0x03 + channel;
	
	//wait for filtering
	_delay_us(40);
	
	return ADCmem[0];
}		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
			/*
			//enable pins as output
			DDRD |= (1 << PD6) | (1 << PD7);
			DDRA |= (1 << PA3) | (1 << PA2) | (1 << PA1) | (1 << PA0);
			
			//write bit set low to clear out unread filtered data
			PORTD &= ~(1 << PD6);
			
			if (channel == 1){
				PORTD |= (1 << PD7); // set read bit high
				PORTA |= ~(1 << PA3) | (1 << PA2) | ~(1 << PA1) | ~(1 << PA0); // MUX input
				PORTD |= (1 << PD6); // set write bit high
				
		
		
	switch(channel){
		case 1:
			PORTD |= (1 << PD7); // set read bit high
			PORTA |= ~(1 << PA3) | (1 << PA2) | ~(1 << PA1) | ~(1 << PA0); // MUX input
			PORTD |= (1 << PD6); // set write bit high
			
			//wait for filtering
			_delay_us(40);
			
			ADCmem = (uint8_t *) 0x1400;
			break;
		case 2:
			PORTD |= (1 << PD7); // set read bit high
			PORTA |= ~(1 << PA3) | (1 << PA2) | ~(1 << PA1) | (1 << PA0); // MUX input
			PORTD |= (1 << PD6); // set write bit high
			
			//wait for filtering
			_delay_us(40);
			
			ADCmem = (uint8_t *) 0x1400;
			break;
		
		case 3:
			PORTD |= (1 << PD7); // set read bit high
			PORTA |= ~(1 << PA3) | (1 << PA2) | (1 << PA1) | ~(1 << PA0); // MUX input
			PORTD |= (1 << PD6); // set write bit high
			
			//wait for filtering
			_delay_us(40);
			
			ADCmem = (uint8_t *) 0x1400;
			break;
		
		case 4:
			PORTD |= (1 << PD7); // set read bit high
			PORTA |= ~(1 << PA3) | (1 << PA2) | (1 << PA1) | (1 << PA0); // MUX input
			PORTD |= (1 << PD6); // set write bit high
			
			//wait for filtering
			_delay_us(40);
			
			ADCmem = (uint8_t *) 0x1400;
			break;
	}
	
	return ADCmem;		
}



// */