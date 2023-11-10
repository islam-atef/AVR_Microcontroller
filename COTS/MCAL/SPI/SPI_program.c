/*
 * SPI_program.c
 *
 * Created: 10/30/2023 9:48:53 AM
 *  Author: Dell
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"
#include "../GPIO/GPIO_interface.h"

// MASTER send clock to the slave.
// Master send SS to the slave to activate it.
// Master send Data.

// ----> There is no Frame here, just Data, so it has the highest throughput.
volatile u8 *DataBuffer;
volatile u8 Global_Size_Buffer;
volatile u8 Global_Counet;
static void (* SPI_CALLBACK )(void) = NULL;

void SPI_voidMasterInit(void)
{
	(*SPCR) = 0x00;
	// 1- choose master mode.
	SET_BIT((*SPCR),MSTR);
	
	// 2- select clock polarity.
	(*SPCR) |= (SPI_CLK_POL<<CPOL); 
	
	// 3- select clock Phase.
	(*SPCR) |= (SPI_CLK_PH<<CPHA);
	
	// 4- select Data Order.
	(*SPCR) |= (SPI_DATA_ORDER<<DORD);
	
	// 5- Double Speed select.
	CLR_BIT((*SPSR),SPI2X);
	(*SPSR) |= (SPI_DOUBLE_SPEED<<SPI2X);
	
	// 6- Select the speed.
	(*SPCR) |= (SPI_FREQ<<SPR0);
	
}

void SPI_voidSlaveInit(void)
{
	(*SPCR) = 0x00;
	// 1- choose master mode.
	CLR_BIT((*SPCR),MSTR);
	
	// 2- select clock polarity.
	(*SPCR) |= (SPI_CLK_POL<<CPOL);
	
	// 3- select clock Phase.
	(*SPCR) |= (SPI_CLK_PH<<CPHA);
	
	// 4- select Data Order.
	(*SPCR) |= (SPI_DATA_ORDER<<DORD);
	
	// 5- Double Speed select.
	CLR_BIT((*SPSR),SPI2X);
	(*SPSR) |= (SPI_DOUBLE_SPEED<<SPI2X);
	
	// 6- Select the speed.
	(*SPCR) |= (SPI_FREQ<<SPR0);
	
	// 7- Enable SPI.
	SET_BIT((*SPCR),SPE);
}

void SPI_voidEnable(void)
{
	// 1- Enable SPI.
	SET_BIT((*SPCR),SPE);
}

u8 SPI_u8Transfer(u8 Copy_Data)
{
	(*SPDR) = Copy_Data;
	while(!GET_BIT((*SPSR), SPIF));
	return (*SPDR);
}

void SPI_voidSetCallBack( void (*PtrToFunc) (void) )
{
	SPI_CALLBACK = PtrToFunc;
}


void SPI_voidEnableInt(u8* ptr_Buffer , u8 Size)
{
	SET_BIT((*SPCR),SPIE);
	DataBuffer = ptr_Buffer;
	Global_Size_Buffer = Size;
}

void SPI_voidDisableInt()
{
	CLR_BIT((*SPCR),SPIE);
}

void SPI_u8ReadDataISR(void)
{
	if (Global_Counet < Global_Size_Buffer && (*SPDR) != '\0' )
	{
		DataBuffer[Global_Counet] = (*SPDR);
		Global_Counet++;
		GPIO_SetValue_Pin(GPIO_PA6,HIGH);
	}
}

void SPI_voidSendDataISR(void)
{
	if (Global_Counet < Global_Size_Buffer )
	{
		(*SPDR) = DataBuffer[Global_Counet];	
		Global_Counet++;
		GPIO_SetValue_Pin(GPIO_PA4,HIGH);
	}
}

void __vector_12(void) __attribute__((signal, used, externally_visible)); // to avoid optimization (TIMER0 OVF ISR)
void __vector_12(void)
{
	if (SPI_CALLBACK != NULL)
	{
		SPI_CALLBACK();
	}
}