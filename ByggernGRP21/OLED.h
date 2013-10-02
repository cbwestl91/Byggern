/*
 * OLED.h
 *
 * Created: 25.09.2013 15:46:59
 *  Author: chriwes
 */ 


#ifndef OLED_H_
#define OLED_H_

void init_program();

void oled_print();

void write_c(int command);
void write_d(int data);

#endif /* OLED_H_ */