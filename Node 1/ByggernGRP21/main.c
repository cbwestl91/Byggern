/*
 * gruppe21Pro.c
 *
 * Created: 03.09.2013 09:56:57
 *  Author: raymondd
 */ 

#define F_CPU 4915200UL

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "drivers/UART.h"
#include "drivers/SRAM.h"
#include "drivers/ADC.h"
#include "drivers/controller.h"
#include "drivers/OLED.h"
#include "drivers/SPI.h"
#include "drivers/CAN.h"
#include "drivers/MCP2515.h"


volatile CANmessage received; //Received messages are put here
volatile CANmessage joystick_info;
volatile int game_over = 0;
volatile position joy_pos;
int main(void){
	
	//Initialization of UART module
	UART_init();
	
	//Initialization of SRAM module
	SRAM_init();
	
	//Initialization of joystick
	autoCal();
	
	//Initialization of OLED
	oled_init();
	button_pressed = 0; //Make sure button variable isn't some mad value
	
	//Enable interrupts
	DDRD &= ~(1 << PD2); // PD2 <==> INT0
	DDRE &= ~(1 << PE0); // PE0 <==> INT2
	MCUCR |= (1 << ISC01);
	EMCUCR &= ~(1 << ISC2);
	GICR |= (1 << INT0) | (1 << INT2);
	sei();
	
	//Enable communication
	SPI_MasterInit();
	CANInit_normal();

	joystick_info.length = 3;
	joystick_info.ID = 0x00;
	
	
	
    while(1){
		//BE POLITE
		oled_welcome();
		
		//HANDLE OLED AND ALLOW INTERFACING
		oled_navigate();
		
		
		//PLAY SOME! YAY
		while(!game_over){
			oled_clear_screen();

			//Periodical sending of joystick position
			joy_pos = joystickPos();
			joystick_info.data[0] = joy_pos.y;
			joystick_info.data[1] = joy_pos.x;
			joystick_info.data[2] = button_pressed;
			/*if(button_pressed){
				_delay_ms(500);
				GIFR |= (1 << INTF2);
			}*/
			
			button_pressed = 0;
			
		
			printf("Sent CAN with info: %d %d %d\n", joystick_info.data[0], joystick_info.data[1], joystick_info.data[2]);
			CAN_send(joystick_info);
			
			_delay_ms(100);
		}

	}
	
	//It's funny, cus... there is no exit from the endless while-loop of doom. SO YOU NEVER GET TO RETURN. BWAHAHAHA!
	return 0;
}

ISR(INT0_vect){
	received = CAN_read();
	printf("RECEIVED CAN MESSAGE: %d\n", received.data[0]);
	
	if(received.data[0] == 1){
		game_over = 1;
	}
}

ISR(INT2_vect){
	button_pressed = 1;
}