/*
 * sound.h
 *
 * Created: 19.11.2013 15:37:10
 *  Author: chriwes
 */ 


#ifndef SOUND_H_
#define SOUND_H_

#define SILENCE 0
#define MENU 1
#define POKEMON 2
#define MARIO 3
#define ZELDA 4
#define GAMEOVER 5
#define ROLL 6

volatile uint8_t ingame_song;

void sound_init();
void sound_play(uint8_t track);


#endif /* SOUND_H_ */