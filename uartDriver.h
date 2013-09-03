/*
 * uartDriver.h
 *
 * Created: 03.09.2013 11:43:14
 *  Author: raymondd
 */ 


#ifndef UARTDRIVER_H_
#define UARTDRIVER_H_


void UARTinit();
void UARTtransmit(unsigned char data);
unsigned char UARTreceive();


#endif /* UARTDRIVER_H_ */