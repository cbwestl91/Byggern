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
	channel 3 -> joystick press
*/

#define Y_AXIS 1
#define X_AXIS 2
#define JOYSTICK_PRESS 3

// Defines for when we regard position to be negative or positive
#define NEGATIVE_TRESHOLD 120
#define POSITIVE_TRESHOLD 140

typedef struct{
	int x;
	int y;
} position;

typedef enum{LEFT, RIGHT, UP, DOWN, NEUTRAL}direction;

// Returns the position of the joystick as a struct
// contains x and y value
position joystickPos();

int offsetX;
int offsetY;

// Returns direction of the joystick as an enum value
direction joystickDirX();
direction joystickDirY();

void autoCal();

#endif /* CONTROLLERDRIVER_H_ */