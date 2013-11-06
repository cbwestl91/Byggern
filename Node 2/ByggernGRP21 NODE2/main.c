/*
 * ByggernGRP21_NODE2.c
 *
 * Created: 06.11.2013 10:40:33
 *  Author: chriwes
 */ 

#include <avr/io.h>
#include "drivers/crystal.h"
#include "drivers/UART.h"
#include "drivers/CAN.h"
#include "drivers/MCP2515.h"
#include <avr/delay.h>

int main(void){
	//Initialization of UART module
	UART_init();
	
	SPI_MasterInit();
	CANInit_loopback();
	
	CANmessage test, returned;
	test.ID = 0b00000000;
	test.length = 8;
	test.data[0] = 7;

	char msg;

	while(1){
		_delay_ms(1000);
		CAN_send(test);
		_delay_ms(50);
		returned = CAN_read();
		
		//returned = CAN_read();
		

		printf("CAN RECEIVED: %d\n", returned.data[0]);


	}
}