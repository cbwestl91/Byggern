/*
 * gruppe21Pro.c
 *
 * Created: 03.09.2013 09:56:57
 *  Author: raymondd
 */ 

//#define F_CPU 4915200UL

#include <avr/io.h>
#include "uartDriver.h"
#include "SRAM.h"
#include "ADC.h"
#include "controllerDriver.h"
#include "OLED.h"

int main(void)
{
	/*
	//Initialization of UART module
	UARTinit();
	fdevopen(UARTtransmit, UARTreceive);
	*/
	//Initialization of SRAM module
	MCUCR |= (1 << SRE);
	SFIOR |= (1 << XMM2);
	
	init_program();
	//oled_print();


    while(1){
		
		
	}
}