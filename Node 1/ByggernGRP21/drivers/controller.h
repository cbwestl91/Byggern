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
#define NEGATIVE_TRESHOLD 90
#define POSITIVE_TRESHOLD 170

typedef struct{
	int x;
	int y;
} position;

typedef enum{NEUTRAL = 0, LEFT, RIGHT, UP, DOWN} direction;

// Returns the position of the joystick as a struct
// contains x and y value

int offsetX;
int offsetY;

typedef struct{
	char x;
	char y;
} final_direction;

// Returns direction of the joystick as an enum value
direction joystickDirX();
direction joystickDirY();

void autoCal();

#endif /* CONTROLLERDRIVER_H_ */