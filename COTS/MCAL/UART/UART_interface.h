/*
 * UART_interface.h
 *
 * Created: 10/29/2023 10:58:30 AM
 *  Author: Dell
 */ 
/****************************************************************/
#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_
/****************************************************************/
typedef	enum{
	_TX_,			
	_RX_,			
	_TX_RX_			
	
}UART_OPERATION;

typedef	enum{
	DATA_REG_EMPTY  = 5,
	TC_COMPLETE_INT = 6,
	RC_COMPLETE_INT = 7
}INTE_TYPES;
/****************************************************************/

/****************************************************************/
/* Description    :  This function used to initialize USART     */
/*					 Inputs : void 								*/
/*					 return : void		 						*/
/****************************************************************/
void USART_Init(void );


/****************************************************************/
/* Description    : This function used to Send Data				*/
/*																*/
/*					Inputs : u8 data				  			*/
/*					Return : void		 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after USART		*/
/*     				 initialized 							    */
/****************************************************************/
void USART_Transmit( u8 data );


/****************************************************************/
/* Description    : This function used to Transmit String		*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after USART		*/
/*     				 initialized 							    */
/****************************************************************/
void USART_Transmit_String(u8 *buffer , u8 end_char , u8 size );


/****************************************************************/
/* Description    : This function used to Receive Data			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after USART		*/
/*     				 initialized 							    */
/****************************************************************/
u8 USART_Receive( );


/****************************************************************/
/* Description    : This function used to Receive String		*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
/* Pre_condition  :  this function must be used after USART		*/
/*     				 initialized 							    */
/****************************************************************/
void USART_Receive_String(u8* Received_Buffer, u8 end_char ,u8 size );


/****************************************************************/
/* Description    : This function used to Set callback function */
/*								 for each Interrupts			*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_InteSetCallback(INTE_TYPES Inte_Type, void (*ptr)(void));


/****************************************************************/
/* Description    : This function used to Disable Interrupts	*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_Interrupt_Disable(INTE_TYPES Inte_Type);


/****************************************************************/
/* Description    : This function used to Enable Interrupts		*/
/*																*/
/*					Inputs : void					  			*/
/*					Return : u8			 					    */
/****************************************************************/
void USART_Interrupt_Enable(INTE_TYPES Inte_Type);


/****************************************************************/
#endif