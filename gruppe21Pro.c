/*
 * gruppe21Pro.c
 *
 * Created: 03.09.2013 09:56:57
 *  Author: raymondd
 */ 


#include <avr/io.h>
#include "uartDriver.h"

int main(void)
{
	unsigned char receivebuffer;
	
	UARTinit();
	
    while(1)
    {
        //TODO:: Please write your application code
		receivebuffer = UARTreceive();
		UARTtransmit(receivebuffer);
	
    }
}