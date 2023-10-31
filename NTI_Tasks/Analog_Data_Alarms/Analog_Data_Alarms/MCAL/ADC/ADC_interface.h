/*
 * ADC_interface.h
 *
 * Created: 10/23/2023 9:02:43 AM
 *  Author: Dell
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef enum{
	ADC0 = 0,
	ADC1 = 1,
	ADC2 = 2,
	ADC3 = 3,
	ADC4 = 4,
	ADC5 = 5,
	ADC6 = 6,
	ADC7 = 7
	} CHAN_NUM;

void ADC_voidInit(void);

void ADC_voidEnable(void);
void ADC_voidDisable(void);

void ADC_voidReadADC(CHAN_NUM chan_num, u16 *adc_reading);
void ADC_voidReadADCInMV(CHAN_NUM chan_num , u16 *adc_readings);

void ADC_voidEnableInt(void);
void ADC_voidDisableInt(void);

void ADC_voidChannelSelect(CHAN_NUM chan_num );
void ADC_voidStart_Conversion(CHAN_NUM chan_num);

void ADC_SetCallback( void (*ptr) (void) );
#endif /* ADC_INTERFACE_H_ */