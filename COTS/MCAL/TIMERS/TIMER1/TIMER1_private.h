/*
 * TIMER1_private.h
 *
 * Created: 10/27/2023 10:34:24 AM
 *  Author: Islam Atef
 */ 
#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0


/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0


/* Timer 1 */
#define ICR1    (volatile u16*)(0x46)
#define ICR1L    (volatile u8*)(0x46)
#define ICR1H    (volatile u8*)(0x47)

#define OCR1B    (volatile u16*)(0x48)
#define OCR1BL    (volatile u8*)(0x48)
#define OCR1BH    (volatile u8*)(0x49)

#define OCR1A    (volatile u16*)(0x4A)
#define OCR1AL    (volatile u8*)(0x4A)
#define OCR1AH    (volatile u8*)(0x4B)

#define TCNT1   (volatile u16*)(0x4C)
#define TCNT1L   (volatile u8*)(0x4C)
#define TCNT1H   (volatile u8*)(0x4D)

#define TCCR1B   (volatile u8*)(0x4E)
#define TCCR1A   (volatile u8*)(0x4F)

#define TIFR    (volatile u8*)(0x58)
#define TIMSK   (volatile u8*)(0x59)

#endif /* TIMER0_PRIVATE_H_ */