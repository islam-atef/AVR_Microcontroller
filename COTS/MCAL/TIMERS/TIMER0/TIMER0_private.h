/*
 * TIMER0_private.h
 *
 * Created: 10/27/2023 10:34:24 AM
 *  Author: Islam Atef
 */ 


#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/* TIMSK */
#define OCIE0   1
#define TOIE0   0


/* TIFR */
#define OCF0    1
#define TOV0    0


/* Timer 0 */
#define TCNT0   (volatile u8*)(0x52)
#define TCCR0   (volatile u8*)(0x53)
#define OCR0    (volatile u8*)(0x5C)
#define TIFR    (volatile u8*)(0x58)
#define TIMSK   (volatile u8*)(0x59)


#endif /* TIMER0_PRIVATE_H_ */