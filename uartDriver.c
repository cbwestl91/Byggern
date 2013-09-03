/*
 * uartDriver.c
 *
 * Created: 03.09.2013 11:42:53
 *  Author: raymondd
 */ 

#include <avr/io.h>

//#define FOSC 4915200 // clock frequency
//#define BAUD 19200 // baudrate
#define localUBRR 15

void UARTinit(){
	
	// set baud rate
	UBRR0H = (unsigned char) (localUBRR >> 8);
	UBRR0L = (unsigned char) localUBRR;
	
	// set asynchronous mode
	UCSR0C &= (0 << UMSEL0);
	
	// disable parity bits
	UCSR0C &= (0 << UPM01) | (0 << UPM00);
	
	//Enable transmitting and receiving
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	// set frame format
	UCSR0C = (1 << URSEL0) | (3 << UCSZ00) | (0 << USBS0);
	
	// double transmission speed
	UCSR0C |= (1 << U2X0);
}

void UARTtransmit(unsigned char data){
	
	/*while ( !(UCSR0A & (1 << UDRE0))){
		// Wait for empty transmission buffer
	}*/
	loop_until_bit_is_set(UCSR0A, UDRE0);
	
	// pasting data to transmission buffer
	UDR0 = data;
	
}

unsigned char UARTreceive(){
	
	/*while (!(UCSR0A & (1 << RXC0))){
		// wait for incoming transmission
	}*/
	
	loop_until_bit_is_set(UCSR0A, RXC0);
	
	return UDR0;
}