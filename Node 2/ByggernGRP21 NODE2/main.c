/*
 * ByggernGRP21_NODE2.c
 *
 * Created: 06.11.2013 10:40:33
 *  Author: chriwes
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include "drivers/crystal.h"
#include "drivers/UART.h"
#include "drivers/CAN.h"
#include "drivers/MCP2515.h"


int main(void){
	//Initialization of UART module
	UART_init();
	
	SPI_MasterInit();
	CANInit_normal();
	
	//Enable interrupts
	DDRE &= ~(1 << PE4);
	EIMSK |= (1 << INT4);
	sei();
	
	
	CANmessage test, returned;
	test.ID = 0b00000001;
	test.length = 8;
	test.data[0] = 5;

	char msg;

	while(1){
		_delay_ms(50);
	}
}

ISR(INT4_vect){
	CANmessage received = CAN_read();
	printf("We are inside the interrupt! received: %d\n", received.data[0]);
}