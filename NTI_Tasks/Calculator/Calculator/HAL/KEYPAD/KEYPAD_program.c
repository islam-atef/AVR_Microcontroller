/*  include Section starts  */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/GPIO/GPIO_interface.h"

#include "KEYPAD_interface.h"
#include "KEYPAD_config.h"
/*  include Section Ends  */

/*  MACRO Section starts  */
/*  MACRO Section Ends  */

/*  Global Variables Section starts  */
const u8 COLU_ARRAY[4] = {COLU_1, COLU_2, COLU_3, COLU_4};
const u8 Data_Array[4][4] = {{'7', '8', '9', '/'},
                             {'4', '5', '6', '*'},
                             {'1', '2', '3', '-'},
                             {'c', '0', '=', '+'}};
/*  Global Variables Section Ends  */

static void ROWS_Activation(u8 row_num);

/// @brief  this Function is used to get a character value from the KEYPAD.
/// @return
u8 KEYPAD_Read() {
  u8 returned_Val = '\0';
  // Check Row_1:
  ROWS_Activation(ROW_1);
  for (int i = 0; i < 4; i++) {
    if (!(GPIO_ReadValue_Pin(COLU_ARRAY[i]))) {
      returned_Val = Data_Array[0][i];
      while (!GPIO_ReadValue_Pin(COLU_ARRAY[i]))
        ;
    }
  }
  ROWS_Activation(ROW_2);
  for (int i = 0; i < 4; i++) {
    if (!(GPIO_ReadValue_Pin(COLU_ARRAY[i]))) {
      returned_Val = Data_Array[1][i];
      while (!GPIO_ReadValue_Pin(COLU_ARRAY[i]))
        ;
    }
  }
  ROWS_Activation(ROW_3);
  for (int i = 0; i < 4; i++) {
    if (!(GPIO_ReadValue_Pin(COLU_ARRAY[i]))) {
      returned_Val = Data_Array[2][i];
      while (!GPIO_ReadValue_Pin(COLU_ARRAY[i]))
        ;
    }
  }
  ROWS_Activation(ROW_4);
  for (int i = 0; i < 4; i++) {
    if (!(GPIO_ReadValue_Pin(COLU_ARRAY[i]))) {
      returned_Val = Data_Array[3][i];
      while (!GPIO_ReadValue_Pin(COLU_ARRAY[i]))
        ;
    }
  }
  return returned_Val;
}

/*--------------------------------------------------------------------------*/
static void ROWS_Activation(u8 row_num) {
  // Set All Rows.
  GPIO_SetValue_Pin(ROW_1, HIGH);
  GPIO_SetValue_Pin(ROW_2, HIGH);
  GPIO_SetValue_Pin(ROW_3, HIGH);
  GPIO_SetValue_Pin(ROW_4, HIGH);
  // Reset the given Row.
  GPIO_SetValue_Pin(row_num, LOW);
}