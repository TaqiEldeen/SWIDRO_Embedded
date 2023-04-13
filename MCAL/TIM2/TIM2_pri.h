/*
 * TIM0_pri.h
 *
 *  Created on: 3 Oct 2022
 *      Author: 20109
 */

#ifndef MCAL_TIM2_TIM2_PRI_H_
#define MCAL_TIM2_TIM2_PRI_H_

/**************   TIMER2_private   **************/


/* Available WaveForm Generation modes for timer0 */
#define TIMER2_WGM_NORMAL_MODE 		   		0
#define TIMER2_WGM_PWM_PHASE_CORRECT_MODE 	1
#define TIMER2_WGM_CTC_MODE			   		2
#define TIMER2_WGM_FAST_PWM_MODE          	3
/*Mask for the  waveForm Generation modes*/
#define TIMER2_WGM_MASK        				0b11111100


/*Available Compare output modes for timer0*/
#define TIMER2_OC2_DISCONNECT	0b00000000
#define TIMER2_TOG_OC2     		0b00010000
#define TIMER2_CLR_OC2     		0b00100000
#define TIMER2_SET_OC2 	 		0b00110000
/*Mask for the Compare output mode*/
#define TIMER2_COM2A0_MASK		0b11001111
#define TIMER2_COM2A1_MASK		0b00111111


/*Available Clock sources/prescaling for timer0*/
#define TIMER2_PRESCALER_NO_CLK 		0b00000000
#define TIMER2_PRESCALER_NO_PRESCALE    0b00000001
#define TIMER2_PRESCALER_8				0b00000010
#define TIMER2_PRESCALER_32				0b00000011
#define TIMER2_PRESCALER_64				0b00000100
#define TIMER2_PRESCALER_128			0b00000101
#define TIMER2_PRESCALER_256			0b00000110
#define TIMER2_PRESCALER_1024     		0b00000111
/*Mask for Clock source*/
#define TIMER2_CLK_SELECT_MASK			0b11111000


/**************   TIMER0 MAX COUNT   **************/
#define TIMER2_MAX_COUNT (u16) 255


/**************   TIMER STATES   **************/
#define TIMER_ENABLE 	0
#define TIMER_DISABLE	1


/**************   TIMER PWM   **************/
#define PWM_NON_INVERTING	2
#define PWM_INVERTING		3
#define PWM_OFF				0


/**************   TIMER INT state   **************/
#define INT_ENABLE 	0
#define INT_DISABLE 1

/**************   TIMER ISRs  **************/
void __vector_7(void)__attribute__((signal));  /*TIMER2 COMPA*/
void __vector_8(void)__attribute__((signal));  /*TIMER2 COMPB*/
void __vector_9(void)__attribute__((signal));  /*TIMER2 OVF*/


/**************   TIMER2 POINTER TO FUNCTION  **************/
void (*G_PTRF_TIM2_OVF)(void) = ADDRESS_NULL;
void (*G_PTRF_TIM2_CTC_OCF2A)(void) = ADDRESS_NULL;
void (*G_PTRF_TIM2_CTC_OCF2B)(void) = ADDRESS_NULL;

/**************   TIMER2 GLOBAL Functions  **************/
static void TIMER_vTimer2_SetupCTC		();
static void TIMER_vTimer2_SetupFastPWM	();
static void TIMER_vTimer2_SetupPhaseCorrectPWM	();


/**************   TIMER2 GLOBAL VARIABLES  **************/
static u16 G_u16Timer2_Cov = 0;
static u8 G_u8Timer2_Preload_Val = 0;
static u8 G_u8Timer2_OcrVal = 0;
#endif /* MCAL_TIM2_TIM2_PRI_H_ */
