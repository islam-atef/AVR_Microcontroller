/************************************************************************/
#ifndef GPIO_CONFIG_H
#define GPIO_CONFIG_H
/************************************************************************/
/*______________________________________________________________________*/
#define INPUT 0
#define OUTPUT 1
/*______________________________________________________________________*/

/*______________________________________________________________________*/
#define A0 INPUT
#define A1 INPUT
#define A2 INPUT
#define A3 INPUT
#define A4 INPUT
#define A5 INPUT
#define A6 INPUT
#define A7 INPUT

#define PORTA_DIRECTION HELPER(A7, A6, A5, A4, A3, A2, A1, A0)
/*______________________________________________________________________*/
/*______________________________________________________________________*/
#define B0 INPUT
#define B1 INPUT
#define B2 INPUT
#define B3 INPUT
#define B4 INPUT
#define B5 INPUT
#define B6 INPUT
#define B7 INPUT

#define PORTB_DIRECTION HELPER(B7, B6, B5, B4, B3, B2, B1, B0)
/*______________________________________________________________________*/
/*______________________________________________________________________*/
#define C0 INPUT
#define C1 INPUT
#define C2 INPUT
#define C3 INPUT
#define C4 INPUT
#define C5 INPUT
#define C6 INPUT
#define C7 INPUT

#define PORTC_DIRECTION HELPER(C7, C6, C5, C4, C3, C2, C1, C0)
/*______________________________________________________________________*/
/*______________________________________________________________________*/
#define D0 INPUT
#define D1 INPUT
#define D2 INPUT
#define D3 INPUT
#define D4 INPUT
#define D5 INPUT
#define D6 INPUT
#define D7 INPUT

#define PORTD_DIRECTION HELPER(D7, D6, D5, D4, D3, D2, D1, D0)
/*______________________________________________________________________*/

/************************************************************************/
#endif