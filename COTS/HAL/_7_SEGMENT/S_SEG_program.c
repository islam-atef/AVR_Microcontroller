#include "../../LIB/BIT_MATH..h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/GPIO/GPIO_interface.h"

#include "S_SEG_config.h"
#include "S_SEG_interface.h"

///////////////////////////////////////////////////////////////////////////////////

/// @brief SEG_CONTROL : this function control the activation of the seven
/// segment.
/// @param pin : the pin that we will control {PIN_1_c / PIN_2_c / PIN_3_c /
/// PIN_4_c}.
/// @param state : the State of the seven segment {ON / OFF}.
void SEG_CONTROL(u8 pin, u8 state) { GPIO_SetValue_Pin(pin, state); }

///////////////////////////////////////////////////////////////////////////////////
char const _7_segment_Normal[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111100, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01100111, // 9

    0b10000000 // DOT
};

char const _7_segment_BCD[] = {
    0, // 0
    1, // 1
    2, // 2
    3, // 3
    4, // 4
    5, // 5
    6, // 6
    7, // 7
    8, // 8
    9  // 9
       // 0b10000000 // DOT
};
///////////////////////////////////////////////////////////////////////////////////

/// @brief
/// @param SEVEN_SEGMENT_NUM
void SEG_SHOW(u8 SEVEN_SEGMENT_NUM) {
#if S_SEG_TYPE == BCD
  // Clear All Pins.
  GPIO_SetValue_Pin(pin_1, LOW);
  GPIO_SetValue_Pin(pin_2, LOW);
  GPIO_SetValue_Pin(pin_3, LOW);
  GPIO_SetValue_Pin(pin_4, LOW);
  // Write The Value.
  GPIO_SetValue_Pin(pin_1, GET_BIT(_7_segment_BCD[SEVEN_SEGMENT_NUM], 0));
  GPIO_SetValue_Pin(pin_2, GET_BIT(_7_segment_BCD[SEVEN_SEGMENT_NUM], 1));
  GPIO_SetValue_Pin(pin_3, GET_BIT(_7_segment_BCD[SEVEN_SEGMENT_NUM], 2));
  GPIO_SetValue_Pin(pin_4, GET_BIT(_7_segment_BCD[SEVEN_SEGMENT_NUM], 3));
#endif
}
