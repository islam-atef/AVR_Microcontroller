/*
 * Calculator.c
 *
 * Created: 10/21/2023 1:59:54 PM
 * Author : Islam atef mohamed
 */ 

/*  include Section starts  */
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include <util/delay.h>
#include "MCAL/GPIO/GPIO_interface.h"

#include "HAL/LCD/LCD_interface.h"
#include "HAL/KEYPAD/KEYPAD_interface.h"
/*  include Section Ends  */



/* Type definition section starts. */
typedef struct
{	
	u8  Operation_ID;
	u64 *Operand_1_ptr;
	u64 *Operand_2_ptr;
}OPERATION;
			   
typedef struct
{
   u8   Operand_ID;
   u8	Operand_arr[10];
   u64  Operand_num;
   u64 *Operand_num_ptr;
   u8   Operand_counter;
}OPERAND;
		
typedef struct
{	
	u8  proc_ID;
	u8  proc_order;
	u8	process;
}PROCESS;
/* Type definition section ends. */


/*  MACRO Section starts  */
/*  MACRO Section Ends  */


/*  Global Variables Section starts  */
OPERATION	operation_Table[10];
PROCESS		processes[10];
OPERAND		Operands[10];
u64			Result_buffer[10];
u8			Start_Flag ;
u8			Global_counter;
/*  Global Variables Section Ends  */


/*  Sub_program Declaration Section starts  */
void	Load_Number(OPERAND *operand,u8 num);
void	Load_Process(PROCESS *process,u8 proc);
void	Arange_Operation(OPERATION *operation_Table );
void	Get_Number(OPERAND *operand);
void	intiiate_Buttons(void);
void	OperatorFun(u8 element);
void	SortProcesses(void);
void	Get_Result(void);
/*  Sub_program Declaration Section Ends  */


/*  Main Function Section starts  */
int main(void)
{
	// initiate the GPIO pins' Direction.
    GPIO_Init();
	// initiate the LCD.
    LCD_Init();
	_delay_ms(100);
	// Local variables.
	u8 keypad_val;
    while (1) 
    {
		keypad_val = KEYPAD_Read();
		if (keypad_val != '\0')
		{
			if (keypad_val != '=')
			{
				LCD_WriteChar(keypad_val);
			}
			OperatorFun(keypad_val);
			_delay_ms(50);
		}
    }
}
/*  Main Function Section Ends  */


