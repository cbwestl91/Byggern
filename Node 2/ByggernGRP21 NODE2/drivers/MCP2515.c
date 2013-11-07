/*
 * MCP2515.c
 *
 * Created: 23.10.2013 09:06:07
 *  Author: chriwes
 */

#include <avr/io.h>
#include "MCP2515.h"

void MCPChipSelect(){
	//Chip select signal is pulled down
	SPI_REGISTER &= ~(1 << MCP_CHIPSELECT);
}

void MCPChipDeselect(){
	//Chip select signal is pulled up
	SPI_REGISTER |= (1 << MCP_CHIPSELECT);
}

void MCPWrite(char reg, char data){
	MCPChipSelect();
	
	//Send write instruction
	SPI_MasterTransmit(MCP_WRITE);
	
	//Transmit desired location
	SPI_MasterTransmit(reg);
	
	//Transmit data
	SPI_MasterTransmit(data);
	
	MCPChipDeselect();
}

char MCPRead(char reg){
	MCPChipSelect();
	
	//Transmit read instruction
	SPI_MasterTransmit(MCP_READ);
	
	//Transmit desired location
	SPI_MasterTransmit(reg);
	

	
	volatile uint8_t readValue = SPI_MasterRead();
	
	MCPChipDeselect();
	
	return readValue;
}

char MCPReadStatus(){
	MCPChipSelect();
	
	SPI_MasterTransmit(MCP_READ_STATUS);
	
	uint8_t readValue = SPI_MasterRead();

	MCPChipDeselect();

	return readValue;
}

void MCPRequestToSend(char reg){
	//Needs input which register to transmit
	//ALL -> input: MCP_RTS_ALL
	//TX0 -> input:	MCP_RTS_TX0
	//TX1 -> input: MCP_RTS_TX1
	//TX2 -> input: MCP_RTS_TX2

	MCPChipSelect();
	SPI_MasterTransmit(reg);
	MCPChipDeselect();
}

void MCPBitModify(char reg, char mask, char data){
	MCPChipSelect();
	
	//Transmit bit modify instruction
	SPI_MasterTransmit(MCP_BITMOD);
	
	SPI_MasterTransmit(reg);
	SPI_MasterTransmit(mask);
	SPI_MasterTransmit(data);
	
	MCPChipDeselect();
}

void MCPReset(){
	MCPChipSelect();
	SPI_MasterTransmit(MCP_RESET);
	MCPChipDeselect();
}