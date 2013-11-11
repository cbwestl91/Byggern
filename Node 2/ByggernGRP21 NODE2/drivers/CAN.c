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
	MCPReset();
	
	volatile uint8_t temp = MCPRead(MCP_CANSTAT);
	
	if((temp & MODE_CONFIG) != 0){
		printf("WE ARE IN CONFIG MODE!\n");
	} else {
		printf("WE ARE NOT IN CONFIG MODE: %i\n", temp);
		//return;
	}
	
	char reg = MCP_CANCTRL;
	char mask = MODE_MASK;
	char data = MODE_LOOPBACK;
	
	MCPBitModify(reg, mask, data);
	
	temp = MCPRead(MCP_CANSTAT);
	
	if(temp == MODE_LOOPBACK){
		printf("WE ARE IN LOOPBACK MODE!\n");
	}

	//Enable interrupt on receive
	MCPBitModify(MCP_CANINTE, MCP_RX_INT, MCP_RX_INT);
}

void CANInit_normal(){
	MCPReset();
	
	volatile uint8_t temp = MCPRead(MCP_CANSTAT);
	
	if(temp == MODE_CONFIG){
		printf("WE ARE IN CONFIG MODE!\n");
	} else {
		printf("WE ARE NOT IN CONFIG MODE: %i\n", temp);
	}
	
	char reg = MCP_CANCTRL;
	char mask = MODE_MASK;
	char data = MODE_NORMAL;
	
	MCPBitModify(reg, mask, data);
	
	temp = MCPRead(MCP_CANSTAT);
	
	if(temp == MODE_NORMAL){
		printf("WE ARE IN NORMAL MODE!\n");
	}

	//Enable interrupt on receive
	MCPBitModify(MCP_CANINTE, MCP_RX_INT, MCP_RX_INT);
}

int CAN_send(CANmessage msg){
	//Locate free register
	//The status return bits seem weirdly placed
	uint8_t status = MCPReadStatus();
	uint8_t buffer = 0;

	if((status & (1 << TXREQ0)) == 0){
		MCPWrite(TXB0SIDL, msg.ID);
		MCPWrite(TXB0SIDH, msg.ID);
		
		MCPWrite(TXB0DLC, msg.length);
		
		buffer = TXB0D0;
		for(int i = 0; i < msg.length; i++){
			MCPWrite(buffer+i, msg.data[i]);
		}
		
		MCPRequestToSend(MCP_RTS_TX0);
		
		return 0;
	}
	else if((status & (1 << TXREQ1)) == 0){
		MCPWrite(TXB1SIDL, msg.ID);
		MCPWrite(TXB1SIDH, msg.ID);
		
		buffer = TXB1D0;
		for(int i = 0; i < msg.length; i++){
			MCPWrite(buffer+i, msg.data[i]);
		}
		
		MCPRequestToSend(MCP_RTS_TX1);
		
		return 0;
	}
	else if((status & (1 << TXREQ2)) == 0){
		MCPWrite(TXB2SIDL, msg.ID);
		MCPWrite(TXB2SIDH, msg.ID);
		
		buffer = TXB2D0;
		for(int i = 0; i < msg.length; i++){
			MCPWrite(buffer+i, msg.data[i]);
		}
		
		MCPRequestToSend(MCP_RTS_TX2);
		
		return 0;
	} else {
		printf("FAILED TO SEND CAN MSG\n");
		return -1;
	}
}

CANmessage CAN_read(){
	CANmessage received;
	received.length = 8;
	received.data[0] = 0x00;
	uint8_t status = MCPReadStatus();
	
	if((status & (1 << RX0IF))){
		printf("CAN received into RX0IF\n");
		received.data[0] = MCPRead(RXB0DM);
		MCPBitModify(MCP_CANINTF, 0x01, 0x00);
		
	} else if((status & (1 << RX1IF))) {
		printf("CAN received into RX1IF\n");
		received.data[0] = MCPRead(RXB1DM);
		MCPBitModify(MCP_CANINTF, 0x02, 0x00);
	}
	
	return received;
}