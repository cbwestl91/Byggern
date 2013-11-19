/*
 * OLED.c
 *
 * Created: 25.09.2013 15:46:48
 *  Author: chriwes
 */ 

#define F_CPU 4915200UL

#include <avr/io.h>
#include <util/delay.h>

#include "font_5x7.h"
#include "font_8x8.h"
#include "OLED.h"
#include "controller.h"
#include "sound.h"

//Takes in a byte and passes to the command memory of the OLED screen
void write_c(char command){
	volatile char *commandMem = (char *)0x1000;
	
	commandMem[0] = command;
}

//Takes in a byte and passes to the data memory of the OLED screen
void write_d(char data){
	volatile char* dataMem = (char *)0x1200;
	
	dataMem[0] = data;
}

//Initializes the OLED screen with a blank screen
void oled_init(){
	write_c(0xae); // display off
	write_c(0xa1); //segment remap
	write_c(0xda); //common pads hardware: alternative
	write_c(0x12);
	write_c(0xc8); //common output scan direction:com63~com0
	write_c(0xa8); //multiplex ration mode:63
	write_c(0x3f);
	write_c(0xd5); //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81); //contrast control
	write_c(0x50);
	write_c(0xd9); //set pre-charge period
	write_c(0x21);
	write_c(0x20); //Set Memory Addressing Mode
	write_c(0x02);
	write_c(0xdb); //VCOM deselect level mode
	write_c(0x30);
	write_c(0xad); //master configuration
	write_c(0x00);
	write_c(0xa4); //out follows RAM content
	write_c(0xa6); //set normal display
	write_c(0xaf); // display on

	// Clear screen
	oled_clear_screen();
}

void oled_clear_screen(){
	int i, j;
	for(i = 0; i < 8; i++){
		oled_goto_line(i);
		for(j = 0; j < 256; j++){
			write_d(0b00000000);
		}
	}
	
	//Jump to first line
	oled_goto_line(0);
}



//Takes in a char and prints it at current position
//SMALL SIZE
void oled_print_char(char c){
	int i;
	for(i=0;i<5;i++){
		write_d(pgm_read_byte(&font[(int) c -32][i]));
	}		
}

//Takes string and prints to screen
//SMALL SIZE
void oled_print(char str[]){
	int i;
	for(i=0; str[i]!='\0';i++){
		oled_print_char(str[i]);
	}
}

//Takes in a char and prints it at current position
//MEDIUM SIZE
void oled_print_char_medium(char c){
	int i;
	for(i=0;i<8;i++){
		write_d(pgm_read_byte(&font_medium[(int) c -32][i]));
	}
}

//Takes string and prints to screen
//MEDIUM SIZE
void oled_print_medium(char str[]){
	int i;
	for(i=0; str[i]!='\0';i++){
		oled_print_char_medium(str[i]);
	}
}

//Takes integer between 0-7 and moves to this line
//Also resets column
void oled_goto_line(uint8_t line){
	write_c(0xB0+line);
	oled_changeColumn(0);
}

void oled_clear_line(){
	int i;
	for(i = 0; i < 128; i++){
		write_d(0x00);
	}
	//Jump to first column
	oled_changeColumn(0);
	
}

void oled_changeColumn(uint8_t column){
	//uint8_t lower = (column) & 0b00001111;
	//uint8_t upper = column >> 4;
	write_c(0x00+column);
	write_c(0x10+column);
}

//Moves to desired line and column
void oled_pos(uint8_t row, uint8_t column){
	oled_goto_line(row);
	oled_changeColumn(column);
}

void oled_welcome(){
	oled_clear_screen();
	
	char message1[] = "VELKOMMEN!";
	char message2[] = "WELCOME!";
	char message3[] = "Willkommen!";
	char message4[] = "Bienvenue!";
	char message5[] = "Bon bini!";
	char message6[] = "Mauya!";
	char message7[] = "Welkam!";
	
	oled_goto_line(0);
	oled_print(message1);
	oled_goto_line(1);
	oled_print(message2);
	oled_goto_line(2);
	oled_print(message3);
	oled_goto_line(3);
	oled_print(message4);
	oled_goto_line(4);
	oled_print(message5);
	oled_goto_line(5);
	oled_print(message6);
	oled_goto_line(6);
	oled_print(message7);
	
	_delay_ms(1000);
}

