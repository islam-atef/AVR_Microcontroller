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
#ifndef S_SEG_INTERFACE_H
#define S_SEG_INTERFACE_H
////////////////////////////////////////////////

#define dot_C 10

///////////////////////////////////////////////

#define ON 0
#define OFF 1

///////////////////////////////////////////////

/// @brief SEG_CONTROL : this function control the activation of the seven
/// segment.
/// @param pin : the pin that we will control {PIN_1_c / PIN_2_c / PIN_3_c /
/// PIN_4_c}.
/// @param state : the State of the seven segment {ON / OFF}.
void SEG_CONTROL(u8 pin, u8 state);

/// @brief
/// @param SEVEN_SEGMENT_NUM
void SEG_SHOW(u8 SEVEN_SEGMENT_NUM);

#endif
