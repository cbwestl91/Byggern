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


// Returns direction of the joystick as an enum value
direction joystickDir();

#endif /* CONTROLLERDRIVER_H_ */