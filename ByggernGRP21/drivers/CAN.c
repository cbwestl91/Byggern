/*
 * CAN.c
 *
 * Created: 23.10.2013 12:49:41
 *  Author: chriwes
 */ 

#include <avr/io.h>
#include "MCP2515.h" //This header file contains MCP2515 register definitions
#include "CAN.h"


void CANInit_loopback(){
	char reg = MCP_CANCTRL;
	char mask = MODE_MASK;
	char data = MODE_LOOPBACK;
	
	MCPBitModify(reg, mask, data);
}

void CANInit_normal(){
	char reg = MCP_CANCTRL;
	char mask = MODE_MASK;
	char data = MODE_NORMAL;
	
	MCPBitModify(reg, mask, data);
}

int CAN_send(CANmessage msg){
	//Locate free register
	//The status return bits seem weirdly placed
	uint8_t status = MCPReadStatus();
	uint8_t buffer = 0;

	if((status & (1 << TXREQ0) == 0){
		buffer = MCP_TXB0CTRL;
	}
	else if(status & (1 << TXREQ1) == 0){
		buffer = MCP_TXB1CTRL;
	}
	else if(status & (1 << TXREQ2) == 0){
		buffer = MCP_TXB2CTRL;
	}
	
	for(uint8_t i = 0; i < frame->msg.length; i++) {
		mcp2515_write(buffer+0x6+i, frame->data[i]);
	}
}
