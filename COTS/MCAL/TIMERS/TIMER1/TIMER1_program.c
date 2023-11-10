/*
 * TIMER1_program.c
 *
 * Created: 10/27/2023 10:33:40 AM
 *  Author: Islam Atef
 */ 
/*----------------------------------------------------------------------------------------------------*/
#include "../../../LIB/BIT_MATH.h"
#include "../../../LIB/STD_TYPES.h"

#include "TIMER1_interface.h"
#include "TIMER1_config.h"
#include "TIMER1_private.h"
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
static void (* TIMER1_ICI_CALLBACK )(void) = NULL;
static void (* TIMER1_OCMA_CALLBACK)(void) = NULL;
static void (* TIMER1_OCMB_CALLBACK)(void) = NULL;
static void (* TIMER1_OVF_CALLBACK )(void) = NULL;
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidInit(void)
{
	// set the Mode;
	/*
	*TCCR1A = (1<<WGM11)|(1<<COM1A1);
	*TCCR1B = (1<<WGM12)|(1<<WGM13);
	*/
	// enable the interrupt.
	*TIMSK |= (1<<TICIE1);
}
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidStart()
{
	// set the Clock source.
	(*TCCR1B)	|=	(TIMER1_CLOCK_SOURCE << CS10);
}
void	TIMER1_voidStop()
{
	// Terminate the Clock source.
	CLR_BIT(*TCCR1B,CS10);
	CLR_BIT(*TCCR1B,CS11);
	CLR_BIT(*TCCR1B,CS12);
}
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidWritePWM_OCRA(u16 pwm_val)
{
	*OCR1A = pwm_val;
}
void	TIMER1_voidWritePWM_OCRA_MAPED(u8 pwm_val)
{
	(*OCR1A) = ((pwm_val*256)/100);
}
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidWritePWM_OCRB(u16 pwm_val)
{
	(*OCR1B) = pwm_val;
}
void	TIMER1_voidWritePWM_OCRB_MAPED(u8 pwm_val)
{
	(*OCR1B) = ((pwm_val*256)/100);
}
/*----------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidSetTCNT(u16 buffer)
{
	*TCNT1 = buffer;
}
void	TIMER1_voidGetTCNT(u16 *buffer)
{
	*buffer = *TCNT1;
}
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidSetOCRA(u16 buffer)
{
	*OCR1A = buffer;
}
void	TIMER1_voidGetOCRA(u16 *buffer)
{
	*buffer = *OCR1A;
}
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidSetOCRB(u16 buffer)
{
	*OCR1B = buffer;
}
void	TIMER1_voidGetOCRB(u16 *buffer)
{
	*buffer = *OCR1B;
}
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidSetICR(u16 buffer)
{
	*ICR1 = buffer;
}
void	TIMER1_voidGetICR(u16 *buffer)
{
	*buffer = *ICR1;
}
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidChange_ICR_TRIG(ICI_TIGG_TYPE Trigger_val)
{
	CLR_BIT(*TCCR1B,ICES1);
	*TCCR1B |= (Trigger_val<<ICES1);
}
/*----------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------*/
void	TIMER1_voidSet_ICI_CallBack( void (*ptr)(void) )
{
	TIMER1_ICI_CALLBACK = ptr;
}
void	TIMER1_voidSet_OCMA_CallBack( void (*ptr)(void) )
{
	TIMER1_OCMA_CALLBACK = ptr;
}
void	TIMER1_voidSet_OCMB_CallBack( void (*ptr)(void) )
{
	TIMER1_OCMB_CALLBACK = ptr;
}
void	TIMER1_voidSet_OVF_CallBack( void (*ptr)(void) )
{
	TIMER1_OVF_CALLBACK = ptr;
}
/*----------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------*/
void __vector_6(void)  __attribute__((signal, used, externally_visible)); // to avoid optimization (TIMER0 COMP ISR)
void __vector_6(void) 
{
	TIMER1_ICI_CALLBACK();
}
/*----------------------------------------------------------------------------------------------------*/
void __vector_7(void) __attribute__((signal, used, externally_visible)); // to avoid optimization (TIMER0 OVF ISR)
void __vector_7(void) 
{
	TIMER1_OCMA_CALLBACK();
}
/*----------------------------------------------------------------------------------------------------*/
void __vector_8(void) __attribute__((signal, used, externally_visible)); // to avoid optimization (TIMER0 COMP ISR)
void __vector_8(void)
{
	TIMER1_OCMB_CALLBACK();
}
/*----------------------------------------------------------------------------------------------------*/
void __vector_9(void) __attribute__((signal, used, externally_visible)); // to avoid optimization (TIMER0 OVF ISR)
void __vector_9(void)
{
	TIMER1_OVF_CALLBACK();
}
/*----------------------------------------------------------------------------------------------------*/