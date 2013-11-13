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

unsigned char buf[4];
volatile uint8_t is_inverted = 0;

void motor_init(){
	DDRA = 0xFF;
	
	TWI_Master_Initialise();
	
	PORTA |= (1 << PA7) | (1 << PA6);
	motor_enable();
}

void motor_enable(){
	PORTA |= (1 << PA4);
}

void motor_disable(){
	PORTA &= ~(1 << PA4);
}

void motor_set_DAC_output(uint8_t motor_speed){
	buf[0] = 0x50;
	buf[1] = 0x00;
	buf[2] = motor_speed;

	TWI_Start_Transceiver_With_Data(buf, 3);

	if(TWI_statusReg.lastTransOK){
		printf("Message successfully sent to DAC\n");
	} else {
		//unsigned char state = TWI_Get_State_Info();
		//printf("TWI state %c\n", state);
	}
}

void motor_send(joystick_position joy_pos){
	//uint8_t motor_speed = 100;
	int motor_speed = 2*joy_pos.x-128;
	if(motor_speed<0){
		motor_speed=-motor_speed;
	}
	printf("Motorspeed: %i", motor_speed);
	if(joy_pos.x < 128 - slack){
		PORTA &= ~(1 << PA3);
		motor_set_DAC_output(motor_speed);
	}
	else if(joy_pos.x > 128 + slack){
		PORTA |= (1 << PA3);
		motor_set_DAC_output(motor_speed);
	}
	else{
		motor_set_DAC_output(0);
	}
}