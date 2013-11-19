/*
 * Servo.c
 *
 * Created: 11.11.2013 12:44:02
 *  Author: raymondd
 */ 

#include <avr/io.h>
#include "Servo.h"
#include "UART.h"

void PWM_init(){
	
	//Mode set according to table 61 in ATmega128 datasheet
	TCCR1A |= (1 << WGM11) | (1 << COM1B1);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);
	
	//Define top value
	ICR1 = 20000;
	
	DDRB |= (1 << PB6);
}

void PWM_set_value(joystick_position joy_pos){
	float multiplier = (max_pulse - min_pulse) / 255.00;
	int value = (joy_pos.y * multiplier) + min_pulse;
	
	if (value < min_pulse || value > max_pulse){
		printf("ERROR: Out of range: %d and %d", min_pulse, max_pulse);
	}
	else{
		OCR1B = value;
	}	
}