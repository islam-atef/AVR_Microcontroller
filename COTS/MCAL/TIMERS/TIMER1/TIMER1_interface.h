/*
 * TIMER1_interface.h
 *
 * Created: 10/27/2023 10:34:00 AM
 *  Author: Islam Atef
 */ 
#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

typedef enum{
ICI_ON_FALLING =	0,
ICI_ON_RISING  =	1
}ICI_TIGG_TYPE;

void	TIMER1_voidInit(void);
void	TIMER1_voidStart(void);
void	TIMER1_voidStop(void);

void	TIMER1_voidSetTCNT(u16 buffer);
void	TIMER1_voidGetTCNT(u16 *buffer);

void	TIMER1_voidSetOCRA(u16 buffer);
void	TIMER1_voidGetOCRA(u16 *buffer);

void	TIMER1_voidSetOCRB(u16 buffer);
void	TIMER1_voidGetOCRB(u16 *buffer);

void	TIMER1_voidSetICR(u16 buffer);
void	TIMER1_voidGetICR(u16 *buffer);

void	TIMER1_voidChange_ICR_TRIG(ICI_TIGG_TYPE Trigger_val);

void	TIMER1_voidWritePWM_OCRA(u16 pwm_val);
void	TIMER1_voidWritePWM_OCRA_MAPED(u8 pwm_maped_val);

void	TIMER1_voidWritePWM_OCRB(u16 pwm_val);
void	TIMER1_voidWritePWM_OCRB_MAPED(u8 pwm_maped_val);

void	TIMER1_voidSet_ICI_CallBack( void (*ptr)(void) );
void	TIMER1_voidSet_OCMA_CallBack( void (*ptr)(void));
void	TIMER1_voidSet_OCMB_CallBack( void (*ptr)(void));
void	TIMER1_voidSet_OVF_CallBack( void (*ptr)(void) );

#endif