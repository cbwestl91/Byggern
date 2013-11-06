/*
 * SPI.h
 *
 * Created: 18.10.2013 11:32:11
 *  Author: chriwes
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_MasterInit();

void SPI_MasterTransmit(char data);

char SPI_MasterRead();


#endif /* SPI_H_ */