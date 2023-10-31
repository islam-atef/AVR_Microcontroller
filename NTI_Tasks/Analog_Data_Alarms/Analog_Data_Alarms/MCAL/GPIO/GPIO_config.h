/************************************************************************/
#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H
/************************************************************************/
/*______________________________________________________________________*/
#define INPUT 0
#define OUTPUT 1
/*______________________________________________________________________*/

/*______________________________________________________________________*/
#define CONCATE(b7, b6, b5, b4, b3, b2, b1, b0)                                \
(0b##b7##b6##b5##b4##b3##b2##b1##b0)

#define HELPER(b7, b6, b5, b4, b3, b2, b1, b0)                                 \
CONCATE(b7, b6, b5, b4, b3, b2, b1, b0)
/*______________________________________________________________________*/

/*______________________________________________________________________*/
#define A0 INPUT
#define A1 INPUT
#define A2 OUTPUT
#define A3 OUTPUT
#define A4 INPUT
#define A5 INPUT
#define A6 INPUT
#define A7 INPUT

#define PORTA_DIRECTION HELPER(A7, A6, A5, A4, A3, A2, A1, A0)
/*______________________________________________________________________*/
/*______________________________________________________________________*/
#define B0 OUTPUT
#define B1 OUTPUT
#define B2 OUTPUT
#define B3 OUTPUT
#define B4 OUTPUT
#define B5 OUTPUT
#define B6 OUTPUT
#define B7 OUTPUT

#define PORTB_DIRECTION HELPER(B7, B6, B5, B4, B3, B2, B1, B0)
/*______________________________________________________________________*/
/*______________________________________________________________________*/
#define C0 OUTPUT
#define C1 OUTPUT
#define C2 OUTPUT
#define C3 OUTPUT
#define C4 INPUT
#define C5 INPUT
#define C6 OUTPUT
#define C7 INPUT

#define PORTC_DIRECTION HELPER(C7, C6, C5, C4, C3, C2, C1, C0)
/*______________________________________________________________________*/
/*______________________________________________________________________*/
#define D0 INPUT
#define D1 INPUT
#define D2 OUTPUT
#define D3 INPUT
#define D4 INPUT
#define D5 INPUT
#define D6 INPUT
#define D7 OUTPUT

#define PORTD_DIRECTION HELPER(D7, D6, D5, D4, D3, D2, D1, D0)
/*______________________________________________________________________*/

/************************************************************************/
#endif