#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

/// @brief  initialization Function.
/// @param  No parameters.
void LCD_Init(void);

/// @brief  Write Character on the LCD.
/// @param character
void LCD_WriteChar(u8 character);

/// @brief Write String on the LCD.
/// @param str
void LCD_WriteString(u8 *str);

/// @brief
/// @param num
void LCD_WriteNumber(s32 num);

/// @brief
/// @param num
void LCD_ClearDisplay(void);

/// @brief
/// @param x_position
/// @param y_position
void LCD_GoTo_xy(u8 x_position, u8 y_position);

/// @brief this function is used to store a custom character in the LCD.
/// @param ptr_Pattern
/// @param Pattern_Num
void LCD_Save_SpecialCharacter(u8 *ptr_Pattern, u8 Pattern_Num);
#endif
