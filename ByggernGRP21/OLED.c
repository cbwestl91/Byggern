/*
 * OLED.c
 *
 * Created: 25.09.2013 15:46:48
 *  Author: chriwes
 */ 
#include <avr/io.h>
#include "font_5x7.h"

#include "controllerDriver.h"

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
	int i, j;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 512; j++){
			write_d(0b00000000);
		}
		oled_goto_line(i);
	}
	
	//Jump to first line
	oled_goto_line(0);
}

//Takes in a char and prints it to screen
void oled_print_char(char c){
	int i,j;
	for(i=0;i<5;i++){
		write_d(pgm_read_byte(&font[(int) c -32][i]));
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
	uint8_t lower = (column) & 0b00001111;
	uint8_t upper = column >> 4;
	write_c(0x00+column);
	write_c(0x10+column);
}

//Takes string and prints to screen
void oled_print(char str[]){
	int i;
	for(i=0; str[i]!='\0';i++){
		oled_print_char(str[i]);
	}
}

//Moves to desired line and column
void oled_pos(uint8_t row, uint8_t column){
	oled_goto_line(row);
	oled_changeColumn(column);
}

void oled_home(){
	// entry one
	char entry1[] = "Start game";
	// entry two
	char entry2[] = "High score";
	// entry three
	char entry3[] = "Funny button";
	
	oled_goto_line(0);
	oled_print("MENU");
	oled_goto_line(2);
	oled_print(entry1);
	oled_goto_line(3);
	oled_print(entry2);
	oled_goto_line(4);
	oled_print(entry3);
	
	//Define menu pointer
	oled_pos(2, 5);
	oled_print("<<");
	
	
	int prev;
	int i = 2;
	while(1){
		while(joystickDirY() != NEUTRAL);
		while(joystickDirY() == NEUTRAL);
					prev = i;
					if(joystickDirY() == UP){
						
						if(i == 2){
							i = 5;
						}
						i--;
					}
					else if(joystickDirY() == DOWN){

						if(i == 4){
							i = 1;
						}
						i++;
					}
					
				
						oled_goto_line(prev);
						oled_clear_line();
						
						if(prev == 2){
							oled_print(entry1);
						} else if(prev == 3){
							oled_print(entry2);
						} else{
							oled_print(entry3);
						}
						
						oled_goto_line(i);
						if(i == 2){
							oled_print(entry1);
						} else if(i == 3){
							oled_print(entry2);
						} else{
							oled_print(entry3);
						}
						
						oled_changeColumn(5);
						oled_print("<<");
			
	}						
}
																		