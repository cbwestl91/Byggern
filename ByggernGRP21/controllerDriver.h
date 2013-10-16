/*
 * controllerDriver.h
 *
 * Created: 11.09.2013 15:19:33
 *  Author: chriwes
 */ 


#ifndef CONTROLLERDRIVER_H_
#define CONTROLLERDRIVER_H_

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