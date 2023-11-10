/*
 * SPI_interface.h
 *
 * Created: 10/30/2023 9:49:10 AM
 *  Author: Dell
 */ 
#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

void SPI_voidMasterInit(void);

void SPI_voidSlaveInit(void);

void SPI_voidEnable(void);

u8 SPI_u8Transfer(u8 Copy_Data);

void SPI_voidEnableInt(u8* ptr_Buffer , u8 Size);

void SPI_voidDisableInt(void);

void SPI_voidSetCallBack( void (*PtrToFunc) (void) );

void SPI_u8ReadDataISR(void);

void SPI_voidSendDataISR(void);

#endif /* SPI_INTERFACE_H_ */