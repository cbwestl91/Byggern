/*
 * gruppe21Pro.c
 *
 * Created: 03.09.2013 09:56:57
 *  Author: raymondd
 */ 

//#define F_CPU 4915200UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "drivers/UART.h"
#include "drivers/SRAM.h"
#include "drivers/ADC.h"
#include "drivers/controller.h"
#include "drivers/OLED.h"
#include "drivers/CAN.h"
#include "drivers/MCP2515.h"

//variables
volatile uint8_t button_pressed = 0;

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
	
	//Enable interrupts
	DDRD &= ~(1 << PD2);
	DDRE &= ~(1 << PE0);
	cli();
	MCUCR |= (1 << ISC01);
	EMCUCR &= ~(1 << ISC2);
	GICR |= (1 << INT0) | (1 << INT2);
	sei();
	
	
	//start execution
	//oled_home();
	
	SPI_MasterInit();
	CANInit_normal();
	
	CANmessage test;
	test.ID = 0b00000000;
	test.length = 8;
	test.data[0] = 7;
	
	//CAN_send(test);
	
	//_delay_ms(20);
	
	//returned = CAN_read();
	
	//printf("CAN message: %i\n", returned.data[0]);
	
	//CAN_send(test);
	//printf("CANINTF: %d\n",MCPRead(MCP_CANINTF));
	
	//_delay_ms(20);
	//returned = CAN_read();
	//printf("CAN message: %i\n", returned.data[0]);
	CANmessage joystick_info;
	
	volatile position joy_pos;
	
	
	joystick_info.length = 8;
	
    while(1){
		//Periodical sending of joystick position
		joy_pos = joystickPos();
		joystick_info.ID = 0x00;
		joystick_info.data[0] = joy_pos.y;

		CAN_send(joystick_info);
		printf("Sent CAN with ID: %i\n", joystick_info.ID);
		
		_delay_ms(50);
		
	/*	joystick_info.ID = 0xFF;
		joystick_info.data[0] = joy_pos.x;
		CAN_send(joystick_info);
		printf("Sent CAN with ID: %i\n", joystick_info.ID);
		*/
	}
	
	return 0;
}

ISR(INT0_vect){
	CANmessage received = CAN_read();
	printf("We are inside the interrupt! received: %d\n", received.data[0]);
}

ISR(INT2_vect){
	button_pressed = 1;
	printf("Detected joystick press!\n");
}