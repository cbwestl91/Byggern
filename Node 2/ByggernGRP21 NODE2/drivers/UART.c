/*
 * uartDriver.c
 *
 * Created: 03.09.2013 11:42:53
 *  Author: raymondd
 */ 


//CLOCK: 513kHz * 16 = 8.2MHz


#include <avr/io.h>
#include <avr/sfr_defs.h>

#define FOSC 8200000 // clock frequency
#define BAUD 19200 // baudrate
#define localUBRR FOSC/16/BAUD-1

void UARTtransmit(unsigned char data){

	loop_until_bit_is_set(UCSR0A, UDRE0);
	
	// passing data to transmission buffer
	UDR0 = data;
}

unsigned char UARTreceive(){
		
	loop_until_bit_is_set(UCSR0A, RXC0);
	
	return UDR0;
}

void UART_init(){
	
	// set baud rate
	/*
	UBRR0H = (unsigned char) (localUBRR >> 8);
	UBRR0L = (unsigned char) localUBRR;*/
	UBRR0L = localUBRR;
	
	
	// set asynchronous mode
	UCSR0C &= ~(1 << UMSEL0);
	
	// disable parity bits
	UCSR0C &= ~((1 << UPM01) | (1 << UPM00));
	
	//Enable transmitting and receiving
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	// set frame format
	UCSR0C = (1 << USBS) | (3 << UCSZ00);
	
	fdevopen(UARTtransmit, UARTreceive);
}