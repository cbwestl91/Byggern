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

#include "drivers/UART.h"
#include "drivers/CAN.h"
#include "drivers/Servo.h"
#include "drivers/Motor.h"
#include "drivers/Solenoid.h"

volatile uint8_t CAN_received = 0;
volatile CANmessage received;
volatile CANmessage message;
volatile joystick_position joy_pos;

int main(void){
	//Initialization of UART module
	UART_init();
	
	//Enable interrupts
	DDRE &= ~(1 << PE4);
	//cli();
	EIMSK |= (1 << INT4);
	EICRB |= (1 << ISC41);
	
	
	//Initialization of CAN module
	SPI_MasterInit();
	CANInit_normal();
	
	//Initialization of PWM module
	PWM_init();
	
	//Initialization of ADC module
	ADC_init();
	
	//Initialization of Solenoid module
	solenoid_init();
	
	//Initialization of motor module
	sei();
	motor_init();
	
	
	while(1){
		cli();
		while(CAN_received != 0){ //If updated controller info is ready, read it into our struct
			CAN_received = 0;
			received = CAN_read();
			joy_pos.y = received.data[0];
			joy_pos.x = received.data[1];
			joy_pos.button_pressed = received.data[2];
			printf("RECEIVED MESSAGE HAD INFO ABOUT BUTTON: %d\n", joy_pos.button_pressed);
			}
		sei();
			
		//Use information available to control PWM, motor and solenoid
		if(joy_pos.y > 128 - margin && joy_pos.y < 128 + margin){
			joy_pos.y = 128;
		}
			
		if(joy_pos.button_pressed){
			solenoid_pulse(); //Apply solenoid pulse
			printf("APPLIED A PULSE!\n");
			joy_pos.button_pressed = 0;
		}
		
			
		PWM_set_value(joy_pos); //update servo
		motor_send(joy_pos); //update motor
	
	}
}

ISR(INT4_vect){
	CAN_received = 1;
}