/*
 * UART_program.c
 *
 * Created: 10/29/2023 10:58:08 AM
 *  Author: Dell
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"

/****************************************************************/
static void (* UART_RX_COMP_CALLBACK )(void) = NULL;
static void (* UART_TX_COMP_CALLBACK )(void) = NULL;
static void (* UART_UDR_EMPTY_CALLBACK )(void) = NULL;

volatile static u8* RX_INIT_local_Received_Buffer ;
volatile static u8  RX_INIT_local_end_char ;
volatile static u8  RX_INIT_local_size;
volatile static u8  RX_INIT_local_counter = 0;

volatile static u8* TX_INIT_local_Transmit_Buffer ;
volatile static u8  TX_INIT_local_end_char ;
volatile static u8  TX_INIT_local_size;
volatile static u8  TX_INIT_local_counter = 0;

static void USART_Receive_INT_HANDLER(void);
static void USART_Transmit_INT_HANDLER(void);
/****************************************************************/
/* Description    :  This function used to initialize USART     */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/
void USART_Init( )
{
	// 1- select the Double Speed Mode.
	(*UCSRA)	= 0x00;
	(*UCSRA)	|=	(_U2X_ <<U2X);
	// 2- select to access {UCSRC} Register.
	(*UCSRC)	= 0x80;  
	// select the Operating mode.
	(*UCSRC)	|= (UART_MODE << UMSEL);  
	// select the parity mode.
	(*UCSRC)	|= (PARITY_MODE << UPM0);  
	// select the number of stop bits.
	(*UCSRC)	|= (STOP_BITS_NUM << USBS);  
	// select the Data Bits number.
	if (DATA_BITS_NUM != _9_BIT_)
	{
		(*UCSRC)	|= (DATA_BITS_NUM << UCSZ0);  
	} 
	else
	{
		SET_BIT((*UCSRC),UCSZ0);
		SET_BIT((*UCSRC),UCSZ1);
		SET_BIT((*UCSRB),UCSZ2);
	}
	// select the Operation mode.
	(*UCSRB)	= 0x00;
	switch(UART_OPERATE)
	{
		case UART_TX:
			SET_BIT((*UCSRB),TXEN);
			break;
		case UART_RX:
			SET_BIT((*UCSRB),RXEN);
			break;
		case UART_TX_RX:
			SET_BIT((*UCSRB),TXEN);
			SET_BIT((*UCSRB),RXEN);
			break;
		default:
			break;
	}
	// Baud Rate Setting.
	(*UBRRL)	=	BAUD_RATE;  
}


/****************************************************************/
/* Description    : This function used to Send Data				*/
/*																*/
/*					Inputs : u8 data				  			*/
/*					Return : void		 					    */
/****************************************************************/
void USART_Transmit( u8 data )
{
	// wait until the DATA register empty flag being set.
	while(!GET_BIT((*UCSRA),UDRE));
	(void)(*UDR);
	(*UDR) = (u8)data;
}