void oled_game_over(){
	oled_clear_screen();
	
	sound_play(GAMEOVER); //Play game over music
	
	char message1[] = "GAME OVER";
	//char message2[] = "YOU DIED";

	oled_goto_line(3);
	oled_changeColumn(2);
	oled_print(message1);
	
	_delay_ms(3000);
	sound_play(SILENCE); //prevent looping
	_delay_ms(1000);
}

int oled_navigate(){
	volatile position joy_pos;
	joy_pos.button_pressed = 150;
	
	oled_clear_screen();
	
	/*FIRST MENU*/
	
	// header
	char header[] = "MENU";
	// entry one
	char entry1[] = "Start game";
	// entry two
	char entry2[] = "Change music";
	// entry three
	char entry3[] = "DO NOT PRESS!";
	
	// arrow starts on entry one. Movement of joystick along Y axis changes this
	int arrow = menu_entry_one;
	int prev_arrow;
	int navigation_counter = 999;
	int started = 0;
	

	
	//Define menu pointer
	oled_pos(menu_entry_one, arrow_column);
	oled_print("<<");
	sound_play(MENU);
	
	while(!started){
		oled_goto_line(menu_header);
		oled_print(header);
		oled_goto_line(menu_entry_one);
		oled_print(entry1);
		oled_goto_line(menu_entry_two);
		oled_print(entry2);
		oled_goto_line(menu_entry_three);
		oled_print(entry3);
		
		if(joystickDirY() != NEUTRAL){
			navigation_counter++;
		}
		else{
			navigation_counter = 1;
		}

		if(navigation_counter % 100 == 0){
			prev_arrow = arrow;
			if(joystickDirY() == UP){
				if(arrow == menu_entry_one){
					arrow = menu_entry_three;
				} else{
					arrow--;
				}
			}
			else if(joystickDirY() == DOWN){

				if(arrow == menu_entry_three){
					arrow = menu_entry_one;
				} else{
					arrow++;
				}
			}
			
			oled_goto_line(prev_arrow);
			oled_clear_line();
			
			oled_goto_line(arrow);
			oled_changeColumn(arrow_column);
			oled_print("<<");
			oled_changeColumn(0);

			navigation_counter++;
		}
		
		//Handle button presses
		joy_pos = joystickPos();
		
		if(joy_pos.button_pressed < button_margin){
			while(joy_pos.button_pressed < button_margin){ //Prevent button spam
				joy_pos = joystickPos();
			}
			
			if(arrow == menu_entry_one){
				started = 1; //A game request has been received, so we should stop interfacing
			} else if(arrow == menu_entry_two){
				oled_submenu1();
				oled_clear_screen();

				//Redefine menu pointer
				oled_goto_line(arrow);
				oled_changeColumn(arrow_column);
				oled_print("<<");
				oled_changeColumn(0);
				sound_play(MENU);
			} else if(arrow == menu_entry_three){
				oled_submenu2();
				oled_clear_screen();

				//Redefine menu pointer
				oled_goto_line(arrow);
				oled_changeColumn(arrow_column);
				oled_print("<<");
				oled_changeColumn(0);
				sound_play(MENU);
				
			}
			button_pressed = 0;
		}
	}
	return 0;
}

