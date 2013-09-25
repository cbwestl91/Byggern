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




position joystickPos();
direction joystickDir();

#endif /* CONTROLLERDRIVER_H_ */