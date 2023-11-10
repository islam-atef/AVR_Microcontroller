/*
              ----A----
                  -       -
                  -       -
                  -       -
                  -       -
                  F       B
                  -       -
                  -       -
                  -       -
                  -       -
                  ----G----
                  -       -
                  -       -
                  -       -
                  -       -
                  E       c
                  -       -
                  -       -
                  -       -
                  -       -
                  ----D----
*/
#ifndef S_SEG_CONFIG_H
#define S_SEG_CONFIG_H

/////////////////////////////////////////////////////////////////////////////////////
#define BCD 0
#define Normal 1
#define S_SEG_TYPE BCD
/////////////////////////////////////////////////////////////////////////////////////

/* This Part Is Configurable */

/* Output Part */
// Data Pins :
#define pin_1 0

#define pin_2 0

#define pin_3 0

#define pin_4 0

#if S_SEG_TYPE == Normal
#define pina 0

#define pinb 0

#define pinc 0

#define pind 0

#define pine 0

#define pinf 0

#define ping 0

#define DOT 0
#endif

// control Pin :
#define pin_1_C PA3
#define pin_2_C PA2
#define pin_3_C PB5
#define pin_4_C PB6

///////////////////////////////////////////////

#endif
