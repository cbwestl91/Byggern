/*
 * Motor.h
 *
 * Created: 12.11.2013 13:03:28
 *  Author: raymondd
 */ 
#include "Servo.h"

#ifndef MOTOR_H_
#define MOTOR_H_

#define slack 20

#define DAC_ADRESS 0x1F
#define DAC_OUTPUT 0x00
#define DAC_OUTPUT_RESET 0x10

void motor_init();
void motor_enable();
void motor_disable();
void motor_set_direction();
void motor_set_DAC_output(uint8_t value);
void motor_send(joystick_position joy_pos);

#endif /* MOTOR_H_ */