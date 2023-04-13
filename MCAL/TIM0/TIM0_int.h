/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: TIMER		**************/
/***********		Version: 1.02		 	**************/
/***********		Date: 13 Sep 2022	 	**************/
/***********		Updated: 17 Sep 2022	**************/
/*********************************************************/

#ifndef MCAL_TIM0_TIM0_INT_H_
#define MCAL_TIM0_TIM0_INT_H_


#define	TIMER_DUTY_CYCLE_25		25
#define	TIMER_DUTY_CYCLE_50		50
#define	TIMER_DUTY_CYCLE_75		75
#define	TIMER_DUTY_CYCLE_100	100

//typedef enum {
//	TIM0_PRESCALER_NO_CLK,
//	TIM0_PRESCALER_NO_PRESCALE,
//	TIM0_PRESCALER_8,
//	TIM0_PRESCALER_64,
//	TIM0_PRESCALER_256,
//	TIM0_PRESCALER_1024,
//	TIM0_EXT_CLK_FALLING_EDGE,
//	TIM0_EXT_CLK_RISING_EDGE
//}timer0_prescaler_t;
//
//typedef enum {
//	INT_ENABLE,
//	INT_DISABLE
//}timer0_interrupt_t;
//
//typedef enum {
//	TIMER0_WGM_NORMAL_MODE,
//	TIMER0_WGM_PWM_PHASE_CORRECT_MODE,
//	TIMER0_WGM_CTC_MODE,
//	TIMER0_WGM_FAST_PWM_MODEs
//}timer0_mode_t;
//
//typedef struct {
//	u8 preload;
//	u8 status;   /* ON = 1 / OFF = 0 */
//	timer0_mode_t mode;
//	timer0_prescaler_t prescaler;
//	timer0_interrupt_t ovfInt;
//	timer0_interrupt_t ctcInt;
//}timer0_t;


/**********************************************************************************************************
 * Description : Interface Function to 1-prescaler select, 2-Timer0 mode select, 3-Set OC0 Pin state
 * Outputs     : void
 * Inputs      : void
 * Notes	   : timer is initially off
 ***********************************************************************************************************/
void TIM0_vInit ();

/**********************************************************************************************************
 * Description : Interface Function to Turn on a timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM0_vTurnOn ();

/**********************************************************************************************************
 * Description : Interface Function to set a delay for a specific timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM0_vTurnOff	();

/**********************************************************************************************************
 * Description : Interface Function to set preload to start counting from this value
 * Outputs     : void
 * Inputs      : Preload value
 ***********************************************************************************************************/
void TIM0_vSetPreload (u8 A_u8PreloadVal);

/**********************************************************************************************************
 * Description : Interface Function to set OCR0B register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM0_vSetOcr0bVal (u8 A_u8OcrVal);

/**********************************************************************************************************
 * Description : Interface Function to set OCR0B register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM0_vSetOcr0aVal (u8 A_u8OcrVal);

/**********************************************************************************************************
 * Description : Interface Function to get OCR0A register
 * Outputs     : OCR0
 * Inputs      : void
 ***********************************************************************************************************/
u8 TIM0_vGetOcr0aVal ();

/**********************************************************************************************************
 * Description : Interface Function to get OCR0B register
 * Outputs     : OCR0
 * Inputs      : void
 ***********************************************************************************************************/
u8 TIM0_vGetOcr0bVal ();

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF0A
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM0_vCallBack_OCF0A (ptr_func_t ptr);

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF0B
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM0_vCallBack_OCF0B (ptr_func_t ptr);

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during overflow
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM0_vCallBack_OVF0	(ptr_func_t ptr);

/**********************************************************************************************************
 * Description : Interface Function to set a delay for a specific timer
 * Outputs     : void
 * Inputs      : Timer ID, required delay in milliseconds, the function to be executed
 * NOTES       : still need some work!
 ***********************************************************************************************************/
void  TIM0_vDelayMilli (u16 A_u16DelayMs, u8 A_u8TimerId, ptr_func_t ptr);

/**********************************************************************************************************
 * Description : interface Function to setup the OC0 pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM0_vSetDutyCycleOC0A (u8 A_u8DutyCycle);

/**********************************************************************************************************
 * Description : interface Function to setup the OC0 pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM0_vSetDutyCycleOC0B (u8 A_u8DutyCycle);

#endif /* MCAL_TIM0_TIM0_INT_H_ */
