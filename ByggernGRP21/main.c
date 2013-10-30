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
#include "drivers/CAN.h"
#include "drivers/MCP2515.h"

#include <util/delay.h>


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
	
	
	//start execution
	//oled_home();
	
	SPI_MasterInit();
	CANInit_loopback();
	
	CANmessage test, returned;
	test.ID = 0b00000000;
	test.length = 8;
	test.data[0] = 1;
	
	CAN_send(test);
	
	_delay_ms(20);
	
	returned = CAN_read();
	
	printf("CAN message: %i\n", returned.data[0]);
	
	CAN_send(test);
	//printf("CANINTF: %d\n",MCPRead(MCP_CANINTF));
	
	_delay_ms(20);
	returned = CAN_read();
	printf("CAN message: %i\n", returned.data[0]);
	
    while(1){
	
	}
	
	return 0;
}