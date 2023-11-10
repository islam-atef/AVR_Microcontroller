/*
 * TIMER0_interface.h
 *
 * Created: 10/27/2023 10:34:00 AM
 *  Author: Islam Atef
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


void	TIMER0_voidInit(void);
void	TIMER0_voidStart(void);
void	TIMER0_voidStop(void);

void	TIMER0_voidGetTCNT(u8 *buffer);
void	TIMER0_voidGetOCR(u8 *buffer);

void	TIMER0_voidWritePWM(u8 pwm_val);
void	TIMER0_voidWritePWM_MAPED(u8 pwm_maped_val);

void	TIMER0_voidSet_COMP_CallBack( void (*ptr)(void) );
void	TIMER0_voidSet_OVF_CallBack( void (*ptr)(void) );

#endif /* TIMER0_INTERFACE_H_ */