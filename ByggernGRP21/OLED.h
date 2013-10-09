/*
 * OLED.h
 *
 * Created: 25.09.2013 15:46:59
 *  Author: chriwes
 */ 


#ifndef OLED_H_
#define OLED_H_

void init_program();

void oled_init();

void write_c(int command);
void write_d(int data);

void oled_goto_line(uint8_t line);
void oled_clear_line();
void oled_changeColumn(uint8_t column);
void oled_print_char(char c);
void oled_print(char str[]);
void oled_pos(uint8_t row, uint8_t column);
void oled_home();

#endif /* OLED_H_ */