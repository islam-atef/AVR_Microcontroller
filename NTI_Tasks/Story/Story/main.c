/**
 * @file  Game_1.c
 * @author islam_atef (islam_atef@domain.com)
 * @brief   PingPong Game.
 * @version 0.1
 * @date 2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */

/*  include Section starts  */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include <util/delay.h>
/*  include Section Ends  */


/*  MACRO Section starts  */
/*  MACRO Section Ends  */


/*  Global Variables Section starts  */
u8  BUTTONS[4] = {GPIO_PD5,GPIO_PD3,GPIO_PD6,GPIO_PD7};
const u8	customChar_Lamb[]	   = {0B10001, 0B01110, 0B00100, 0B01110, 0B10101, 0B10101, 0B01010, 0B01010};
const u8	customChar_axe[]	   = {0B00000, 0B10000, 0B01000, 0B00100, 0B00010, 0B00111, 0B00110, 0B00000};
const u8	customChar_Heart[]	   = {0B00000, 0B00000, 0B01010, 0B11111, 0B01110, 0B00100, 0B00000, 0B00000};
const u8	customChar_R_heart[]   = {0B01100, 0B11110, 0B11111, 0B11111, 0B01111, 0B00111, 0B00011, 0B00001};
const u8	customChar_L_heart[]   = {0B00110, 0B01111, 0B11111, 0B11111, 0B11110, 0B11100, 0B11000, 0B10000};
const u8	customChar_wolf[]	   = {0B01010, 0B11011, 0B01110, 0B10101, 0B11111, 0B01110, 0B01110, 0B00100};		
/*  Global Variables Section Ends  */


/*  Sub_program Declaration Section starts  */
void	Store_Element(void);
void	Initiate_Buttons(void);
u8		TakeInput(void);
void	page_1(void);
void	page_2(void);
void	page_3(void);
void	page_4(void);
void	page_5(void);
void	page_6(void);
void	page_7(void);
void	page_8(void);
void	page_9(void);
void	page_10(void);
void	Show_Page(u8 num);
/*  Sub_program Declaration Section Ends  */

/*  Main Function Section starts  */
int main() 
{
	GPIO_Init();
	Initiate_Buttons();
	LCD_Init();
	Store_Element();
	_delay_ms(100);
	
	Show_Page(1);
	page_1();
	_delay_ms(15000);
	LCD_ClearDisplay();
	Show_Page(2);
	page_2();
	_delay_ms(15000);
	LCD_ClearDisplay();
	Show_Page(3);
	page_3();
	_delay_ms(15000);
	LCD_ClearDisplay();
	Show_Page(4);
	page_4();
	_delay_ms(15000);
	LCD_ClearDisplay();
	Show_Page(5);
	page_5();
	_delay_ms(15000);
	LCD_ClearDisplay();
	Show_Page(6);
	page_6();
	_delay_ms(15000);
	LCD_ClearDisplay();
	Show_Page(7);
	page_7();
	_delay_ms(15000);
	LCD_ClearDisplay();
	Show_Page(8);
	page_8();
	_delay_ms(15000);
	LCD_ClearDisplay();
	Show_Page(9);
	page_9();
	_delay_ms(25000);
	LCD_ClearDisplay();
	Show_Page(10);
	page_10();
	while (1) 
	{}
	return 0;
}
/*  Main Function Section Ends  */


