/*
 * ADC_config.h
 *
 * Created: 10/23/2023 9:02:59 AM
 *  Author: Dell
 */ 
#ifndef _ADC_CONFIG_H
#define _ADC_CONFIG_H
/****************************************************************/
#define		AREF						0
#define		AVCC						1
#define		Int_2_56V					3

#define		VOLTAGE_REFERENCE			AVCC
/****************************************************************/
#define		VOLTAGE_VALUE				5
/****************************************************************/
#define		REGHT_ADJUSTMENT			0
#define		LEFT_ADJUSTMENT				1

#define		ADJUSTMENT			REGHT_ADJUSTMENT
/****************************************************************/
#define		ADC_NORMAL_MODE				0
#define		ADC_AUTO_TRIGGER_MODE		1

#define		ADC_MODE		ADC_AUTO_TRIGGER_MODE
/****************************************************************/
#define		Free_Running_mode					0
#define		Analog_Comparator					1
#define		External_Interrupt_Request_0		2
#define		Timer_Counter0_Compare_Match		3
#define		Timer_Counter0_Overflow				4
#define		Timer_Counter1_Compare_Match_B		5
#define		Timer_Counter1_Overflow				6
#define		Timer_Counter1_Capture_Event		7

#define		ADC_AUTO_TRIGGER_SOURCE		Free_Running_mode
/****************************************************************/
#define		DIVID_BY_2						0
#define		DIVID_BY_4						2	
#define		DIVID_BY_8						3
#define		DIVID_BY_16						4
#define		DIVID_BY_32						5
#define		DIVID_BY_64						6
#define		DIVID_BY_128					7

#define		ADC_PRESCALLER				DIVID_BY_64
/****************************************************************/
#endif
