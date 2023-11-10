#ifndef EXTI_INTEFACE_H
#define EXTI_INTEFACE_H

typedef enum { EXTI_INT_0, EXTI_INT_1, EXTI_INT_2 } INTERRUPT_NUM;

typedef enum {
  _EXTI_LOW = 0,
  _EXTI_IOC = 1,
  _EXTI_FALLING = 2,
  _EXTI_RISING = 3
} INTERRUPT_SIGNAL_LCH;

// Enable The global interrupt.
void GIE_voidEnable(void);

// Disable The global interrupt.
void GIE_voidDisable(void);

// initialize the INT with sensing mood in preprocessing stage
void EXTI_voidInit(void);

// enable EXTI
void EXTI_voidEnable(INTERRUPT_NUM int_num);

// disable EXTI
void EXTI_voidDisable(INTERRUPT_NUM int_num);

// change the INT with sensing mood in runtime
void EXTI_voidSetSignalch(INTERRUPT_NUM int_num, INTERRUPT_SIGNAL_LCH SenseCpy);

// callback function
void EXTI_VID_SET_CALL_BACK(INTERRUPT_NUM int_num, void (*PTR)(void));

#endif