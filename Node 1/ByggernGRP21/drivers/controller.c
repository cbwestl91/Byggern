/*
 * controllerDriver.c
 *
 * Created: 11.09.2013 15:19:21
 *  Author: chriwes
 */ 

#include <avr/io.h>
#include "ADC.h"
#include "controller.h"

void autoCal(){
	// something something works
	
	position initPos = joystickPos();
	offsetX = initPos.x;
	offsetY = initPos.y;
}

position joystickPos(){ //NB: Channels are a bit undefined as of now
	position current_position;
	
	current_position.x = ADC_read(X_AXIS);
	current_position.y = ADC_read(Y_AXIS);

	return current_position;
}

direction joystickDirX(){
	position current_position = joystickPos();
	direction current_direction;
	
	if ((double)current_position.x > POSITIVE_TRESHOLD){
		current_direction = RIGHT;
	}
	else if((double)current_position.x < NEGATIVE_TRESHOLD){
		current_direction = LEFT;
	}
	else{
		current_direction = NEUTRAL;
	}
	
	return current_direction;
}

direction joystickDirY(){
	position current_position = joystickPos();
	direction current_direction;
	
	if ((double)current_position.y > POSITIVE_TRESHOLD){
		current_direction = UP;
	}
	else if((double)current_position.y < NEGATIVE_TRESHOLD){
		current_direction = DOWN;
	}
	else{
		current_direction = NEUTRAL;
	}
	
	return current_direction;
}