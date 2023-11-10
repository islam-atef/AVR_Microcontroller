/*
 * ACD_program.c
 *
 * Created: 10/23/2023 9:02:09 AM
 *  Author: Dell
 */ 
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "ADC_privatef.h"
#include "ADC_interface.h"
#include "ADC_config.h"

#include "../../MCAL/GPIO/GPIO_interface.h"
/*------------------------------------------------------*/
static void ADC_voidStartConversion(void);
static void (*ADC_HANDLER)(void) = NULL;
/*------------------------------------------------------*/
void ADC_voidInit()  
{
	// 1- Reference Type Result
	(*ADMUX) &= (0x00);
	(*ADMUX) |= (VOLTAGE_REFERENCE << (REFS0));  
	// 2- Adjustment Type Result
	(*ADMUX) |= (ADJUSTMENT << (ADLAR));	
	// 3- Set pre-scaler.
	(*ADCSRA) &= (0x00);
	(*ADCSRA) |= (ADC_PRESCALLER);   
	// 4- Choose the mode.
	(*ADCSRA) |= (ADC_MODE << (ADATE));
#if ADC_MODE == ADC_AUTO_TRIGGER_MODE
	// 5- choose the Trigger source.
	(*SFIOR) &= (0b00011111);
	(*SFIOR) |= (ADC_AUTO_TRIGGER_SOURCE << (ADTS0));  
#endif
}
/*------------------------------------------------------*/
void ADC_voidEnable()
{
	SET_BIT(*ADCSRA,ADEN);
}
/*------------------------------------------------------*/
void ADC_voidDisable()
{
	CLR_BIT(*ADCSRA,ADEN);
}
/*------------------------------------------------------*/
void ADC_voidReadADC(CHAN_NUM chan_num , u16 *adc_reading)
{
	u16 Returned_Val;
	// select the channel.
	(*ADMUX) &= (0b11111000);
	(*ADMUX) |= (chan_num); 
	// Start conversion.
#if ADC_MODE != ADC_AUTO_TRIGGER_MODE
	// Start conversion.
	SET_BIT(*ADCSRA ,ADSC);
	while(GET_BIT(*ADCSRA ,ADSC));
#endif
	// take the reading from
#if ADJUSTMENT == REGHT_ADJUSTMENT
	Returned_Val = *ADCW;
#elif ADJUSTMENT == LEFT_ADJUSTMENT
	Returned_Val = (*ADCW>>6);
#endif
 	*adc_reading = Returned_Val;
 	*ADCW = 0x0000;
}
/*------------------------------------------------------*/
void ADC_voidReadADCInMV(CHAN_NUM chan_num , u16 *adc_reading)
{
	u16 Reading;
	ADC_voidReadADC(chan_num , &Reading);
	u16 Volt_Val = ((Reading * VOLTAGE_VALUE)/ 1024);
	*adc_reading = Volt_Val;
}
/*------------------------------------------------------*/
void ADC_voidEnableInt()
{
	SET_BIT(*ADCSRA,ADIE);
}
/*------------------------------------------------------*/
void ADC_voidDisableInt()
{
	CLR_BIT(*ADCSRA,ADIE);
}
/*------------------------------------------------------*/
static void ADC_voidStartConversion()
{
#if ADC_MODE == ADC_NORMAL_MODE
	SET_BIT(*ADCSRA ,ADSC);
	while(GET_BIT(*ADCSRA ,ADSC));
#elif ADC_MODE == ADC_AUTO_TRIGGER_MODE
	SET_BIT(*ADCSRA ,ADSC);
#endif
}
/*------------------------------------------------------*/
void ADC_voidStart_Conversion(CHAN_NUM chan_num)
{
	// select the channel.
	(*ADMUX) &= (0b11111000);
	(*ADMUX) |= (chan_num);
	// start conversion
#if ADC_MODE == ADC_NORMAL_MODE
	SET_BIT(*ADCSRA ,ADSC);
	while(GET_BIT(*ADCSRA ,ADSC));
	
#elif ADC_MODE == ADC_AUTO_TRIGGER_MODE
	SET_BIT(*ADCSRA ,ADSC);
	GPIO_SetValue_Pin(GPIO_PB7,TOGG);
#endif
}
/*------------------------------------------------------*/
void ADC_SetCallback( void (*ptr) (void) )
{
	ADC_HANDLER = ptr;
}
/*------------------------------------------------------*/
void __vector_16 (void) __attribute__ ((signal,used, externally_visible)); //to avoid optimization
void __vector_16 (void)
{
	ADC_HANDLER();
	SET_BIT(*ADCSRA,ADIF);
}
