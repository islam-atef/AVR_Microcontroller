/*
 * TIMER0_program.c
 *
 * Created: 10/27/2023 10:33:40 AM
 *  Author: Islam Atef
 */ 

#include "../../../LIB/BIT_MATH.h"
#include "../../../LIB/STD_TYPES.h"

#include "TIMER0_interface.h"
#include "TIMER0_config.h"
#include "TIMER0_private.h"


static void (*TIMER0_COMP_CALLBACK)(void) = NULL;
static void (*TIMER0_OVF_CALLBACK)(void) = NULL;

void	TIMER0_voidInit(void)
{
	// Clear Registers.
	(*TCCR0)	=	0x00;
	(*TCNT0)	=	0x00;
	(*OCR0)		=	0x00;
	// set the Mode;
	(*TCCR0)	|=	(GET_BIT(TIMER0_MODE,0) << WGM00);
	(*TCCR0)	|=	(GET_BIT(TIMER0_MODE,1) << WGM01);
	
	// Set OC0_Pin Output.
#if TIMER0_MODE == TIMER0_PWM_FAST_MODE
	(*TCCR0)	|=	(TIMER0_COM_FAST_PWM << COM00);
	
#elif TIMER0_MODE == TIMER0_PWM_PHASE_CORRECT
	(*TCCR0)	|=	(TIMER0_COM_PHASE_CORRECT_PWM << COM00);
	
#else
	(*TCCR0)	|=	(TIMER0_COM_NON_PWM << COM00);
#endif
}

void	TIMER0_voidStart()
{
	// set the Clock source.
	(*TCCR0)	|=	(TIMER0_CLOCK_SOURCE << CS00);
}

void	TIMER0_voidStop()
{
	// Terminate the Clock source.
	CLR_BIT(*TCCR0,CS00);
	CLR_BIT(*TCCR0,CS01);
	CLR_BIT(*TCCR0,CS02);
}

void	TIMER0_voidWritePWM(u8 pwm_val)
{
	(*OCR0) = pwm_val;
}

void	TIMER0_voidWritePWM_MAPED(u8 pwm_val)
{
	
	(*OCR0) = ((pwm_val*256)/100);
}

void	TIMER0_voidGetTCNT(u8 *buffer)
{
	*buffer = *TCNT0;
}

void	TIMER0_voidGetOCR(u8 *buffer)
{
	*buffer = *OCR0;
}

void	TIMER0_voidSet_COMP_CallBack( void (*ptr)(void) )
{
	TIMER0_COMP_CALLBACK = ptr;
}

void	TIMER0_voidSet_OVF_CallBack( void (*ptr)(void) )
{
	TIMER0_OVF_CALLBACK = ptr;
}

void __vector_10(void) 
__attribute__((signal, used, externally_visible)); // to avoid optimization (TIMER0 COMP ISR)
void __vector_10(void) {
	TIMER0_COMP_CALLBACK();
}

void __vector_11(void)
__attribute__((signal, used, externally_visible)); // to avoid optimization (TIMER0 OVF ISR)
void __vector_11(void) {
	TIMER0_OVF_CALLBACK();
}
