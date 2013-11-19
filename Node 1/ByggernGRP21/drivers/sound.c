/*
 * sound.c
 *
 * Created: 19.11.2013 15:37:00
 *  Author: chriwes
 */

#include <avr/io.h>

void sound_init(){
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
}

void sound_play(uint8_t track){
	switch (track){
	case 1: // 001
		PORTB &= ~(1 << PB1);
		PORTB &= ~(1 << PB2);
		PORTB |= (1 << PB0);
		break;
	case 2: // 010
		PORTB &= ~(1 << PB0);
		PORTB &= ~(1 << PB2);
		PORTB |= (1 << PB1);
		break;
	case 3: // 011
		PORTB &= ~(1 << PB2);
		PORTB |= (1 << PB0) | (1 << PB1);
		break;
	case 4: // 100
		PORTB &= ~(1 << PB0);
		PORTB &= ~(1 << PB1);
		PORTB |= (1 << PB2);
		break;
	case 5: // 101
		PORTB &= ~(1 << PB1);
		PORTB |= (1 << PB0) | (1 << PB2);
		break;
	case 6: // 110
		PORTB &= ~(1 << PB0);
		PORTB |= (1 << PB1) | (1 << PB2);
		break;
	default: // 000
		PORTB &= ~(1 << PB0);
		PORTB &= ~(1 << PB1);
		PORTB &= ~(1 << PB2);
	}
}