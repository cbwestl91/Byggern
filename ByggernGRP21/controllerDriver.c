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

typedef struct position{
int x;
int y;
};

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL} direction_t;






void autoCal(){
	// something something works
	
}

position_t joystickPos(){ //NB: which channel is which is not known at current time!
	struct 

	position_t.x = ADC_read(1);
	position_t.y = ADC_read(2);
	
	return position_t;
}

direction_t joystickDir(){
	/*
	struct position_t = joystickPos();
	
	if(position_t.x < position_t.y && ){
		direction_t = 
		
	}
	*/
}

//voltage angle relationship: MIN: 0.44V, MAX: 2.54V, MID: 1.7V
// angle = ax