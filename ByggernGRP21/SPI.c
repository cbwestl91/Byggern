/*
 * SPI.c
 *
 * Created: 18.10.2013 11:32:01
 *  Author: chriwes
 */ 

#include "avr/io.h"

void SPI_MasterInit(){
	//MOSI and SCK output, others input
	DDRB = (1 << DDB5) | (1 << DDB7);
	//Enable SPI, Master, set clock rate 
	SPCR = (1 << SPE) | (1 << MSTR) | ();
}