/****************************************************************/
/* Description    : This function used to Transmit String		*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_Transmit_String(u8 *buffer , u8 end_char , u8 size )
{
	volatile u8 counter = 0;
	// wait until the DATA register Not empty flag being set.
	while(!GET_BIT((*UCSRA),UDRE));
	(void)(*UDR);
	//while((buffer[counter] != end_char) && (counter < size))
	while (counter < size )
	{
		if (buffer[counter] == end_char)
		{
			break;
		}
		USART_Transmit(buffer[counter]);
		counter++;
	}
}

/****************************************************************/
/* Description    : This function used to Receive String		*/
/*								by Interrupt					*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_Transmit_INT(u8* Transmit_Buffer , u8 end_char , u8 size  )
{
	// create Local buffers and initiate them.
	
	TX_INIT_local_Transmit_Buffer = Transmit_Buffer;
	TX_INIT_local_end_char = end_char;
	TX_INIT_local_size = size;
	TX_INIT_local_counter = 0;

	// transmit first element.
	USART_Transmit( TX_INIT_local_Transmit_Buffer[TX_INIT_local_counter]  );
	TX_INIT_local_counter++;

	if (TX_INIT_local_counter <= TX_INIT_local_size)
	{
		// Enable Interrupt.
	    USART_Interrupt_Enable(TC_COMPLETE_INT);
	}
}

static void USART_Transmit_INT_HANDLER()
{
	if (TX_INIT_local_counter > TX_INIT_local_size )
	{
		TX_INIT_local_Transmit_Buffer[TX_INIT_local_counter] = '\0';
		(*UDR) = TX_INIT_local_Transmit_Buffer[TX_INIT_local_counter];
		// Disable the interrupt.
		USART_Interrupt_Disable(TC_COMPLETE_INT);
	}
	else
	{
		if (TX_INIT_local_Transmit_Buffer[TX_INIT_local_counter] != TX_INIT_local_end_char)
		{
			(*UDR) = TX_INIT_local_Transmit_Buffer[TX_INIT_local_counter];
			TX_INIT_local_counter++;
		}
		else
		{
			TX_INIT_local_Transmit_Buffer[TX_INIT_local_counter] = '\0';
			(*UDR) = TX_INIT_local_Transmit_Buffer[TX_INIT_local_counter];
			// Disable the interrupt.
			USART_Interrupt_Disable(TC_COMPLETE_INT);
		}
	}
}

/****************************************************************/
/* Description    : This function used to Receive Data			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
u8 USART_Receive( )
{
	// wait until the DATA register Not empty flag being set.
	while(!GET_BIT((*UCSRA),RXC));	
	return (*UDR);
}


/****************************************************************/
/* Description    : This function used to Receive String		*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_Receive_String(u8* Received_Buffer , u8 end_char , u8 size  )
{
	volatile u8  counter = 0;
	// wait until the DATA register Not empty flag being set.
	while(!GET_BIT((*UCSRA),RXC));	
	//while((*UDR != end_char) && (counter < size))
	while (counter < size )
	{
		if (*UDR == end_char)
		{
			break;
		}
		Received_Buffer[counter] =  USART_Receive();
		counter++;
	}
	*Received_Buffer = '\0';
}

/****************************************************************/
/* Description    : This function used to Receive String		*/
/*								by Interrupt					*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_Receive_INT(u8* Received_Buffer , u8 end_char , u8 size  )
{
	// create Local buffers and initiate them.
	
	RX_INIT_local_Received_Buffer = Received_Buffer;
	RX_INIT_local_end_char = end_char;
	RX_INIT_local_size = size;
	RX_INIT_local_counter = 0;
	// Enable Interrupt.
	USART_Interrupt_Enable(RC_COMPLETE_INT);
}

static void USART_Receive_INT_HANDLER()
{
	if (RX_INIT_local_counter > RX_INIT_local_size )
	{
		RX_INIT_local_Received_Buffer[RX_INIT_local_counter] = '\0';
		// Disable the interrupt.
		USART_Interrupt_Disable(RC_COMPLETE_INT);
	}
	else
	{
		if (*UDR != RX_INIT_local_end_char)
		{
			RX_INIT_local_Received_Buffer[RX_INIT_local_counter] = (*UDR);
			RX_INIT_local_counter++;
		}
		else
		{
			RX_INIT_local_Received_Buffer[RX_INIT_local_counter] = '\0';
			// Disable the interrupt.
			USART_Interrupt_Disable(RC_COMPLETE_INT);
		}
	}
}

/****************************************************************/
/* Description    : This function used to Enable Interrupts		*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_Interrupt_Enable(INTE_TYPES Inte_Type)
{
	SET_BIT((*UCSRB),Inte_Type);
}

/****************************************************************/
/* Description    : This function used to Disable Interrupts	*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_Interrupt_Disable(INTE_TYPES Inte_Type)
{
	CLR_BIT((*UCSRB),Inte_Type);
}

/****************************************************************/
/* Description    : This function used to Set callback function */
/*								 for each Interrupts			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_InteSetCallback(INTE_TYPES Inte_Type, void (*ptr)(void))
{
	switch(Inte_Type)
	{
		case RC_COMPLETE_INT:
			UART_RX_COMP_CALLBACK = ptr;
			break;
		case TC_COMPLETE_INT:
			UART_TX_COMP_CALLBACK = ptr;
			break;
		case DATA_REG_EMPTY :
			UART_UDR_EMPTY_CALLBACK = ptr;
			break;
		default:
			break;
	};
}




void __vector_13(void) __attribute__((signal, used, externally_visible)); // to avoid optimization 
void __vector_13(void)
{
	if (UART_RX_COMP_CALLBACK != NULL)
	{
		UART_RX_COMP_CALLBACK();
	}
	USART_Receive_INT_HANDLER();
}

void __vector_14(void) __attribute__((signal, used, externally_visible)); // to avoid optimization 
void __vector_14(void)
{
	if (UART_TX_COMP_CALLBACK != NULL)
	{
		UART_TX_COMP_CALLBACK();
	}
	USART_Transmit_INT_HANDLER();
}

void __vector_15(void) __attribute__((signal, used, externally_visible)); // to avoid optimization 
void __vector_15(void)
{
	if (UART_UDR_EMPTY_CALLBACK != NULL)
	{
		UART_UDR_EMPTY_CALLBACK();
	}
}