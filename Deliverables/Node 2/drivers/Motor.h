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

#define MOTOR_PORT PORTA
#define ENCODER_DDR DDRC
#define ENCODER_PORT PORTC

#define MOTOR_DIR PA3
#define MOTOR_EN PA4
#define MOTOR_SEL PA5
#define MOTOR_RST PA6 // !
#define MOTOR_OE PA7 // !

#define ENCODER0 PC7
#define ENCODER1 PC6
#define ENCODER2 PC5
#define ENCODER3 PC4
#define ENCODER4 PC3
#define ENCODER5 PC2
#define ENCODER6 PC1
#define ENCODER7 PC0

//Motor functions
void motor_init();
void motor_enable();
void motor_disable();
void motor_set_direction();
void motor_set_DAC_output(uint8_t value);
void motor_send(joystick_position joy_pos);

//Encoder functions
void encoder_init();
uint8_t encoder_read();
void encoder_reset();
uint8_t encoder_convert(uint8_t value);

#endif /* MOTOR_H_ */