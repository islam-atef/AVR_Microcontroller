/*
 * GccApplication9.c
 *
 * Created: 10/23/2023 8:56:42 AM
 * Author : Dell
 */ 

/************************************************************************/
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/EXTI/EXTI_interface.h"

#include "HAL/LCD/LCD_interface.h"
#include <util/delay.h>                                                                 
/************************************************************************/

/************************************************************************/
#define		F_CPU	8000000UL
/************************************************************************/

/************************************************************************/
#define		EXRI0_PIN	GPIO_PD2
#define		BUZZER_PIN	GPIO_PC6

#define		SENSOR_0_MAX_VAL	999
#define		SENSOR_1_MAX_VAL	80
#define		SENSOR_2_MAX_VAL	1000
/************************************************************************/


/************************************************************************/
volatile u16 Read[3];
volatile u8 CHAN_array[3] = {ADC0 , ADC1 , ADC4};
volatile u8 Flag_1 = 1 ;
volatile u8 Flag_2 ;
volatile u8 Flag_3 ;
volatile u8 Flag_Alarm ;
volatile u8 Flag_Alarm_Buffer ;
volatile u8 Alarm_Source ;
/************************************************************************/


/************************************************************************/
void ADC_Handler(void);
void EXTI0_Handler(void);
void LCD_Presentation(void);
void ReadingCheck(void);
void Alarm_Call(void);
/************************************************************************/


/************************************************************************/
int main(void)
{
	// initializations.
	GPIO_Init();
	LCD_Init();
	ADC_voidInit();
	EXTI_voidInit();
	_delay_ms(100);
	// Interrupt Set callback functions.
	ADC_SetCallback(ADC_Handler);
	EXTI_VID_SET_CALL_BACK(EXTI_INT_0, EXTI0_Handler);
	
	// GPIO Settings.
	GPIO_SetValue_Pin(EXRI0_PIN,HIGH); // EXTI0 pin start as High.
	
	// Interrupts Enabling.
	ADC_voidEnableInt();
	EXTI_voidEnable(EXTI_INT_0);
	
	// Peripherals Enabling.
	ADC_voidEnable();
	
	// Start the ADC conversion.
	ADC_voidStart_Conversion(CHAN_array[0]);
	
	// Global Interrupt Enable.
	GIE_voidEnable();
	while (1)
	{
		
		ReadingCheck();
		if (Flag_Alarm != Flag_Alarm_Buffer)
		{
			Alarm_Call();
		}
		else
		{
			if(!Flag_Alarm)
			{
				LCD_Presentation();
			}
		}
	};
}
/************************************************************************/


/************************************************************************/
void LCD_Presentation(void)
{
	//LCD_ClearDisplay();
	LCD_GoTo_xy(0,0);
	LCD_WriteString("LDR Value is : ");
	LCD_WriteNumber(Read[0]);
	LCD_WriteString("  ");
	LCD_GoTo_xy(1,0);
	LCD_WriteString("LM35 Value is : ");
	LCD_WriteNumber(Read[1]);
	LCD_WriteString("  ");
	LCD_GoTo_xy(2,0);
	LCD_WriteString("LM35 Value is : ");
	LCD_WriteNumber(Read[2]);
	LCD_WriteString("  ");
	//_delay_ms(3000);
}
/*----------------------------------------------------------------------*/
void ReadingCheck()
{
	if (Read[0] >= SENSOR_0_MAX_VAL)
	{
		Alarm_Source = 0;
		GPIO_SetValue_Pin(EXRI0_PIN,LOW);
	}
	else if (Read[1] >= SENSOR_1_MAX_VAL)
	{
		Alarm_Source = 1;
		GPIO_SetValue_Pin(EXRI0_PIN,LOW);
	}
	else if (Read[2] >= SENSOR_2_MAX_VAL)
	{
		Alarm_Source = 2;
		GPIO_SetValue_Pin(EXRI0_PIN,LOW);
	}
	else
	{
		Flag_Alarm = 0;
	}
}
/*----------------------------------------------------------------------*/
void Alarm_Call()
{
	// store the Flag Reading.
	Flag_Alarm_Buffer = Flag_Alarm;
	if (Flag_Alarm)
	{
		// 1 - Turn on the Buzzer.
		GPIO_SetValue_Pin(BUZZER_PIN,HIGH);
		// show the source and its Reading on the LCD.
		LCD_ClearDisplay();
		LCD_GoTo_xy(1,0);
		switch(Alarm_Source)
		{
			case 0:
				LCD_WriteString("LDR Value is : ");
				LCD_WriteNumber(Read[0]);
			break;
			case 1:
				LCD_WriteString("LM35 Value is : ");
				LCD_WriteNumber(Read[1]);
			break;
			case 2:
				LCD_WriteString("LM35 Value is : ");
				LCD_WriteNumber(Read[2]);
			break;
			default:
			break;
		}
	}
	else
	{
		GPIO_SetValue_Pin(BUZZER_PIN,LOW);
		// clear the display.
		LCD_ClearDisplay();
	}
}
/************************************************************************/


/************************************************************************/
void ADC_Handler()
{
	if (Flag_1)
	{
		GPIO_SetValue_Pin(GPIO_PC0,HIGH);
		ADC_voidReadADCInMV(CHAN_array[0],&Read[0]);
		Flag_1 = 0;
		Flag_2 = 1;
		ADC_voidChannelSelect(CHAN_array[1]);
		GPIO_SetValue_Pin(GPIO_PC3,HIGH);
	}
	else if(Flag_2)
	{
		GPIO_SetValue_Pin(GPIO_PC1,HIGH);
		ADC_voidReadADCInMV(CHAN_array[1],&Read[1]);
		Flag_2 = 0;
		Flag_3 = 1;
		ADC_voidChannelSelect(CHAN_array[2]);
	}
	else if(Flag_3)
	{
		GPIO_SetValue_Pin(GPIO_PC2,HIGH);
		ADC_voidReadADCInMV(CHAN_array[2],&Read[1]);
		Flag_3 = 0;
		Flag_1 = 1;
		ADC_voidChannelSelect(CHAN_array[0]);
	}
	else{}
}
/*----------------------------------------------------------------------*/
void EXTI0_Handler()
{
	// start the buzzer Function,
	Flag_Alarm = 1;
	GPIO_SetValue_Pin(EXRI0_PIN,HIGH);
}
/************************************************************************/
