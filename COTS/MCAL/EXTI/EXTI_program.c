#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "EXTI_config.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
// callBack Functions.
static void (*EXTI_0_CALLBACK)(void) = NULL;
static void (*EXTI_1_CALLBACK)(void) = NULL;
static void (*EXTI_2_CALLBACK)(void) = NULL;

void GIE_voidEnable(void) { sei(); }

void GIE_voidDisable(void) { cli(); }

// initialize the INT with sensing mood in preprocessing stage
void EXTI_voidInit(void) {
  (*MCUCR) &= (0b11110000);
#if EXTI_0 == ON
  (*MCUCR) |= (INT_0_TRIGGER);
#endif
#if EXTI_1 == ON
  (*MCUCR) |= (INT_1_TRIGGER << ISC10);
#endif
#if EXTI_2 == ON
  (*MCUCSR) &= (0b10111111);
  (*MCUCSR) |= (INT_2_TRIGGER << ISC2);
#endif
}

// enable EXTI.
void EXTI_voidEnable(INTERRUPT_NUM int_num) {
  switch (int_num) {
  case EXTI_INT_0:
    SET_BIT(*GICR, INT0);
    break;
  case EXTI_INT_1:
    SET_BIT(*GICR, INT1);
    break;
  case EXTI_INT_2:
    SET_BIT(*GICR, INT2);
    break;
  default:
    break;
  };
}

// disable EXTI
void EXTI_voidDisable(INTERRUPT_NUM int_num) {
  switch (int_num) {
  case EXTI_INT_0:
    CLR_BIT(*GICR, INT0);
    break;
  case EXTI_INT_1:
    CLR_BIT(*GICR, INT1);
    break;
  case EXTI_INT_2:
    CLR_BIT(*GICR, INT2);
    break;
  default:
    break;
  };
}

// change the INT with sensing mood in runtime
void EXTI_voidSetSignalch(INTERRUPT_NUM int_num,
                          INTERRUPT_SIGNAL_LCH SenseCpy) {
  switch (int_num) {
  case EXTI_INT_0:
    (*MCUCR) &= (0b11111100);
    (*MCUCR) |= (SenseCpy);
    break;
  case EXTI_INT_1:
    (*MCUCR) &= (0b11110011);
    (*MCUCR) |= (SenseCpy << ISC10);
    break;
  case EXTI_INT_2:
    (*MCUCSR) &= (0b10111111);
    (*MCUCSR) |= (SenseCpy << ISC2);
    break;
  default:
    break;
  };
}

// callback function
void EXTI_VID_SET_CALL_BACK(INTERRUPT_NUM int_num, void (*PTR)(void)) {
  switch (int_num) {
  case EXTI_INT_0:
    EXTI_0_CALLBACK = PTR;
    break;
  case EXTI_INT_1:
    EXTI_1_CALLBACK = PTR;
    break;
  case EXTI_INT_2:
    EXTI_2_CALLBACK = PTR;
    break;
  default:
    break;
  };
}

// ISR_FUNCTION:-
/*------------------------------------------------------------------------*/
void __vector_1(void)
    __attribute__((signal, used, externally_visible)); // to avoid optimization
void __vector_1(void) {
  EXTI_0_CALLBACK();
  SET_BIT(*GIFR, INTF0);
}
/*------------------------------------------------------------------------*/
void __vector_2(void)
    __attribute__((signal, used, externally_visible)); // to avoid optmization
void __vector_2(void) {
  EXTI_1_CALLBACK();
  SET_BIT(*GIFR, INTF1);
}
/*------------------------------------------------------------------------*/
void __vector_3(void)
    __attribute__((signal, used, externally_visible)); // to avoid optmization
void __vector_3(void) {
  EXTI_2_CALLBACK();
  SET_BIT(*GIFR, INTF2);
}