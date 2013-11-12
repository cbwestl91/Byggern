/*
 * Motor.c
 *
 * Created: 12.11.2013 13:03:21
 *  Author: raymondd
 */ 

#include <avr/io.h>
#include "Motor.h"
#include "TWI_Master.h"
#include "Servo.h"

char buf[3];
uint8_t is_inverted = 0;

//Let the coding begin!!!
void motor_init(){
	DDRA = 0xFF;
	
	buf[0] = 0x60;
	buf[1] = 0x00;
	
	TWI_Master_Initialise();
	
	PORTA |= (1 << PA7) | (1 << PB6);
	motor_enable();
}

void motor_enable(){
	PORTA |= (1 << PA4);
}

void motor_disable(){
	PORTA &= ~(1 << PA4);
}

void motor_set_direction(){
	if(is_inverted){
		PORTA |= (1 << PA3);
	} else {
		PORTA &= ~(1 << PA3);
	}
}

void motor_set_DAC_output(uint8_t value){
	motor_set_direction();
	buf[2] = value;
	
	TWI_Start_Transceiver_With_Data(buf, 3);
	
	
	printf("ARE WE EVER HERE?\n");
	if(TWI_statusReg.lastTransOK){
		printf("Message successfully sent to DAC\n");
	} else {
		volatile char state = TWI_Get_State_Info();
		printf("TWI state %c\n", state);
	}
}

void motor_send(joystick_position joy_pos){
	uint8_t motor_speed = joy_pos.x;
	if(joy_pos.x < 128 - slack){
		is_inverted = 0;
		motor_set_DAC_output(motor_speed);
	}
	else if(joy_pos.x > 128 + slack){
		is_inverted = 1;
		motor_set_DAC_output(motor_speed);
	}
	else{
		motor_set_DAC_output(0);
	}
}