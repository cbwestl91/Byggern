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
uint8_t button_pressed = 0;

int main(void){
	
	//Initialization of UART module
	UART_init();
	
	//Initialization of SRAM module
	SRAM_init();
	
	//Initialization of joystick
	autoCal();
	
	//Initialization of OLED
	oled_init();
	
	//Enable interrupts
	DDRD &= ~(1 << PD2);
	DDRE &= ~(1 << PE0);
	MCUCR |= (1 << ISC01);
	//EMCUCR &= ~(1 << ISC2);
	GICR |= (1 << INT0) | (1 << INT2);
	sei();
	
	
	//start execution
	//oled_home();
	
	SPI_MasterInit();
	CANInit_normal();
	
	//CAN_send(test);
	
	//_delay_ms(20);
	
	//returned = CAN_read();
	
	//printf("CAN message: %i\n", returned.data[0]);
	
	//CAN_send(test);
	//printf("CANINTF: %d\n",MCPRead(MCP_CANINTF));
	
	//_delay_ms(20);
	//returned = CAN_read();
	//printf("CAN message: %i\n", returned.data[0]);
	volatile CANmessage joystick_info;
	
	volatile position joy_pos;
	
	joystick_info.length = 3;
	joystick_info.ID = 0x00;
	
    while(1){
		//Periodical sending of joystick position
		joy_pos = joystickPos();
		
		cli();
		joystick_info.data[0] = joy_pos.y;
		joystick_info.data[1] = joy_pos.x;
		joystick_info.data[2] = button_pressed;
		button_pressed = 0;
		sei();
		
		printf("Sent CAN with info: %d %d %d\n", joystick_info.data[0], joystick_info.data[1], joystick_info.data[2]);
		CAN_send(joystick_info);

		

		
	
		_delay_ms(20);
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