/*
 * Motor.c
 *
 * Created: 12.11.2013 13:03:21
 *  Author: raymondd
 */ 

#include "crystal.h"

#include <avr/io.h>
#include <util/delay.h>

#include "Motor.h"
#include "TWI_Master.h"
#include "Servo.h"

void motor_init(){
	DDRA = 0xFF; //PORTA <==> motor connections
	
	TWI_Master_Initialise();
	
	MOTOR_PORT |= (1 << MOTOR_OE) | (1 << MOTOR_RST);
	motor_enable();
}

void motor_enable(){
	MOTOR_PORT |= (1 << MOTOR_EN);
}

void motor_disable(){
	MOTOR_PORT &= ~(1 << MOTOR_EN);
}

void motor_set_DAC_output(uint8_t motor_speed){
	unsigned char buf[4];
	
	buf[0] = 0x50;
	buf[1] = 0x00;
	buf[2] = motor_speed;

	TWI_Start_Transceiver_With_Data(buf, 3);

	if(TWI_statusReg.lastTransOK){
		printf("Message successfully sent to DAC\n");
	} else {
	}
}

void motor_send(joystick_position joy_pos){
	int motor_speed = 2*joy_pos.x-128;
	if(motor_speed<0){
		motor_speed=-motor_speed;
	}

	if(joy_pos.x < 128 - slack){
		MOTOR_PORT &= ~(1 << MOTOR_DIR);
		motor_set_DAC_output(motor_speed);
	}
	else if(joy_pos.x > 128 + slack){
		MOTOR_PORT |= (1 << MOTOR_DIR);
		motor_set_DAC_output(motor_speed);
	}
	else{
		motor_set_DAC_output(0);
	}
}

uint8_t bit_reverse(uint8_t bits){ //Since cable is inverted, we need to reverse the received data
	uint8_t out = bits;
	out = (out & 0xaa) >> 1 | (out & 0x55) << 1; // Simple method discussed on stackoverflow.com
	out = (out & 0xcc) >> 2 | (out & 0x33) << 2;
	out = (out & 0xf0) >> 4 | (out & 0x0f) << 4;
	
	return out;
}

void encoder_init(){
	MOTOR_PORT &= ~(1 << MOTOR_OE);
	
	encoder_reset();
}

uint8_t encoder_read(){
	uint8_t encoder_value = PINC;
	
	return bit_reverse(encoder_value);
}

void encoder_reset(){
	MOTOR_PORT &= ~(1 << MOTOR_RST);
	
	_delay_ms(10);
	
	MOTOR_PORT |= (1 << MOTOR_RST);
}