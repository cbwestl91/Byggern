/*
 * CAN.h
 *
 * Created: 23.10.2013 12:49:49
 *  Author: chriwes
 */ 


#ifndef CAN_H_
#define CAN_H_

//STATUS Register Bits

#define MCP_STATUS_RX0IF 0
#define MCP_STATUS_RX1IF 1
#define MCP_STATUS_TXREQ0 2
#define MCP_STATUS_TX0IF 3
#define MCP_STATUS_TXREQ1 4
#define MCP_STATUS_TX1IF 5
#define MCP_STATUS_TXREQ2 6
#define MCP_STATUS_RX2IF 7


typedef struct{
	uint8_t ID;
	unsigned char data[8];
	uint8_t length;
} CANmessage;

void CANInit_loopback();
void CANInit_normal();

int CAN_send(CANmessage msg);
CANmessage CAN_read();

#endif /* CAN_H_ */