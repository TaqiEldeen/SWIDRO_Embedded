/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: TIMER		**************/
/***********		Version: 1.02		 	**************/
/***********		Date: 13 Sep 2022	 	**************/
/***********		Updated: 17 Sep 2022	**************/
/*********************************************************/

#ifndef MCAL_TIM0_TIM0_CFG_H_
#define MCAL_TIM0_TIM0_CFG_H_

/**************   TIMER0_config   **************/

/* WaveForm generation Mode
 *
 * Options:
 * 1- TIMER0_WGM_NORMAL_MODE
 * 2- TIMER0_WGM_PWM_PHASE_CORRECT_MODE
 * 3- TIMER0_WGM_CTC_MODE
 * 4- TIMER0_WGM_FAST_PWM_MODE
 * */
#define TIMER0_WGM_MODE TIMER0_WGM_NORMAL_MODE

/* Compare Match Output Mode (OC0A Pin)  CTC
 *
 * Options:
 * 1- TIMER0_OC0_DISCONNECT
 * 2- TIMER0_TOG_OC0
 * 3- TIMER0_CLR_OC0
 * 4- TIMER0_SET_OC0
 * */
#define TIMER0_OC0A_MODE TIMER0_OC0_DISCONNECT

/* Compare Match Output Mode (OC0B Pin)  CTC
 *
 * Options:
 * 1- TIMER0_OC0_DISCONNECT
 * 2- TIMER0_TOG_OC0
 * 3- TIMER0_CLR_OC0
 * 4- TIMER0_SET_OC0
 * */
#define TIMER0_OC0B_MODE TIMER0_OC0_DISCONNECT

/* Clock select
 *
 * Options:
 * 1- TIMER0_PRESCALER_NO_CLK
 * 2- TIMER0_PRESCALER_NO_PRESCALE
 * 3- TIMER0_PRESCALER_8
 * 4- TIMER0_PRESCALER_64
 * 5- TIMER0_PRESCALER_256
 * 6- TIMER0_PRESCALER_1024
 * 7- TIMER0_EXT_CLK_FALLING_EDGE
 * 8- TIMER0_EXT_CLK_RISING_EDGE
 * */
#define TIMER0_CLK_SELECT TIMER0_PRESCALER_64


/* Timers state
 *
 * Options:
 * 1- TIMER_ENABLE
 * 2- TIMER_DISABLE
 * */
#define TIMER0_STATE TIMER_ENABLE

/* interrupt state
 *
 * Options:
 * 1- INT_ENABLE
 * 2- INT_DISABLE
 * */
#define TIMER0_OVF_INT_STATE	INT_ENABLE
#define TIMER0_CTC_INT_STATE	INT_DISABLE

/* TIMER0 PWM mode
 *
 * Options:
 * 1- PWM_NON_INVERTING
 * 2- PWM_INVERTING
 * 3- PWM_OFF
 * Note:
 * PWM_NON_INVERTING means the Duty cycle is directly proportional to OCR
 * PWM_INVERTING means the Duty cycle is inversely proportional to OCR
 * */
#define TIMER0_PWM_OC0A_MODE PWM_OFF
#define TIMER0_PWM_OC0B_MODE PWM_OFF

/* Default PWM value
 *
 * Options:
 * 1- TIMER_DUTY_CYCLE_25
 * 2- TIMER_DUTY_CYCLE_50
 * 3- TIMER_DUTY_CYCLE_75
 * 4- TIMER_DUTY_CYCLE_100
 * */
#define TIMER0_DUTY_CYCLE TIMER_DUTY_CYCLE_25

/* TIMER0 FCPU frequency
 *
 *	Options:
 *	user specify the frequency
 * */
#ifndef TIMER0_InputFreq
	#define TIMER0_InputFreq 16000000UL
#endif

/* OC0A Pin Configuration */
#define OC0A_PORT 	 PORTD_ID
#define OC0A_PIN	 PIN6_ID

/* OC0B Pin Configuration */
#define OC0B_PORT 	 PORTD_ID
#define OC0B_PIN	 PIN5_ID

#endif /* MCAL_TIM0_TIM0_CFG_H_ */
