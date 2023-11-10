/*
 * UART_config.h
 *
 * Created: 10/29/2023 10:58:51 AM
 *  Author: Dell
 */ 
#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/*		UART MODE			*/
#define		ASYNCHRONOUS		0
#define		SYNCHRONOUS			1

#define		UART_MODE			ASYNCHRONOUS
/*--------------------------*/

/*		UART Operating Modes			*/
#define		UART_TX			0
#define		UART_RX			1
#define		UART_TX_RX		2

#define		UART_OPERATE		UART_TX_RX
/*--------------------------*/

/*		Data Bits Number	*/
#define		_5_BIT_		0
#define		_6_BIT_		1
#define		_7_BIT_		2
#define		_8_BIT_		3
#define		_9_BIT_		7

#define		DATA_BITS_NUM		_8_BIT_
/*--------------------------*/

/*		Parity Bit Type	    */
#define		DISABLE_PARITY		0
#define		EVEN_PARITY			2
#define		ODD_PARITY			3

#define		PARITY_MODE		DISABLE_PARITY
/*--------------------------*/

/*		Stop Bits Number	*/
#define		_1_BIT_		0
#define		_2_BIT_		1

#define		STOP_BITS_NUM		_1_BIT_
/*--------------------------*/




/*		Frequency Value		*/
#define		F_CPU		8000000UL
/*--------------------------*/

/*		Double Speed Mode	*/
#define		_U2X_		0
/*--------------------------*/
/*		BAUD Rate Options	*/
/*--------------------------*/
//////////////////////////////
#if		F_CPU	==	8000000UL
//////////////////////////////
#if		_U2X_	==	0
//////////////////////////////
#define		_9600_		51
#define		_14_4k_		34
#define		_19_2k_		25
#define		_28_8k_		16
#define		_38_4k_		12
#define		_57_6k_		8
#define		_76_8k_		6
#define		_115_2k_	3
#define		_230_4k_	1
#define		_250k_		1
//////////////////////////////
#else
//////////////////////////////
#define		_9600_		103
#define		_14_4k_		68
#define		_19_2k_		51
#define		_28_8k_		34
#define		_38_4k_		25
#define		_57_6k_		16
#define		_76_8k_		12
#define		_115_2k_	8
#define		_230_4k_	3
#define		_250k_		3
#endif
/*--------------------------*/
/*--------------------------*/
#elif	F_CPU	==	16000000UL
/*		BAUD Rate Options	*/
//////////////////////////////
#if		_U2X_	==	0
//////////////////////////////
#define		_9600_		103
#define		_14_4k_		68
#define		_19_2k_		51
#define		_28_8k_		34
#define		_38_4k_		25
#define		_57_6k_		16
#define		_76_8k_		12
#define		_115_2k_	8
#define		_230_4k_	3
#define		_250k_		3
//////////////////////////////
#else
//////////////////////////////
#define		_9600_		207
#define		_14_4k_		138
#define		_19_2k_		103
#define		_28_8k_		68
#define		_38_4k_		51
#define		_57_6k_		34
#define		_76_8k_		25
#define		_115_2k_	16
#define		_230_4k_	8
#define		_250k_		7
//////////////////////////////
#endif
//////////////////////////////
/*--------------------------*/
#endif

#define		BAUD_RATE	_9600_
/*--------------------------*/









#endif /* UART_CONFIG_H_ */