/*
 * TIM0_int.h
 *
 *  Created on: 3 Oct 2022
 *      Author: 20109
 */

#ifndef MCAL_TIM0_TIM0_INT_H_
#define MCAL_TIM0_TIM0_INT_H_

/*ICR edge*/
typedef enum {
	ICR_FALLING_EDGE,
	ICR_RISING_EDGE
};

/*Some available dutys*/
#define	TIMER_DUTY_CYCLE_25		25
#define	TIMER_DUTY_CYCLE_50		50
#define	TIMER_DUTY_CYCLE_75		75
#define	TIMER_DUTY_CYCLE_100	100

/**********************************************************************************************************
 * Description : Interface Function to 1-prescaler select, 2-Timer1 mode select, 3-Set OC0 Pin state
 * Outputs     : void
 * Inputs      : void
 * Notes	   : timer is initially off
 ***********************************************************************************************************/
void TIM1_vInit();

/**********************************************************************************************************
 * Description : Interface Function to Turn on a timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM1_vTurnOn ();

/**********************************************************************************************************
 * Description : Interface Function to set a delay for a specific timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM1_vTurnOff	();

/**********************************************************************************************************
 * Description : Interface Function to set preload to start counting from this value
 * Outputs     : void
 * Inputs      : Preload value
 ***********************************************************************************************************/
void TIM1_vSetPreload (u16 A_u16PreloadVal);

/**********************************************************************************************************
 * Description : Interface Function to set OCR1A register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM1_vSetOcr1aVal (u16 A_u16OcrVal);

/**********************************************************************************************************
 * Description : Interface Function to set OCR1B register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM1_vSetOcr1bVal (u16 A_u16OcrVal);

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during overflow
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM1_vCallBack_OVF	(ptr_func_t ptr);

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF1A
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM1_vCallBack_OCF1A (ptr_func_t ptr);

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF1B
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM1_vCallBack_OCF1B (ptr_func_t ptr);

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during ICR event
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM1_vCallBack_ICF1 (ptr_func_t ptr);

/**********************************************************************************************************
 * Description : interface Function to setup the OC1a pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM1_vSetDutyCycleOC1A (u8 A_u8DutyCycle);

/**********************************************************************************************************
 * Description : interface Function to setup the OC1b pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM1_vSetDutyCycleOC1B (u8 A_u8DutyCycle);

/**********************************************************************************************************
 * Description : Interface Function to set ICR1 register
 * Outputs     : void
 * Inputs      : ICR value
 ***********************************************************************************************************/
void TIM1_vSetIcr1Val (u16 A_u16IcrVal);

/**********************************************************************************************************
 * Description : Interface Function to set TIMER1 in ICU mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM1_vInitICU ();

/**********************************************************************************************************
 * Description : Interface Function to turn off interrupt of iCR
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM1_vDisableICU ();

/**********************************************************************************************************
 * Description : Interface Function to set the Triggering edge for the ICU
 * Outputs     : void
 * Inputs      : Trigger mode
 ***********************************************************************************************************/
void TIM1_vSetTriggering (u8 A_u8Trigger);

/**********************************************************************************************************
 * Description : Interface Function to set ICR1 register
 * Outputs     : ICR
 * Inputs      : void
 ***********************************************************************************************************/
u16 TIM1_vGetIcr1Val ();


/*For disconnecting the timer from OCR1B pin*/
void TIM1_vOcr1bOff();

/*For reconnecting the timer from OCR1B pin*/
void TIM1_vOcr1bOn();

/**
 * Description : Interface Function to set a delay for a specific timer
 * Outputs     : void
 * Inputs      :required delay in milliseconds, the function to be executed
 * NOTES       : still need some work!
 **/
void  TIM1_vDelayMilli (u16 A_u16DelayMs, ptr_func_t ptr);

#endif /* MCAL_TIM0_TIM0_INT_H_ */
