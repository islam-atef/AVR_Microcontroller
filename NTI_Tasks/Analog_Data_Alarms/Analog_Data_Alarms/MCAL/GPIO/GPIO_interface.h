/************************************************************************/
#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H
/************************************************************************/

/*______________________________________________________________________*/
// Return State Of Functions :
typedef enum {
  GPIO_OK = 0x00U,
  GPIO_ERROR = 0x01U,
  GPIO_TIMEOUT = 0x02U,
  GPIO_BUSY = 0x03U

} GPIO_Fun_Status;
/*______________________________________________________________________*/

/*______________________________________________________________________*/
// OUTPUT SIGNAL TYPES :
typedef enum {
  LOW = 0x00U,
  HIGH = 0x01U,
  TOGG = 0x02U
} GPIO_OUTPUT_TYPE;
/*______________________________________________________________________*/

/*______________________________________________________________________*/
// Pin Number :
#define GPIO_PA0 (16)
#define GPIO_PA1 (16 + 1)
#define GPIO_PA2 (16 + 2)
#define GPIO_PA3 (16 + 3)
#define GPIO_PA4 (16 + 4)
#define GPIO_PA5 (16 + 5)
#define GPIO_PA6 (16 + 6)
#define GPIO_PA7 (16 + 7)

#define GPIO_PB0 (32)
#define GPIO_PB1 (32 + 1)
#define GPIO_PB2 (32 + 2)
#define GPIO_PB3 (32 + 3)
#define GPIO_PB4 (32 + 4)
#define GPIO_PB5 (32 + 5)
#define GPIO_PB6 (32 + 6)
#define GPIO_PB7 (32 + 7)

#define GPIO_PC0 (48)
#define GPIO_PC1 (48 + 1)
#define GPIO_PC2 (48 + 2)
#define GPIO_PC3 (48 + 3)
#define GPIO_PC4 (48 + 4)
#define GPIO_PC5 (48 + 5)
#define GPIO_PC6 (48 + 6)
#define GPIO_PC7 (48 + 7)

#define GPIO_PD0 (64U)
#define GPIO_PD1 (64 + 1)
#define GPIO_PD2 (64 + 2)
#define GPIO_PD3 (64 + 3)
#define GPIO_PD4 (64 + 4)
#define GPIO_PD5 (64 + 5)
#define GPIO_PD6 (64 + 6)
#define GPIO_PD7 (64 + 7)
/*______________________________________________________________________*/

/*______________________________________________________________________*/
// Pin Number :
typedef enum { PA, PB, PC, PD } GPIO_PORT_NUM;
/*______________________________________________________________________*/

/*______________________________________________________________________*/
/// @brief GPIO_Init :  THIS FUNCTION DEFINE THE DIRECTION OF THE WHOLE
/// PERIPHERAL
/// @param
/// @return
/*______________________________________________________________________*/
GPIO_Fun_Status GPIO_Init(void);
/*______________________________________________________________________*/

/*______________________________________________________________________*/
/// @brief GPIO_SetValue_Pin : THIS FUNCTION SET THE VALUE OF THE PIN.
/// @param
/// @return
/*______________________________________________________________________*/
GPIO_Fun_Status GPIO_SetValue_Pin(u8 Pin, GPIO_OUTPUT_TYPE Output_Type);
/*______________________________________________________________________*/

/*______________________________________________________________________*/
/// @brief GPIO_ReadValue_Pin : THIS FUNCTION READ THE VALUE OF THE PIN.
/// @param
/// @return
/*______________________________________________________________________*/
u8 GPIO_ReadValue_Pin(u8 Pin);
/*______________________________________________________________________*/

/*______________________________________________________________________*/
/// @brief GPIO_SetValue_Port : THIS FUNCTION SET THE VALUE OF THE WHOLE PORT.
/// @param
/// @return
/*______________________________________________________________________*/
GPIO_Fun_Status GPIO_SetValue_Port(GPIO_PORT_NUM Port, u8 port_val);
/*______________________________________________________________________*/

/*______________________________________________________________________*/
/// @brief GPIO_ReadValue_Port : THIS FUNCTION READ THE VALUE OF THE WHOLE PORT
/// @param
/// @return
/*______________________________________________________________________*/
u8 GPIO_ReadValue_Port(GPIO_PORT_NUM Port);
/*______________________________________________________________________*/
/************************************************************************/
#endif