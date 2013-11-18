/*
 * ByggernGRP21_NODE2.c
 *
 * Created: 06.11.2013 10:40:33
 *  Author: chriwes
 */ 

#include "drivers/crystal.h"

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "drivers/ADC.h"
#include "drivers/UART.h"
#include "drivers/CAN.h"
#include "drivers/Servo.h"
#include "drivers/Motor.h"
#include "drivers/Solenoid.h"

volatile uint8_t CAN_received = 0;
volatile CANmessage received;
volatile CANmessage message;

int main(void){
	//Initialization of UART module
	UART_init();
	
	//Enable interrupts
	DDRE &= ~(1 << PE4);
	EIMSK |= (1 << INT4);
	EICRB |= (1 << ISC41);
	sei();
	
	//Initialization of CAN module
	SPI_MasterInit();
	CANInit_normal();
	
	//Initialization of PWM module
	PWM_init();
	
	//Initialization of ADC module
	ADC_init();
	
	//Initialization of Solenoid module
	solenoid_init();
	
	//Initialization of Motor module
	motor_init();
	
	//Variables
	uint8_t ready = 0;
	uint8_t game_over = 0;
	uint8_t some_counter = 0;
	
	//This is where new received joystick values are stored
	joystick_position joy_pos;
	
	message.length = 1;
	message.ID = 0x01;
	
	while(1){
		/* PHASE 0: INITIALIZATION */
		ready = 0;
		game_over = 0;
		joy_pos.x = 128;
		joy_pos.y = 128;
		joy_pos.button_pressed = 0;
		
		//Set to some start value
		PWM_set_value(joy_pos);
		motor_send(joy_pos);
		
		/* PHASE 1: PRE-GAME */
		/* Wait for node 1 to make contact */
		printf("Waiting for node 1 to initiate game\n");
		while(!ready){
			if(CAN_received){
				received = CAN_read();
				CAN_received = 0;
				
				if(received.data[3] == 1){
					received.data[3] = 0;
					ready = 1;
				}
			}
			
			
		}
		printf("Established contact!\n");
		printf("Starting game\n");

		/* PHASE 2: IN-GAME */
		/* Follow input over CAN and return a message when we have a game over. It is not a matter of if, only when! */
		
		while(!game_over){
			//cli(); //Interrupts are disabled while we read from the CAN bus. Bad values were sometimes introduced otherwise
			
			if(CAN_received){ //If updated controller info is ready, read it into our struct
				received = CAN_read();
				CAN_received = 0;
				joy_pos.y = received.data[0];				//first spot contains y value
				joy_pos.x = received.data[1];				//second spot contains x value
				joy_pos.button_pressed = received.data[2];  //third spot contains button value
			}
			
			if(joy_pos.y > 128 - margin && joy_pos.y < 128 + margin){
				joy_pos.y = 128; //This is done to avoid noisy PWM input
			}
			
			/* Apply new numbers to the system */
			//Use information available to control PWM, motor and solenoid
			
			if(joy_pos.button_pressed){
				solenoid_pulse(); //Apply solenoid pulse
				joy_pos.button_pressed = 0;
			}
			
			PWM_set_value(joy_pos); //update servo
			motor_send(joy_pos); //update motor
		
			if(ADC_check_goal()){ //Evaluates to 1 if goal is detected
				some_counter++;
				
				if(some_counter == 20){
					some_counter = 0;
					game_over = 1; //Start procedure all over
					CAN_reset();
					
					//Tell node 1 about the failure
					message.data[0] = 1;
					CAN_send(message);
				}
				
			}
		
			//sei(); //Allow interrupts to occur
			
			_delay_ms(20);
		}
		/* GAME ENDED. WAIT FOR NEW ONE TO START */
	}
}

ISR(INT4_vect){
	printf("RECEIVED A MESSAGE\n");
	CAN_received = 1;
}