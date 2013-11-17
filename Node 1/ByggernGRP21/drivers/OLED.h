/*
 * OLED.h
 *
 * Created: 25.09.2013 15:46:59
 *  Author: chriwes
 */ 


#ifndef OLED_H_
#define OLED_H_

#define menu_header 0
#define menu_entry_one 2
#define menu_entry_two 3
#define menu_entry_three 4

#define arrow_column 5

volatile int button_pressed; //Variable set by interrupt

void oled_init();

void oled_print_char(char c);
void oled_print(char str[]);
void oled_print_char_medium(char c);
void oled_print_medium(char str[]);

void oled_clear_screen();
void oled_goto_line(uint8_t line);
void oled_clear_line();
void oled_changeColumn(uint8_t column);

void oled_pos(uint8_t row, uint8_t column);

void oled_welcome();
int oled_navigate();

#endif /* OLED_H_ */