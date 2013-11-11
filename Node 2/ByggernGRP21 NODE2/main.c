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
#include "drivers/Servo.h"

volatile uint8_t CAN_received = 0;
CANmessage received;
joystick_position joy_pos;

int main(void){
	//Initialization of UART module
	UART_init();
	
	//Initialization of CAN module
	SPI_MasterInit();
	CANInit_normal();
	
	//Initialization of PWM module
	PWM_init();
	
	//Enable interrupts
	DDRE &= ~(1 << PE4);
	cli();
	EIMSK |= (1 << INT4);
	sei();

	while(1){
		if(CAN_received == 1){
			received = CAN_read();
			printf("We are inside the interrupt! received: %d\n", received.data[0]);
			joy_pos.y = received.data[0];
			CAN_received = 0;
		}
		
		
		
		
		if(joy_pos.y > 130 && joy_pos.y < 140){
			joy_pos.y = 134;
		}
		//_delay_us(500);
		PWM_set_value(joy_pos);
	}
}

ISR(INT4_vect){
	CAN_received = 1;
}