int oled_submenu1(){
	volatile position joy_pos;
	joy_pos.button_pressed = 150;
	
	oled_clear_screen();
	
	/*FIRST MENU*/
	
	// header
	char header[] = "MUSIC MENU";
	// entry one
	char entry1[] = "POKEMON";
	// entry two
	char entry2[] = "SUPER MARIO";
	// entry three
	char entry3[] = "ZELDA";
	
	// arrow starts on entry one. Movement of joystick along Y axis changes this
	int arrow = menu_entry_one;
	int prev_arrow;
	int navigation_counter = 999;
	int started = 0;
	
	//Define menu pointer
	oled_pos(menu_entry_one, arrow_column);
	oled_print("<<");
	sound_play(POKEMON);
	
	while(!started){
		oled_goto_line(menu_header);
		oled_print(header);
		oled_goto_line(menu_entry_one);
		oled_print(entry1);
		oled_goto_line(menu_entry_two);
		oled_print(entry2);
		oled_goto_line(menu_entry_three);
		oled_print(entry3);
		
		if(joystickDirY() != NEUTRAL){
			navigation_counter++;
		}
		else{
			navigation_counter = 1;
		}

		if(navigation_counter % 100 == 0){
			prev_arrow = arrow;
			if(joystickDirY() == UP){
				if(arrow == menu_entry_one){
					arrow = menu_entry_three;
				} else{
					arrow--;
				}
			}
			else if(joystickDirY() == DOWN){

				if(arrow == menu_entry_three){
					arrow = menu_entry_one;
				} else{
					arrow++;
				}
			}
			
			//Let user listen to currently selected song
			if(arrow == menu_entry_one){
				sound_play(POKEMON);
			} else if(arrow == menu_entry_two){
				sound_play(MARIO);
			} else if(arrow == menu_entry_three){
				sound_play(ZELDA);
			} else {
				sound_play(ROLL);
			}
			
			oled_goto_line(prev_arrow);
			oled_clear_line();
			
			oled_goto_line(arrow);
			
			oled_changeColumn(arrow_column);
			oled_print("<<");
			oled_changeColumn(0);

			navigation_counter++;
		}
		
		//Handle button presses
		joy_pos = joystickPos();
		
		if(joy_pos.button_pressed < button_margin){
			while(joy_pos.button_pressed < button_margin){ //Prevent button spam
				joy_pos = joystickPos();
			}
			
			if(arrow == menu_entry_one){
				ingame_song = POKEMON;
			} else if(arrow == menu_entry_two){
				ingame_song = MARIO;
			} else if(arrow == menu_entry_three){
				ingame_song = ZELDA;
			}
			started = 1;
			button_pressed = 0;
		}
	}
	return 0;
}

void oled_submenu2(){
	volatile position joy_pos;
	joy_pos.button_pressed = 150;
	
	oled_clear_screen();
	
	/*FIRST MENU*/
	
	// header
	char header[] = "YOU ARE TRAPPED!";
	// entry one
	char entry1[] = "NEVER";
	// entry two
	char entry2[] = "GONNA";
	// entry three
	char entry3[] = "GIVE YOU UP";
	
	// arrow starts on entry one. Movement of joystick along Y axis changes this
	int arrow = menu_entry_one;
	int prev_arrow;
	int navigation_counter = 999;
	int started = 0;
	
	//Define menu pointer
	oled_pos(menu_entry_one, arrow_column);
	oled_print("<<");
	sound_play(ROLL);
	
	while(!started){
		oled_goto_line(menu_header);
		oled_print(header);
		oled_goto_line(menu_entry_one);
		oled_print(entry1);
		oled_goto_line(menu_entry_two);
		oled_print(entry2);
		oled_goto_line(menu_entry_three);
		oled_print(entry3);
		
		if(joystickDirY() != NEUTRAL){
			navigation_counter++;
		}
		else{
			navigation_counter = 1;
		}

		if(navigation_counter % 100 == 0){
			prev_arrow = arrow;
			if(joystickDirY() == UP){
				if(arrow == menu_entry_one){
					arrow = menu_entry_three;
				} else{
					arrow--;
				}
			}
			else if(joystickDirY() == DOWN){

				if(arrow == menu_entry_three){
					arrow = menu_entry_one;
				} else{
					arrow++;
				}
			}
			
			oled_goto_line(prev_arrow);
			oled_clear_line();
			
			oled_goto_line(arrow);
			
			oled_changeColumn(arrow_column);
			oled_print("<<");
			oled_changeColumn(0);

			navigation_counter++;
		}
		
		//Handle button presses
		joy_pos = joystickPos();
		
		if(joy_pos.button_pressed < button_margin){
			while(joy_pos.button_pressed < button_margin){ //Prevent button spam
			joy_pos = joystickPos();
		}
		started = 1;
		button_pressed = 0;
	}
}
return 0;
}