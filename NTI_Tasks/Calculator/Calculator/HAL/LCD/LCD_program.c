/**
 * @file LCD_program.c
 * @author islam_atef (islam_atef@domain.com)
 * @brief   LCD program file.
 * @version 0.1
 * @date 2023-10-19
 *
 * @copyright Copyright (c) 2023
 *
 */
/*  include Section starts  */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/GPIO/GPIO_interface.h"
#include <util/delay.h>

#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_private.h"
/*  include Section Ends  */
#define F_CPU 8000000UL
/*-----------------------------------------------------------------------------------------------------*/
static void SendInstruction(u8 inst);
static void SendData(u8 Data);
/*-----------------------------------------------------------------------------------------------------*/

/// @brief  initialization Function.
/// @param  No parameters.
void LCD_Init(void) {
#if LCD_MODE == _4_PIN_MODE_
  // 1- Delay 35 ms.
  _delay_ms(50);
  // 2 - enter the Instructions.
  SendInstruction(0x02);
  SendInstruction(0x28);
  SendInstruction(0x0c);
  SendInstruction(0x01);
  _delay_ms(1);
  SendInstruction(0x06);
  _delay_ms(2);
#elif LCD_MODE == _8_PIN_MODE_
#endif
}

/// @brief  Write Character on the LCD.
/// @param characters
void LCD_WriteChar(u8 character) { SendData(character); }

void LCD_WriteString(u8* str) { 
	for (int i=0; str[i] != '\0' ; i++)
	{
		SendData(str[i]);
	}
}


void LCD_WriteNumber(s32 num)
{
	u8 str[10],i=0,j;
	if (num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if (num<0)
	{
		num=num*(-1);
		LCD_WriteChar('-');
	}
	while(num)
	{
		str[i]=num%10 +'0';
		i++;
		num=num/10;
	}
	for (j=i;j>0;j--)
	{
		LCD_WriteChar(str[j-1]);
	}
}

/// @brief
/// @param num
void LCD_ClearDisplay() {
	_delay_ms(1); 
	SendInstruction(0x01);
	_delay_ms(50);
	 }

void LCD_GoTo_xy(u8 x_position, u8 y_position) {
	u8 Local_u8address;
	switch(x_position)
	{
		case 0:
		Local_u8address = y_position + (0x80);
		break;
		case 1:
		Local_u8address = y_position + (0xc0);
		break;
		case 2:
		Local_u8address = y_position + (0x94);
		break;
		case 3:
		Local_u8address = y_position + (0xd4);
		break;
		default:
		break;
	}
	SendInstruction(Local_u8address);
	//_delay_ms(2);
}


	/// @brief
	/// @param ptr_Pattern
	/// @param Pattern_Num
	/// @param x_position
	/// @param y_position
	void LCD_Save_SpecialCharacter(u8 *ptr_Pattern, u8 Pattern_Num) {
		u8 counter;
		/* Send CGRam address command to LCD ,with setting  bit 6*/
		SendInstruction(Pattern_Num * 8 + 0x40);
		/* Write pattern in CG Ram */
		for (counter = 0; counter < 8; counter++) {
			SendData(ptr_Pattern[counter]);
		}
		SendInstruction(0x80);
	}
/*-----------------------------------------------------------------------------------------------------*/
static void SendInstruction(u8 inst) {
#if LCD_MODE == _4_PIN_MODE_
  // 1 - RS ----> Low.
  GPIO_SetValue_Pin(RS_Pin, LOW);
  // 3 - write the first half of the instruction.
  GPIO_SetValue_Pin(DB_4, GET_BIT(inst, 4));
  GPIO_SetValue_Pin(DB_5, GET_BIT(inst, 5));
  GPIO_SetValue_Pin(DB_6, GET_BIT(inst, 6));
  GPIO_SetValue_Pin(DB_7, GET_BIT(inst, 7));
  // 4 - E ------> High.
  GPIO_SetValue_Pin(Enable_Pin, HIGH);
  // 5 - Wait (1 mS).
  _delay_ms(1);
  // 6 - E ------> Low.
  GPIO_SetValue_Pin(Enable_Pin, LOW);
  // 7 - Wait (1 mS).
  _delay_ms(1);
  // 8 - write the first half of the instruction.
  GPIO_SetValue_Pin(DB_4, GET_BIT(inst, 0));
  GPIO_SetValue_Pin(DB_5, GET_BIT(inst, 1));
  GPIO_SetValue_Pin(DB_6, GET_BIT(inst, 2));
  GPIO_SetValue_Pin(DB_7, GET_BIT(inst, 3));
  // 9 - E ------> High.
  GPIO_SetValue_Pin(Enable_Pin, HIGH);
  // 10 - Wait (1 mS).
  _delay_ms(1);
  // 11 - E ------> Low.
  GPIO_SetValue_Pin(Enable_Pin, LOW);
  // 12 - Wait (1 mS).
  _delay_ms(1);
#elif LCD_MODE == _8_PIN_MODE_
#endif
}

static void SendData(u8 Data) {
#if LCD_MODE == _4_PIN_MODE_
  // 1 - RS ----> High.
  GPIO_SetValue_Pin(RS_Pin, HIGH);
  // 3 - write the first half of the instruction.
  GPIO_SetValue_Pin(DB_4, GET_BIT(Data, 4));
  GPIO_SetValue_Pin(DB_5, GET_BIT(Data, 5));
  GPIO_SetValue_Pin(DB_6, GET_BIT(Data, 6));
  GPIO_SetValue_Pin(DB_7, GET_BIT(Data, 7));
  // 4 - E ------> High.
  GPIO_SetValue_Pin(Enable_Pin, HIGH);
  // 5 - Wait (1 mS).
  _delay_ms(1);
  // 6 - E ------> Low.
  GPIO_SetValue_Pin(Enable_Pin, LOW);
  // 7 - Wait (1 mS).
  _delay_ms(1);
  // 8 - write the first half of the instruction.
  GPIO_SetValue_Pin(DB_4, GET_BIT(Data, 0));
  GPIO_SetValue_Pin(DB_5, GET_BIT(Data, 1));
  GPIO_SetValue_Pin(DB_6, GET_BIT(Data, 2));
  GPIO_SetValue_Pin(DB_7, GET_BIT(Data, 3));
  // 9 - E ------> High.
  GPIO_SetValue_Pin(Enable_Pin, HIGH);
  // 10 - Wait (1 mS).
  _delay_ms(1);
  // 11 - E ------> Low.
  GPIO_SetValue_Pin(Enable_Pin, LOW);
  // 12 - Wait (1 mS).
  _delay_ms(1);
#elif LCD_MODE == _8_PIN_MODE_
#endif
}