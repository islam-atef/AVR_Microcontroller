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
//u8	Player_1_Position[2] = {0,0};
//u8	Player_2_Position[2] = {0,19};
u8	Ball_Position[2];
u8	Score[2] ;
u8	Flag_G_Val;
u8	Player_1_pos;
u8	Player_2_pos;
u8  BUTTONS[4] = {GPIO_PD5,GPIO_PD3,GPIO_PD6,GPIO_PD7};
const u8	customChar_Player_1[] = {0B00010, 0B00110, 0B00110, 0B00110, 0B00110, 0B00110, 0B01010, 0B10000};
const u8	customChar_Player_2[] = {0B01000, 0B01100, 0B01100, 0B01100, 0B01100, 0B01100, 0B01010, 0B00001};
const u8	customChar_BALL[]     = {0B00000, 0B00100, 0B01110, 0B11111, 0B01110, 0B00100, 0B00000, 0B00000};
const u8	customChar_NET[]	  = {0B00100, 0B00000, 0B00100, 0B00000, 0B00100, 0B00000, 0B00100, 0B00000};
/*  Global Variables Section Ends  */


/*  Sub_program Declaration Section starts  */
void	Player_1(u8 new_pos);
void	Player_2(u8 new_pos);
void	Ball(u8 *Ball_pos);
void	Store_Element(void);
void	Initiate_Buttons(void);
void	Show_Score(void);
void	Show_Net(void);
void	Speed(void);
void	GamePlay(u8 input_);
void	BallMovement(void);
u8		TakeInput(void);
void	Start(void);
/*  Sub_program Declaration Section Ends  */


/*  Main Function Section starts  */
int main() 
{
	GPIO_Init();
	Initiate_Buttons();
	LCD_Init();
	Store_Element();
	_delay_ms(100);
	Start();
	while (1) 
	{
		GamePlay(TakeInput());
		BallMovement();
		/*-------------------------------*/
		Show_Net();
		Show_Score();
		Speed();
	}
	return 0;
}
/*  Main Function Section Ends  */


