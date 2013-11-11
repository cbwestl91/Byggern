/*
 * Servo.h
 *
 * Created: 11.11.2013 12:44:15
 *  Author: raymondd
 */ 

#ifndef SERVO_H_
#define SERVO_H_

#define max_pulse 2000
#define min_pulse 1000
#define max_control 255
#define min_control 0

typedef struct{
	uint8_t x;
	uint8_t y;
} joystick_position;

void PWM_init();
void PWM_set_value(joystick_position joy_pos);




#endif /* SERVO_H_ */