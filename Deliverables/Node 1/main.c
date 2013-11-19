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
#include "drivers/MCP2515.h" /* The header file MCP2515.h was written by ATMEL */
#include "drivers/sound.h"

volatile CANmessage initiate;
volatile CANmessage received; //Received messages are put here
volatile CANmessage joystick_info;
volatile position joy_pos;
volatile CAN_received = 0;


int main(void){
	//Initialization of UART module
	UART_init();
	
	//Initialization of SRAM module
	SRAM_init();
	
	//Initialization of joystick
	autoCal();
	
	//Initialization of sound module
	sound_init();
	ingame_song = POKEMON; //default is pokemon
	
	//Initialization of OLED
	oled_init();
	
	//Enable interrupts
	DDRD &= ~(1 << PD2); // PD2 <==> INT0
/*	DDRE &= ~(1 << PE0); // PE0 <==> INT2*/
	MCUCR |= (1 << ISC01);
	/*EMCUCR &= ~(1 << ISC2);*/
	GICR |= (1 << INT0);
	/*GICR |= (1 << INT0) | (1 << INT2);*/
	sei();
	
	//Enable communication
	SPI_MasterInit();
	CANInit_normal();


	//Make the CAN messages ready for use
	initiate.length = 6;
	initiate.ID = 0x00;
	initiate.data[3] = 1;

	joystick_info.length = 3;
	joystick_info.ID = 0x00;
	
	uint8_t game_over;
	
	//BE POLITE
	oled_welcome();
	
    while(1){
		game_over = 0;
		
		/* PHASE 1: PRE-GAME */
		/* MENU INTERFACING */
		oled_navigate();
		
		/* Tell node 2 that we are ready to begin */
		CAN_send(initiate);
		printf("SENT INITIATION MSG: %d\n", initiate.data[3]);
		
		/* PHASE 2: IN-GAME */
		/* Provide node 2 with input until game over msg is returned */
		printf("Entering in-game phase\n");
		sound_play(ingame_song); //Play song selected in music menu. Default is POKEMON
		while(!game_over){
			oled_clear_screen(); //To prevent the solenoid from bullying the screen
		
			joy_pos = joystickPos();
		
			joystick_info.data[0] = joy_pos.y;
			joystick_info.data[1] = joy_pos.x;
			if(joy_pos.button_pressed < button_margin){
				joystick_info.data[2] = 1;
			} else {
				joystick_info.data[2] = 0;
			}
			
			printf("SENT: %d %d %d\n", joystick_info.data[0], joystick_info.data[1], joystick_info.data[2]);
			CAN_send(joystick_info);
		
			cli();
			if(CAN_received){ //Node 2 might have information about game status
				received = CAN_read();
				CAN_received = 0;
				if(received.data[0] == 1){
					received.data[0] = 0;
					game_over = 1;
				}
			}
			sei();
			
			_delay_ms(50);
		}
		oled_game_over();
		printf("Game over detected. Going back to menu\n");
	}
	//It's funny, because... there is no exit from the endless while-loop of doom. SO YOU NEVER GET TO RETURN!
	return 0;
}

ISR(INT0_vect){
	CAN_received = 1;
	printf("RECEIVED CAN MESSAGE: \n");
}