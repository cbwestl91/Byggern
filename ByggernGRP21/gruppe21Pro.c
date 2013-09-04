/*
 * gruppe21Pro.c
 *
 * Created: 03.09.2013 09:56:57
 *  Author: raymondd
 */ 


#include <avr/io.h>
#include "uartDriver.h"
#include "SRAM.h"

int main(void)
{
	
	//Initialization of UART module
	UARTinit();
	fdevopen(UARTtransmit, UARTreceive);
	
	//Initialization of SRAM module
	|MCUCR = (1 << SRE);
	|SFIOR = (1 << XMM2);
	
	SRAM_test();


    while(1){
	
	
	}
}