/*
 * ADC.h
 *
 * Created: 12.11.2013 11:55:41
 *  Author: raymondd
 */ 


#ifndef ADC_H_
#define ADC_H_

#define goal_trigger 50

void ADC_init();
int ADC_read();

int ADC_check_goal();

#endif /* ADC_H_ */