/*  Sub_program Section starts  */
void	OperatorFun(u8 element) // [2/4].
{
	if ( ((element == '*') || (element == '/') || (element == '+') || (element == '-')) && (Start_Flag == 1) )  // error
	{
		// 1- load the process.
		Load_Process(&processes[Global_counter],element);
		
		// 2- Load the Process ID into the Processes Array.
		processes[Global_counter].proc_ID = Global_counter;
		
		// 3- Load the Process ID into the Table.
		operation_Table[Global_counter].Operation_ID = Global_counter;
		
		// 4- Convert the array of characters into an integer.
		Get_Number(&Operands[Global_counter]);
		
		// 5- Load the First Operand Address into the Table.
		operation_Table[Global_counter].Operand_1_ptr = Operands[Global_counter].Operand_num_ptr;
		
		// 6- increase the first counter.
		Global_counter++;
		
		// 7- Load the Second Operand Address into the Table.
		operation_Table[Global_counter - 1].Operand_2_ptr = Operands[Global_counter].Operand_num_ptr;
		
		// 8- Sort the Operation in the processes array
		SortProcesses();
	}
	else if ((element == '=')  && (Start_Flag == 1))
	{
		// 1- Convert the last operand array of characters into an integer.
		Get_Number(&Operands[Global_counter]);
		// 2- calculate the result.
		Get_Result();
		LCD_GoTo_xy(3,0);
		LCD_WriteChar('=');
		LCD_WriteNumber(Result_buffer[Global_counter-1]);
	}
	else if ((element == 'c') && (Start_Flag == 1))
	{

	}
	else
	{
		if ((element >= '0') && (element <='9'))
		{
			Load_Number(&Operands[Global_counter],element);
			Operands[Global_counter].Operand_ID = Global_counter;
			Start_Flag = 1;
		}
	}
}
/*-------------------------------------------------------------------*/
void	SortProcesses(void)
{
	PROCESS local_buffer = {0};
	u8 local_counter = Global_counter;
	for (u8 i = 0; i < (local_counter - 1); i++) {
	  for (u8 j = 0; j < (local_counter - i - 1) ; j++) {
	    if (processes[j].proc_order > processes[j + 1].proc_order ) {
	      local_buffer = processes[j + 1];
	      processes[j + 1] = processes[j];
	      processes[j] = local_buffer;
	    }
	  }
	}	
}
/*-------------------------------------------------------------------*/
void	Get_Result(void)
{
	u8 local_ID_buffer_1;
	// the result will be stored in the second operand always.
	for (u8 i = 0; i < Global_counter ; i++)
	{
		local_ID_buffer_1 = processes[i].proc_ID;
		switch (processes[i].process)
		{
			case '+':
				Result_buffer[i] = ((*(Operands[local_ID_buffer_1].Operand_num_ptr))+(*(Operands[local_ID_buffer_1+1].Operand_num_ptr))); 
				LCD_GoTo_xy(1,0);
				LCD_WriteNumber(*(Operands[local_ID_buffer_1].Operand_num_ptr));
				LCD_GoTo_xy(1,10);
				LCD_WriteNumber(*(Operands[local_ID_buffer_1+1].Operand_num_ptr));
				Operands[local_ID_buffer_1].Operand_num_ptr = &Result_buffer[i];
				Operands[local_ID_buffer_1+1].Operand_num_ptr = &Result_buffer[i];
				////////////////////////////////////////////////////////////////////////////
				Operands[local_ID_buffer_1].Operand_num_ptr = Operands[local_ID_buffer_1+1].Operand_num_ptr;
				////////////////////////////////////////////////////////////////////////////
				LCD_GoTo_xy(2,0);
				LCD_WriteNumber(Result_buffer[i]);
				LCD_WriteChar(' ');
				GPIO_SetValue_Pin(GPIO_PA7,HIGH);
				_delay_ms(10000);
				break;
			case '-':
				Result_buffer[i] = ((*(Operands[local_ID_buffer_1].Operand_num_ptr))-(*(Operands[local_ID_buffer_1+1].Operand_num_ptr)));
				LCD_GoTo_xy(1,0);
				LCD_WriteNumber(*(Operands[local_ID_buffer_1].Operand_num_ptr));
				LCD_GoTo_xy(1,10);
				LCD_WriteNumber(*(Operands[local_ID_buffer_1+1].Operand_num_ptr));
				Operands[local_ID_buffer_1].Operand_num_ptr = &Result_buffer[i];
				Operands[local_ID_buffer_1+1].Operand_num_ptr = &Result_buffer[i];
				////////////////////////////////////////////////////////////////////////////
				Operands[local_ID_buffer_1].Operand_num_ptr = Operands[local_ID_buffer_1+1].Operand_num_ptr;
				////////////////////////////////////////////////////////////////////////////
				LCD_GoTo_xy(2,0);
				LCD_WriteNumber(Result_buffer[i]);
				LCD_WriteChar(' ');
				GPIO_SetValue_Pin(GPIO_PA6,HIGH);
				_delay_ms(10000);
				break;
			case '*':
				Result_buffer[i] = ((*(Operands[local_ID_buffer_1].Operand_num_ptr))*(*(Operands[local_ID_buffer_1+1].Operand_num_ptr)));
				LCD_GoTo_xy(1,0);
				LCD_WriteNumber(*(Operands[local_ID_buffer_1].Operand_num_ptr));
				LCD_GoTo_xy(1,10);
				LCD_WriteNumber(*(Operands[local_ID_buffer_1+1].Operand_num_ptr));
				Operands[local_ID_buffer_1].Operand_num_ptr = &Result_buffer[i];
				Operands[local_ID_buffer_1+1].Operand_num_ptr = &Result_buffer[i];
				////////////////////////////////////////////////////////////////////////////
				Operands[local_ID_buffer_1].Operand_num_ptr = Operands[local_ID_buffer_1+1].Operand_num_ptr;
				////////////////////////////////////////////////////////////////////////////
				LCD_GoTo_xy(2,0);
				LCD_WriteNumber(Result_buffer[i]);
				LCD_WriteChar(' ');
				GPIO_SetValue_Pin(GPIO_PA5,HIGH);
				_delay_ms(10000);
				break;
			case '/':
				Result_buffer[i] = ((*(Operands[local_ID_buffer_1].Operand_num_ptr)) / (*(Operands[local_ID_buffer_1+1].Operand_num_ptr)));
				LCD_GoTo_xy(1,0);
				LCD_WriteNumber(*(Operands[local_ID_buffer_1].Operand_num_ptr));
				LCD_GoTo_xy(1,10);
				LCD_WriteNumber(*(Operands[local_ID_buffer_1+1].Operand_num_ptr));
				Operands[local_ID_buffer_1].Operand_num_ptr = &Result_buffer[i];
				Operands[local_ID_buffer_1+1].Operand_num_ptr = &Result_buffer[i];
				////////////////////////////////////////////////////////////////////////////
				Operands[local_ID_buffer_1].Operand_num_ptr = Operands[local_ID_buffer_1+1].Operand_num_ptr;
				////////////////////////////////////////////////////////////////////////////
				LCD_GoTo_xy(2,0);
				LCD_WriteNumber(Result_buffer[i]);
				LCD_WriteChar(' ');
				GPIO_SetValue_Pin(GPIO_PA4,HIGH);
				_delay_ms(10000);
				break;
			default:
				break;
		}
	}
}
/*-------------------------------------------------------------------*/
/*-------------------------------------------------------------------*/
void	Load_Process(PROCESS *process, u8 proc) // [work]
{
	switch (proc)
	{
		case '+':
			process -> proc_order = 2;
			process -> process = '+';
			
			break;
		case '-':
			process -> proc_order = 2;
			process -> process = '-';
			break;
		case '*':
			process -> proc_order = 1;
			process -> process = '*';
			break;
		case '/':
			process -> proc_order = 1;
			process -> process = '/';
			break;
		default:
			break;
	}
}
/*-------------------------------------------------------------------*/
void	Load_Number(OPERAND *operand ,u8 num) // [work].
{
	operand -> Operand_arr[(operand ->Operand_counter)] = num; 
	operand ->Operand_counter++;
}
/*-------------------------------------------------------------------*/
void	Get_Number(OPERAND *operand) // [work].
{
	(operand ->Operand_num) = 0;
	for (u8 i = 0; i < (operand->Operand_counter) ; i++)
	{
		(operand ->Operand_num) *= 10;
		(operand ->Operand_num) += (operand->Operand_arr[i] - 48); 
	}
	operand ->Operand_num_ptr = &operand ->Operand_num;
}
/*-------------------------------------------------------------------*/
void	intiiate_Buttons(void)
{
	// initiate the Column pins as input Pull_Up.
	GPIO_SetValue_Pin(GPIO_PD7,HIGH);
	GPIO_SetValue_Pin(GPIO_PD6,HIGH);
	GPIO_SetValue_Pin(GPIO_PD5,HIGH);
	GPIO_SetValue_Pin(GPIO_PD3,HIGH);
}
/*-------------------------------------------------------------------*/
/*  Sub_program Section Ends  */