/*  Sub_program Section starts  */
/*-------------------------------------------------------------------*/
void	Start()
{
	u8 arr[] = {0,1};
	LCD_WriteString("Welcome To The Game!");
	while(TakeInput() == 0);
	LCD_ClearDisplay();
	Player_1(0);
	Player_2(0);
	Show_Net();
	Ball(arr);
	Show_Score();
}
/*-------------------------------------------------------------------*/
void	Player_1(u8 new_pos)
{
	static u8 Old_position ;
	// Clear the Old place.
	LCD_GoTo_xy(Old_position,0);
	LCD_WriteChar(' ');
	Old_position = new_pos ;
	LCD_GoTo_xy(Old_position,0);
	LCD_WriteChar(0x02);
}
/*-------------------------------------------------------------------*/
void	Player_2(u8 new_pos)
{
	static u8 Old_position ;
	// Clear the Old place.
	LCD_GoTo_xy(Old_position,19);
	LCD_WriteChar(' ');
	Old_position = new_pos ;
	LCD_GoTo_xy(Old_position,19);
	LCD_WriteChar(0x03);
}
/*-------------------------------------------------------------------*/
void	Ball(u8 *Ball_pos)
{
	static u8 Old_position[2] = {1,0};
	// Clear the Old place.
	LCD_GoTo_xy(Old_position[0],Old_position[1]);
	if(Old_position[1] != 0 || Old_position[1] != 19)
	{
		LCD_WriteChar(' ');
		Old_position[0] = Ball_pos[0];
		Old_position[1] = Ball_pos[1];
		LCD_GoTo_xy(Old_position[0],Old_position[1]);
		LCD_WriteChar(0x04);
	}
	else
	{
		Old_position[0] = Ball_pos[0];
		Old_position[1] = Ball_pos[1];
		LCD_GoTo_xy(Old_position[0],Old_position[1]);
	}
}
/*-------------------------------------------------------------------*/
void	GamePlay(u8 input_)
{
	if(!Flag_G_Val)
	{
		switch(input_)
		{
			case 1:
				if (Ball_Position[1] <= 9) 
				{
					if (Ball_Position[0] < 2) 
					{
						Ball_Position[0]++;
					}
					Ball(Ball_Position);
				} else {
					if (Player_1_pos < 2) {
						Player_1_pos++;
					}
					Player_1(Player_1_pos);
				}
			break;
			case 2:
				if (Ball_Position[1] <= 9) 
				{
					if (Ball_Position[0] > 0)
					{
						Ball_Position[0]--;
					}
					Ball(Ball_Position);
				} else {
					if (Player_1_pos > 0)
					{
						Player_1_pos--;
					}
					Player_1(Player_1_pos);
				}
				break;	
			case 3:
					if (Player_2_pos < 2)
					{
						Player_2_pos++;
					}
					Player_2(Player_2_pos);
				break;
			case 4:
					if(Player_2_pos > 0)
					{
						Player_2_pos--;
					}
					Player_2(Player_2_pos);
				break;
			default:
				Player_2(Player_2_pos);
				Player_1(Player_1_pos);
			break;
		}
	}
	else
	{
		switch(input_)
		{
			case 3:
				if (Ball_Position[1] > 9)
				{
					if (Ball_Position[0] < 2)
					{
						Ball_Position[0]++;
					}
					Ball(Ball_Position);
				} else {
					if (Player_2_pos < 2)
					{
						Player_2_pos++;
					}
					Player_2(Player_2_pos);
				}
				break;
			case 4:
				if (Ball_Position[1] > 9)
				{
					if (Ball_Position[0] > 0)
					{
						Ball_Position[0]--;
					}
					Ball(Ball_Position);
				}
				else
				{
					if(Player_2_pos > 0)
					{
						Player_2_pos--;
					}
					Player_2(Player_2_pos);
				}
				break;
			case 1:
				if (Player_1_pos < 2) {
					Player_1_pos++;
				}
				Player_1(Player_1_pos);
				break;
			case 2:
				if (Player_1_pos > 0)
				{
					Player_1_pos--;
				}
				Player_1(Player_1_pos);
				break;
			default:
				Player_2(Player_2_pos);
				Player_1(Player_1_pos);
			break;
		};
	}
}
/*-------------------------------------------------------------------*/
void	BallMovement()
{
	if (Flag_G_Val == 0)
	{
		Ball_Position[1]++;
		Ball(Ball_Position);
	} 
	else 
	{
		Ball_Position[1]--;
		Ball(Ball_Position);
	}
	// check the win.
	if (Ball_Position[1] == 0 || Ball_Position[1] == 19)
	{
		if (!Flag_G_Val)
		{
			if( Player_2_pos != Ball_Position[0])
			{
				Score[0]++;
			}
		}
		else
		{
			if( Player_1_pos != Ball_Position[0])
			{
				Score[1]++;
			}
		}
		Flag_G_Val = !Flag_G_Val;
		Player_1(Player_1_pos);
		Player_2(Player_2_pos);
	}
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
void	Speed()
{
	if (!Flag_G_Val )
	{
		if(Ball_Position[1] < 9)
		{
			_delay_ms(3000);
		}
		else
		{
			_delay_ms(1000);
		}
	} 
	else
	{
		if(Ball_Position[1] > 9)
		{
			_delay_ms(3000);
		}
		else
		{
			_delay_ms(1000);
		}
	}
}
/*-------------------------------------------------------------------*/
void	Show_Score()
{
	LCD_GoTo_xy(3,0);
	LCD_WriteString("Ply-1:");
	LCD_WriteNumber(Score[0]);
	LCD_GoTo_xy(3,10);
	LCD_WriteString("Ply-2:");
	LCD_WriteNumber(Score[1]);
}
/*-------------------------------------------------------------------*/
void	Show_Net()
{
	LCD_GoTo_xy(0,9);
	LCD_WriteChar(0x05);
	LCD_GoTo_xy(1,9);
	LCD_WriteChar(0x05);
	LCD_GoTo_xy(2,9);
	LCD_WriteChar(0x05);
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
void	Store_Element()
{
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_Player_1,0x02);
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_Player_2,0x03);
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_BALL,0x04);
	_delay_ms(10);
	LCD_Save_SpecialCharacter(customChar_NET,0x05);
}
/*-------------------------------------------------------------------*/
/*  Sub_program Section Ends  */