/*
 * CAN.c
 *
 * Created: 23.10.2013 12:49:41
 *  Author: chriwes
 */ 

#include <avr/io.h>
#include "MCP2515.h"
#include "CAN.h"


void CANInit(){
	char reg = MCP_CANCTRL;
	
	//These settings give loopback mode
	char mask = 0xe0;
	char data = 0;
	
	MCPBitModify(reg, mask, data); 
}

void CANSend(CANmessage *msg){
	
	uint8_t i;
	for(i = 0; i < msg->length; i++){
		
	}
}