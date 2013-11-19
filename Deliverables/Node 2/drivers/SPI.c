/*
 * SPI.c
 *
 * Created: 18.10.2013 11:32:01
 *  Author: chriwes
 */ 

#include "avr/io.h"

void SPI_MasterInit(){
	
	//Set MOSI, SCK and SS as output, others as input
	DDRB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
	
	//Set SS high
	PORTB |= (1 << PB0);
	
	//Enable SPI, Master, set clock rate 
	SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void SPI_MasterTransmit(char data){
	
	//Start transmission
	SPDR = data;
	
	//Wait for completion
	while(!(SPSR & (1 << SPIF)));
}

volatile char SPI_MasterRead(){
	
	
	//Start transmission
	SPDR = 0;
		
	//Wait for completion
	while(!(SPSR & (1 << SPIF)));
	//Deliver contents of the data register
	return SPDR;
}