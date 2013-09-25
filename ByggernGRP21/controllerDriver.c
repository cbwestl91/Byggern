/*
 * controllerDriver.c
 *
 * Created: 11.09.2013 15:19:21
 *  Author: chriwes
 */ 


/* CHANNEL DEFINES:
	channel 1 -> X?
	channel 2 -> Y?
	channel 3 -> joystick press
*/

#include <avr/io.h>
#include "ADC.h"
#include "controllerDriver.h"

void autoCal(){
	// something something works
	
}

position joystickPos(){ //NB: which channel is which is not known at current time!
	position current_position;

	current_position.x = ADC_read(1);
	current_position.y = ADC_read(2);
	
	return current_position;
}

direction joystickDir(){
	position current_position = joystickPos();
	direction current_direction;
	
	if ((double)current_position.x > 140){
		current_direction = RIGHT;
	}
	else if((double)current_position.x < 120){
		current_direction = LEFT;
	}
	else{
		current_direction = NEUTRAL;
	}
	return current_direction;
}

//voltage angle relationship: MIN: 0.44V, MAX: 2.54V, MID: 1.7V
// angle = ax