/*  Sub_program Section starts  */
/*-------------------------------------------------------------------*/
void	Show_Page(u8 num)
{
	LCD_GoTo_xy(0,0);
	LCD_WriteNumber(num);
	LCD_WriteString("/10");
}
/*-------------------------------------------------------------------*/
void	page_1()
{
	// title.
	LCD_GoTo_xy(1,4);
	LCD_WriteString("The Lamb and ");
	LCD_GoTo_xy(2,3);
	LCD_WriteString("The Wolf Story");
	LCD_GoTo_xy(3,8);
	LCD_WriteChar(0x02);
	LCD_GoTo_xy(3,11);
	LCD_WriteChar(0x07);
}
/*-------------------------------------------------------------------*/
void	page_2()
{
	LCD_GoTo_xy(1,0);
	LCD_WriteChar(0x07);
	LCD_WriteString(":   Lamb,Tell me ");
	LCD_GoTo_xy(2,6);
	LCD_WriteString(" a Story ");
	
}
/*-------------------------------------------------------------------*/
void	page_3()
{
	LCD_GoTo_xy(1,0);
	LCD_WriteChar(0x02);
	LCD_WriteString(": There was once ");
	LCD_GoTo_xy(2,0);
	LCD_WriteString("a pale man with dark"); 
	LCD_GoTo_xy(3,0);
	LCD_WriteString("        hair,");
	_delay_ms(13000);
	LCD_ClearDisplay();
	Show_Page(3);
	LCD_GoTo_xy(2,0);
	LCD_WriteString(" who was very lonely");
}
/*-------------------------------------------------------------------*/
void	page_4()
{
	LCD_GoTo_xy(1,0);
	LCD_WriteChar(0x07);
	LCD_WriteString(": Why was it Lonely");
	LCD_GoTo_xy(2,9);
	LCD_WriteChar('?');
}
/*-------------------------------------------------------------------*/
void	page_5()
{
	LCD_GoTo_xy(1,0);
	LCD_WriteChar(0x02);
	LCD_WriteString(": All Things must ");
	LCD_GoTo_xy(2,0);
	LCD_WriteString("meet this man,So...");
	_delay_ms(13000);
	LCD_ClearDisplay();
	Show_Page(5);
	LCD_GoTo_xy(2,0);
	LCD_WriteString("They Shunned him.");
}	
/*-------------------------------------------------------------------*/
void	page_6()
{
	LCD_GoTo_xy(1,0);
	LCD_WriteChar(0x07);
	LCD_WriteString(":  Did he Chase ");
	LCD_GoTo_xy(2,5);
	LCD_WriteString("Them all");
	LCD_GoTo_xy(3,9);
	LCD_WriteChar('?');
}
/*-------------------------------------------------------------------*/
void	page_7()
{
	LCD_GoTo_xy(1,0);
	LCD_WriteChar(0x02);
	LCD_WriteString(": He took an Axe");
	LCD_GoTo_xy(2,5);
	LCD_WriteString(" and Split");
	LCD_GoTo_xy(3,3);
	LCD_WriteString("himself in two");
	_delay_ms(13000);
	LCD_ClearDisplay();
	Show_Page(7);
	LCD_GoTo_xy(1,9);
	LCD_WriteChar(0x03);
	LCD_WriteChar(0x04);
	LCD_GoTo_xy(2,0);
	LCD_WriteString("   Right, Down ");
	LCD_GoTo_xy(3,0);
	LCD_WriteString("     , The Middle");
	_delay_ms(8000);
	LCD_GoTo_xy(1,9);
	LCD_WriteChar(0x05);
	LCD_WriteChar(0x06);
}
/*-------------------------------------------------------------------*/
void	page_8()
{
	LCD_GoTo_xy(1,0);
	LCD_WriteChar(0x07);
	LCD_WriteString(":  So, he would ");
	LCD_GoTo_xy(2,0);
	LCD_WriteString("always have a Friend");
	LCD_GoTo_xy(3,9);
	LCD_WriteChar('!');
}
/*-------------------------------------------------------------------*/
void	page_9()
{
	LCD_GoTo_xy(1,0);
	LCD_WriteChar(0x02);
	LCD_WriteString(":  So, he would ");
	LCD_GoTo_xy(2,0);
	LCD_WriteString("always have a Friend");
}
/*-------------------------------------------------------------------*/
void	page_10()
{
	LCD_GoTo_xy(1,0);
	LCD_WriteString("DO you Recognize the");
	LCD_GoTo_xy(2,7);
	LCD_WriteString(" Man");
	LCD_GoTo_xy(3,9);
	LCD_WriteChar('?');
}
/*-------------------------------------------------------------------*/
u8		TakeInput()
{
	u8 returned_val;
	// BUTTONS[4] = {GPIO_PD3,GPIO_PD5,GPIO_PD6,GPIO_PD7};
	for(u8 i=0 ; i<4 ; i++)
	{
		if (!GPIO_ReadValue_Pin(BUTTONS[i]))
		{
			returned_val = i+1;
			break;
		}
		else
		{
			returned_val = 0;
		}
	}
	return returned_val;
}
/*-------------------------------------------------------------------*/
void	Initiate_Buttons()
{
	GPIO_SetValue_Pin(GPIO_PD7,HIGH);
	GPIO_SetValue_Pin(GPIO_PD6,HIGH);
	GPIO_SetValue_Pin(GPIO_PD5,HIGH);
	GPIO_SetValue_Pin(GPIO_PD3,HIGH);
}
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
void	Store_Element()
{
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_Lamb,0x02);
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_axe,0x03);
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_Heart,0x04);
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_R_heart,0x05);
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_L_heart,0x06);
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_wolf,0x07);
}
/*-------------------------------------------------------------------*/
/*  Sub_program Section Ends  */