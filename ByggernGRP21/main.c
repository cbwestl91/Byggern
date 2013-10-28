/*
 * gruppe21Pro.c
 *
 * Created: 03.09.2013 09:56:57
 *  Author: raymondd
 */ 

//#define F_CPU 4915200UL

#include <avr/io.h>
#include "drivers/UART.h"
#include "drivers/SRAM.h"
#include "drivers/ADC.h"
#include "drivers/controller.h"
#include "drivers/OLED.h"


int main(void){
	//Initialization of UART module
	UART_init();
	
	//Initialization of SRAM module
	SRAM_init();
	
	//Initialization of joystick
	autoCal();
	
	printf("%i, %i\n", offsetX, offsetY);
	
	//Initialization of OLED
	oled_init();
	
	
	
	MCPWrite();
	
	
	//start execution
	//oled_home();
	
    while(1){
	
	}
	
	return 0;
}