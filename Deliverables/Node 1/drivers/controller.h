/*
 * controllerDriver.h
 *
 * Created: 11.09.2013 15:19:33
 *  Author: chriwes
 */ 


#ifndef CONTROLLERDRIVER_H_
#define CONTROLLERDRIVER_H_

/* CHANNEL DEFINES:
	channel 1 -> Y
	channel 2 -> X
*/

#define Y_AXIS 1
#define X_AXIS 2
#define BUTTON 3

// Defines for when we regard position to be negative or positive
#define NEGATIVE_TRESHOLD 90
#define POSITIVE_TRESHOLD 170

typedef struct{
	uint8_t x;
	uint8_t y;
	uint8_t button_pressed;
} position;

typedef enum{NEUTRAL, LEFT, RIGHT, UP, DOWN} direction;

// Returns the position of the joystick as a struct
// contains x and y value

int offsetX;
int offsetY;

// Returns direction of the joystick
position joystickPos();
direction joystickDirX();
direction joystickDirY();


void autoCal();

#endif /* CONTROLLERDRIVER_H_ */