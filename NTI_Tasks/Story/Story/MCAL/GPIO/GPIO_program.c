#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"

/*______________________________________________________________________*/
/// @brief
/// @param
/// @return
/*______________________________________________________________________*/
GPIO_Fun_Status GPIO_Init(void) {
  DDRA->Port = (u8)PORTA_DIRECTION;
  DDRB->Port = (u8)PORTB_DIRECTION;
  DDRC->Port = (u8)PORTC_DIRECTION;
  DDRD->Port = (u8)PORTD_DIRECTION;
  return GPIO_OK;
}
/*______________________________________________________________________*/

/*______________________________________________________________________*/
/// @brief
/// @param
/// @return
/*______________________________________________________________________*/
GPIO_Fun_Status GPIO_SetValue_Pin(u8 Pin, GPIO_OUTPUT_TYPE Output_Type) {
  u8 pin_num = Pin & (0b00001111);
  u8 port_num = ((Pin & (0b11110000)) >> 4);
  switch (port_num) {
  case 1:
    CLR_BIT(PORTA->Port, pin_num);
    if (Output_Type == TOGG) {
      TOG_BIT(PORTA->Port,pin_num);
    } else {
      (PORTA->Port) |= (Output_Type << (pin_num));
    }
    break;
  case 2:
    CLR_BIT(PORTB->Port, pin_num);
    if (Output_Type == TOGG) {
	 (PORTB->Port) ^= (1 << pin_num);
    } else {
      (PORTB->Port) |= (Output_Type << (pin_num));
    }
    break;
  case 3:
    CLR_BIT(PORTC->Port, pin_num);
    if (Output_Type == TOGG) {
     TOG_BIT(PORTC->Port,pin_num);
    } else {
      (PORTC->Port) |= (Output_Type << (pin_num));
    }
    break;
  case 4:
    CLR_BIT(PORTD->Port, pin_num);
    if (Output_Type == TOGG) {
      TOG_BIT(PORTD->Port,pin_num);
    } else {
      (PORTD->Port) |= (Output_Type << (pin_num));
    }
    break;
  default:
    break;
  }
  return GPIO_OK;
}
/*______________________________________________________________________*/

/*______________________________________________________________________*/
/// @brief
/// @param
/// @return
/*______________________________________________________________________*/
u8 GPIO_ReadValue_Pin(u8 Pin) {
  volatile u8 returned_Val = 0;
  u8 pin_num = Pin & (0b00001111);
  u8 port_num = ((Pin & (0b11110000)) >> 4);
  // u8 *Location;
  switch (port_num) {
  case 1:
    // Location = (u8 *)(&(PINA->BITS) + pin_num);
    // returned_Val = *Location;
    returned_Val = GET_BIT(PINA->Port, pin_num);
  case 2:
    // Location = (u8 *)(&(PINB->BITS) + pin_num);
    // returned_Val = *Location;
    returned_Val = GET_BIT(PINB->Port, pin_num);
    break;
  case 3:
    // Location = (u8 *)(&(PINC->BITS) + pin_num);
    // returned_Val = *Location;
    returned_Val = GET_BIT(PINC->Port, pin_num);
    break;
  case 4:
    // Location = (u8 *)(&(PIND->BITS) + pin_num);
    // returned_Val = *Location;
    returned_Val = GET_BIT(PIND->Port, pin_num);
    break;
  default:
    break;
  }
  return returned_Val;
}
/*______________________________________________________________________*/

/*______________________________________________________________________*/
/// @brief
/// @param
/// @return
/*______________________________________________________________________*/
GPIO_Fun_Status GPIO_SetValue_Port(GPIO_PORT_NUM Port, u8 port_val) {
  switch (Port) {
  case PA:
    PORTA->Port = port_val;
  case PB:
    PORTB->Port = port_val;
  case PC:
    PORTC->Port = port_val;
  case PD:
    PORTD->Port = port_val;
    break;
  default:
    break;
  }
  return GPIO_OK;
}
/*______________________________________________________________________*/

/*______________________________________________________________________*/
/// @brief
/// @param
/// @return
/*______________________________________________________________________*/
u8 GPIO_ReadValue_Port(GPIO_PORT_NUM Port) {
  volatile u8 returned_Val = 0;
  switch (Port) {
  case PA:
    returned_Val = PINA->Port;
  case PB:
    returned_Val = PINB->Port;
  case PC:
    returned_Val = PINC->Port;
  case PD:
    returned_Val = PIND->Port;
    break;
  default:
    break;
  }
  return returned_Val;
}
/*______________________________________________________________________*/