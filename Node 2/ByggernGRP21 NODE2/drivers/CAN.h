/*
 * CAN.h
 *
 * Created: 23.10.2013 12:49:49
 *  Author: chriwes
 */ 


#ifndef CAN_H_
#define CAN_H_

//STATUS Register Bits

#define RX0IF 0x00
#define RX1IF 0x01
#define TXREQ0 0x04
#define TXREQ1 0x10
#define TXREQ2 0x40


typedef struct{
	uint8_t ID;
	unsigned char data[8];
	uint8_t length;
} CANmessage;

void CANInit_loopback();
void CANInit_normal();

int CAN_send(CANmessage msg);
CANmessage CAN_read();
void CAN_reset();

#endif /* CAN_H_ */