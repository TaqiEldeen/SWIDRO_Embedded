/*
 * TIM0_pri.h
 *
 *  Created on: 3 Oct 2022
 *      Author: 20109
 */

#ifndef MCAL_TIM0_TIM0_PRI_H_
#define MCAL_TIM0_TIM0_PRI_H_

/**************   TIMER1_private   **************/


/* Available WaveForm Generation modes for timer1 */

#define TIMER1_WGM_NORMAL_MODE						0
#define TIMER1_WGM_PWM_PHASE_CORRECT_8BIT_MODE		1
#define TIMER1_WGM_PWM_PHASE_CORRECT_9BIT_MODE		2
#define TIMER1_WGM_PWM_PHASE_CORRECT_10BIT_MODE		3
#define TIMER1_WGM_CTC_MODE							4
#define TIMER1_WGM_FAST_PWM_8BIT_MODE				5
#define TIMER1_WGM_FAST_PWM_9BIT_MODE				6
#define TIMER1_WGM_FAST_PWM_10BIT_MODE				7
#define TIMER1_WGM_PWM_PHASE_CORRECT_TOP_ICR1		8
#define TIMER1_WGM_PWM_PHASE_CORRECT_TOP_OCR1A		9
/*
#define TIMER1_WGM_PWM_PHASE_CORRECT_TOP_ICR1		10
#define TIMER1_WGM_PWM_PHASE_CORRECT_TOP_OCR1A		11
*/
#define TIMER1_WGM_CTC_TOP_ICR1						12
#define TIMER1_WGM_FAST_PWM_TOP_ICR1				13
#define TIMER1_WGM_FAST_PWM_TOP_OCR1A				14


/*Available Compare output modes for timer1*/
#define TIMER1_OC1x_DISCONNECT		0
#define TIMER1_TOG_OC1x     		1
#define TIMER1_CLR_OC1x     		2
#define TIMER1_SET_OC1x 	 		3
#define TIMER1_COM1xx_MASK			0b00001111


/*Available Clock sources/prescaling for timer1*/
#define TIMER1_PRESCALER_NO_CLK 		0b00000000
#define TIMER1_PRESCALER_NO_PRESCALE    0b00000001
#define TIMER1_PRESCALER_8				0b00000010
#define TIMER1_PRESCALER_64				0b00000011
#define TIMER1_PRESCALER_256			0b00000100
#define TIMER1_PRESCALER_1024			0b00000101
#define TIMER1_EXT_CLK_FALLING_EDGE		0b00000110
#define TIMER1_EXT_CLK_RISING_EDGE      0b00000111
/*Mask for Clock source*/
#define TIMER1_CLK_SELECT_MASK			0b11111000


/*input capture unit setting for timer1*/



/**************   TIMER1 MAX COUNT   **************/
#define TIMER1_MAX_COUNT (u16) 65535

/**************   TIMER STATES   **************/
#define TIMER_ENABLE 	0
#define TIMER_DISABLE	1


/**************   TIMER PWM   **************/
#define PWM_NON_INVERTING	0
#define PWM_INVERTING		1
#define PWM_OFF				2

/**************   TIMER INT state   **************/
#define INT_ENABLE 	0
#define INT_DISABLE 1

/**************   TIMER1 ISRs  **************/
void __vector_10(void)__attribute__((signal));  /*TIMER1 CAPT*/
void __vector_11(void)__attribute__((signal));  /*TIMER1 COMPA*/
void __vector_12(void)__attribute__((signal));  /*TIMER1 COMPB*/
void __vector_13(void)__attribute__((signal));  /*TIMER1 OVF*/


/**************   TIMERn POINTER TO FUNCTION  **************/
void (*G_PTRF_TIM1_OVF)(void) 	= ADDRESS_NULL;
void (*G_PTRF_TIM1_OC1AF)(void) = ADDRESS_NULL;
void (*G_PTRF_TIM1_OC1BF)(void) = ADDRESS_NULL;
void (*G_PTRF_TIM1_ICF1)(void) 	= ADDRESS_NULL;


/**************   TIMER1 GLOBAL Functions  **************/
static void TIMER_vTimer1_setupWGM();


/**************   TIMER1 GLOBAL VARIABLES  **************/
static u16 G_u16Timer1_Cov 			= 0;
static u16 G_u16Timer1_Preload_Val 	= 0;
static u16 G_u16Timer1_OcrVal		= 0;

#endif /* MCAL_TIM0_TIM0_PRI_H_ */
