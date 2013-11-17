/*
 * Solenoid.c
 *
 * Created: 13.11.2013 18:29:45
 *  Author: chriwes
 */

#include "crystal.h"

#include <avr/io.h>
#include <util/delay.h>

void solenoid_init(){
	DDRE |= (1 << PE2);
	
	PORTE &= ~(1 << PE2);
}

void solenoid_pulse(){
	PORTE &= ~(1 << PE2);
	
	_delay_ms(500);
	
	PORTE |= (1 << PE2);
}