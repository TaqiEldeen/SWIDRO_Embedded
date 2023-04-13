/*
 * TIM0_cfg.h
 *
 *  Created on: 3 Oct 2022
 *      Author: 20109
 */

#ifndef MCAL_TIM2_TIM2_CFG_H_
#define MCAL_TIM2_TIM2_CFG_H_

/**************   TIMER2_config   **************/

/* WaveForm generation Mode
 *
 * Options:
 * 1- TIMER2_WGM_NORMAL_MODE
 * 2- TIMER2_WGM_PWM_PHASE_CORRECT_MODE
 * 3- TIMER2_WGM_CTC_MODE
 * 4- TIMER2_WGM_FAST_PWM_MODE
 * */
#define TIMER2_WGM_MODE TIMER2_WGM_NORMAL_MODE

/* Compare Match Output Mode (OC0A Pin)  CTC
 *
 * Options:
 * 1- TIMER2_OC2_DISCONNECT
 * 2- TIMER2_TOG_OC2
 * 3- TIMER2_CLR_OC2
 * 4- TIMER2_SET_OC2
 * */
#define TIMER2_OC2A_MODE TIMER2_OC2_DISCONNECT

/* Compare Match Output Mode (OC0B Pin)  CTC
 *
 * Options:
 * 1- TIMER2_OC0_DISCONNECT
 * 2- TIMER2_TOG_OC0
 * 3- TIMER2_CLR_OC0
 * 4- TIMER2_SET_OC0
 * */
#define TIMER2_OC2B_MODE TIMER2_OC2_DISCONNECT

/* Clock select
 *
 * Options:
 * 1- TIMER2_PRESCALER_NO_CLK
 * 2- TIMER2_PRESCALER_NO_PRESCALE
 * 3- TIMER2_PRESCALER_8
 * 4- TIMER2_PRESCALER_32
 * 5- TIMER2_PRESCALER_64
 * 6- TIMER2_PRESCALER_128
 * 7- TIMER2_PRESCALER_256
 * 8- TIMER2_PRESCALER_1024
 * */
#define TIMER2_CLK_SELECT TIMER2_PRESCALER_1024


/* Timers state
 *
 * Options:
 * 1- TIMER_ENABLE
 * 2- TIMER_DISABLE
 * */
#define TIMER2_STATE TIMER_ENABLE

/* interrupt state
 *
 * Options:
 * 1- INT_ENABLE
 * 2- INT_DISABLE
 * */
#define TIMER2_OVF_INT_STATE	INT_ENABLE
#define TIMER2_CTC_INT_STATE	INT_DISABLE

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
#define TIMER2_PWM_OC2A_MODE PWM_OFF
#define TIMER2_PWM_OC2B_MODE PWM_OFF

/* Default PWM value
 *
 * Options:
 * 1- TIMER_DUTY_CYCLE_25
 * 2- TIMER_DUTY_CYCLE_50
 * 3- TIMER_DUTY_CYCLE_75
 * 4- TIMER_DUTY_CYCLE_100
 * */
#define TIMER2_DUTY_CYCLE TIMER_DUTY_CYCLE_25

/* TIMER2 FCPU frequency
 *
 *	Options:
 *	user specify the frequency
 * */
#ifndef TIMER0_InputFreq
	#define TIMER0_InputFreq 16000000UL
#endif

/* OC2A Pin Configuration */
#define OC2A_PORT 	 PORTB_ID
#define OC2A_PIN	 PIN3_ID

/* OC2B Pin Configuration */
#define OC2B_PORT 	 PORTD_ID
#define OC2B_PIN	 PIN3_ID

#endif /* MCAL_TIM2_TIM2_CFG_H_ */
