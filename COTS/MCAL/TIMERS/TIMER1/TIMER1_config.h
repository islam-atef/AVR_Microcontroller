/*
 * TIMER1_config.h
 *
 * Created: 10/27/2023 10:34:47 AM
 *  Author: Islam Atef
 */ 


#ifndef TIMER1_CONFIG_H_
#define TIMER1_CONFIG_H_

/*		Operation Modes Section start		*/
#define		TIMER1_NORMAL_MODE			0
#define		TIMER1_PWM_PHASE_CORRECT	1
#define		TIMER1_CTC_MODE				2
#define		TIMER1_PWM_FAST_MODE_ICR1	3

#define		TIMER1_MODE		TIMER1_PWM_FAST_MODE_ICR1
/*		Operation Modes Section End			*/



/*		Clock selection Section start		*/
#define		TIMER1_DISABLE				0
#define		TIMER1_CLK_1				1
#define		TIMER1_CLK_8				2
#define		TIMER1_CLK_64				3
#define		TIMER1_CLK_256				4
#define		TIMER1_CLK_1024				5
#define		TIMER1_EX_CL_FALLING_EDGE	6
#define		TIMER1_EX_CL_RISING_EDGE	7

#define		TIMER1_CLOCK_SOURCE		TIMER1_CLK_8
/*		Clock selection Section End			*/



#if  (TIMER0_MODE == TIMER0_NORMAL_MODE) ||  (TIMER0_MODE == TIMER0_CTC_MODE)
/*		Compare Match Output Non_PWM Mode Section start		*/
#define		TIMER1_OC0_DISCONNECT				0
#define		TIMER1_OC0_TOGG_ON_CM				1
#define		TIMER1_OC0_CLR_ON_CM				2
#define		TIMER1_OC0_SET_ON_CM				3

#define		TIMER1_COM_NON_PWM		TIMER1_OC0_DISCONNECT
/*		Compare Match Output Non_PWM Section End			*/
#endif



#if TIMER0_MODE == TIMER0_PWM_FAST_MODE
/*		Compare Match Output FAST_PWM Mode Section start		*/
#define		TIMER1_OC0_DISCONNECT				0
#define		TIMER1_OC0_NIN_INVERTING 			2
#define		TIMER1_OC0_INVERTING				3

#define		TIMER1_COM_FAST_PWM		TIMER1_OC0_NIN_INVERTING
/*		Compare Match Output FAST_PWM Section End			*/
#endif




#if TIMER0_MODE == TIMER0_PWM_PHASE_CORRECT
/*		Compare Match Output PHASE_CORRECT_PWM Mode Section start		*/
#define		TIMER1_OC0_DISCONNECT				0
#define		TIMER1_OC0_CLR_ON_DOWNCOUNT			2
#define		TIMER1_OC0_SET_ON_DOWNCOUNT			3

#define		TIMER1_COM_PHASE_CORRECT_PWM		TIMER1_OC0_DISCONNECT
/*		Compare Match Output PHASE_CORRECT_PWM Section End			*/
#endif



#endif /* TIMER0_CONFIG_H_ */