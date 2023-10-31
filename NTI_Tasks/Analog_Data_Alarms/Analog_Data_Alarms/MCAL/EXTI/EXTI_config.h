#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H

#define ON 1
#define OFF 0

// Used Interrupts.
#define		EXTI_0				ON
#define		EXTI_1				OFF
#define		EXTI_2				OFF

// Trigger Signal Types For Interrupt.
#define		EXTI_FALLING		2
#define		EXTI_RISING			3
#define		EXTI_IOC			1
#define		EXTI_LOW			0

// Trigger Signal For Each Interrupt.
#define		INT_0_TRIGGER		EXTI_FALLING
#define		INT_1_TRIGGER		EXTI_LOW
// For INT2, The trigger signal could be either (FALLING_EDGE) or (RISING_EDGE).
#define		INT_2_TRIGGER		EXTI_LOW
#endif