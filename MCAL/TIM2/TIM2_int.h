/*
 * TIM0_int.h
 *
 *  Created on: 3 Oct 2022
 *      Author: 20109
 */

#ifndef MCAL_TIM2_TIM2_INT_H_
#define MCAL_TIM2_TIM2_INT_H_

#define	TIMER_DUTY_CYCLE_25		25
#define	TIMER_DUTY_CYCLE_50		50
#define	TIMER_DUTY_CYCLE_75		75
#define	TIMER_DUTY_CYCLE_100	100

/**********************************************************************************************************
 * Description : Interface Function to 1-prescaler select, 2-Timer2 mode select, 3-Set OC0 Pin state
 * Outputs     : void
 * Inputs      : void
 * Notes	   : timer is initially off
 ***********************************************************************************************************/
void TIM2_vInit ();

/**********************************************************************************************************
 * Description : Interface Function to Turn on a timer
 * Outputs     : void
 * Inputs      : Timer ID
 ***********************************************************************************************************/
void TIM2_vTurnOn			();

/**********************************************************************************************************
 * Description : Interface Function to set a delay for a specific timer
 * Outputs     : void
 * Inputs      : Timer ID
 ***********************************************************************************************************/
void TIM2_vTurnOff			();

/**********************************************************************************************************
 * Description : Interface Function to set preload to start counting from this value
 * Outputs     : void
 * Inputs      : Preload value
 ***********************************************************************************************************/
void TIM2_vSetPreload		(u8 A_u8PreloadVal);

/**********************************************************************************************************
 * Description : Interface Function to set OCR2 register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM2_vSetOcr2aVal (u8 A_u8OcrVal);

/**********************************************************************************************************
 * Description : Interface Function to set OCR2 register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM2_vSetOcr2bVal (u8 A_u8OcrVal);

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF2
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM2_vCallBack_OCF2A (ptr_func_t ptr);

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF2
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM2_vCallBack_OCF2B (ptr_func_t ptr);

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OVF
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM2_vCallBack_OVF2 (ptr_func_t ptr);

/**********************************************************************************************************
 * Description : interface Function to setup the OC2 pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM2_vSetDutyCycleOC2b (u8 A_u8DutyCycle);

/**********************************************************************************************************
 * Description : interface Function to setup the OC2 pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM2_vSetDutyCycleOC2a (u8 A_u8DutyCycle);

#endif /* MCAL_TIM2_TIM2_INT_H_ */
