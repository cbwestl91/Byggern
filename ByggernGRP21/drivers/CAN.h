/*
 * CAN.h
 *
 * Created: 23.10.2013 12:49:49
 *  Author: chriwes
 */ 


#ifndef CAN_H_
#define CAN_H_

typedef struct{
	unsigned int ID;
	uint8_t data[8];
	uint8_t length;
} CANmessage;




#endif /* CAN_H_ */