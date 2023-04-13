/*
 * TIM0_prg.c
 *
 *  Created on: 3 Oct 2022
 *      Author: 20109
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"
#include "TIM2_pri.h"
#include "TIM2_cfg.h"
#include "TIM2_reg.h"
#include "TIM2_int.h"


/**********************************************************************************************************
 * Description : Interface Function to 1-prescaler select, 2-Timer2 mode select, 3-Set OC0 Pin state
 * Outputs     : void
 * Inputs      : void
 * Notes	   : timer is initially off
 ***********************************************************************************************************/
void TIM2_vInit (){
	#if TIMER2_STATE == TIMER_ENABLE
		/*Step 1: Choose timer mode*/
		#if TIMER2_WGM_MODE == TIMER2_WGM_NORMAL_MODE
			TCCR2A &= TIMER2_WGM_MASK;
			TCCR2A |= TIMER2_WGM_MODE;

			/*Set the interrupt*/
			#if TIMER2_OVF_INT_STATE == INT_ENABLE
				SET_BIT(TIMSK2, TOIE2);
			#endif

		#elif TIMER2_WGM_MODE == TIMER2_WGM_CTC_MODE
			TIMER_vTimer2_SetupCTC();
		#elif TIMER2_WGM_MODE == TIMER2_WGM_FAST_PWM_MODE
			TIMER_vTimer2_SetupFastPWM();
		#elif TIMER2_WGM_MODE == TIMER2_WGM_PWM_PHASE_CORRECT_MODE
			TIMER_vTimer2_SetupPhaseCorrectPWM();
		#endif

		/*Disable force output compare by default*/
		CLR_BIT(TCCR2B, FOC2B);
		CLR_BIT(TCCR2B, FOC2A);
	#else

	#endif
}

/**********************************************************************************************************
 * Description : Interface Function to Turn on a timer
 * Outputs     : void
 * Inputs      : Timer ID
 ***********************************************************************************************************/
void TIM2_vTurnOn (){
	TCCR2B &= TIMER2_CLK_SELECT_MASK;
	TCCR2B |= TIMER2_CLK_SELECT;
}

/**********************************************************************************************************
 * Description : Interface Function to set a delay for a specific timer
 * Outputs     : void
 * Inputs      : Timer ID
 ***********************************************************************************************************/
void TIM2_vTurnOff (){
	TCCR2B &= TIMER2_CLK_SELECT_MASK;
	TCCR2B |= TIMER2_PRESCALER_NO_CLK;
}

/**********************************************************************************************************
 * Description : Interface Function to set preload to start counting from this value
 * Outputs     : void
 * Inputs      : Preload value
 ***********************************************************************************************************/
void TIM2_vSetPreload (u8 A_u8PreloadVal){
	TCNT2 = A_u8PreloadVal;
}

/**********************************************************************************************************
 * Description : Interface Function to set OCR2 register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM2_vSetOcr2aVal (u8 A_u8OcrVal){
	OCR2A = A_u8OcrVal;
}

/**********************************************************************************************************
 * Description : Interface Function to set OCR2 register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM2_vSetOcr2bVal (u8 A_u8OcrVal){
	OCR2B = A_u8OcrVal;
}

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF2
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM2_vCallBack_OCF2A (ptr_func_t ptr){
	G_PTRF_TIM2_CTC_OCF2A = ptr;
}

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF2
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM2_vCallBack_OCF2B (ptr_func_t ptr){
	G_PTRF_TIM2_CTC_OCF2B = ptr;
}

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OVF
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM2_vCallBack_OVF2 (ptr_func_t ptr){
	G_PTRF_TIM2_OVF = ptr;
}

/**********************************************************************************************************
 * Description : interface Function to setup the OC2 pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM2_vSetDutyCycleOC2b (u8 A_u8DutyCycle){
	#if TIMER2_PWM_OC2B_MODE == PWM_NON_INVERTING
		TIM2_vSetOcr2bVal( ( (TIMER2_MAX_COUNT + 1) * A_u8DutyCycle ) /100);
	#elif TIMER2_PWM_OC2B_MODE == PWM_INVERTING
		TIM2_vSetOcr2bVal( ( -( (A_u8DutyCycle/100) - 1) ) * (TIMER2_MAX_COUNT + 1);
	#endif
}


/**********************************************************************************************************
 * Description : interface Function to setup the OC2 pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM2_vSetDutyCycleOC2a (u8 A_u8DutyCycle){
	#if TIMER2_PWM_OC2A_MODE == PWM_NON_INVERTING
		TIM2_vSetOcr2aVal( ( (TIMER2_MAX_COUNT + 1) * A_u8DutyCycle ) /100);
	#elif TIMER2_PWM_OC2A_MODE == PWM_INVERTING
		TIM2_vSetOcr2aVal( ( -( (A_u8DutyCycle/100) - 1) ) * (TIMER2_MAX_COUNT + 1);
	#endif
}


/**************   TIMER2 mode functions   **************/

static void TIMER_vTimer2_SetupCTC(){
	/*Setup the mode*/
	TCCR2A &= TIMER2_WGM_MASK;
	TCCR2A |= TIMER2_WGM_MODE;

	/*Setup the OC2 Pin*/
	TCCR2A &= TIMER2_COM2A0_MASK;
	TCCR2A |= TIMER2_OC2A_MODE;

	/*Setup the OC2 Pin*/
	TCCR2A &= TIMER2_COM2A1_MASK;
	TCCR2A |= TIMER2_OC2B_MODE;

	/* OC2A mode */
	#if TIMER2_OC2A_MODE == TIMER2_OC2_DISCONNECT

	#else
		/*Must set the OC2 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2A_PORT, OC2A_PIN, DIR_OUTPUT);
	#endif

	#if TIMER0_CTC_INT_STATE == INT_ENABLE
		SET_BIT(TIMSK2, OCIE2A);
	#endif

	/* OC2B mode */
	#if TIMER2_OC0B_MODE == TIMER2_OC2_DISCONNECT

	#else
		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2B_PORT, OC2B_PIN, DIR_OUTPUT);
	#endif

	#if TIMER0_CTC_INT_STATE == INT_ENABLE
		SET_BIT(TIMSK2, OCIE2B);
	#endif

	return;
}

static void TIMER_vTimer2_SetupFastPWM	(){
	TCCR2A &= TIMER2_WGM_MASK;
	TCCR2A |= TIMER2_WGM_MODE;

	/*Step 2: Setup the OC0B Pin*/
	#if TIMER2_PWM_MODE == PWM_INVERTING
		SET_BIT(TCCR2A, COM2B0);
		SET_BIT(TCCR2A, COM2B1);

		/*Calculate the dutyCycle*/
		TIM2_vSetDutyCycleOC2B(TIMER2_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2B_PORT, OC2B_PIN, DIR_OUTPUT);
	#elif TIMER0_PWM_MODE == PWM_NON_INVERTING
		CLR_BIT(TCCR2A, COM2B0);
		SET_BIT(TCCR2A, COM2B1);

		/*Calculate the dutyCycle*/
		TIM2_vSetDutyCycleOC2B(TIMER2_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2B_PORT, OC2B_PIN, DIR_OUTPUT);
	#else
	#endif

	/*Step 2: Setup the OC0A Pin*/
	#if TIMER2_PWM_MODE == PWM_INVERTING
		SET_BIT(TCCR2A, COM2A0);
		SET_BIT(TCCR2A, COM2A1);

		/*Calculate the dutyCycle*/
		TIM0_vSetDutyCycleOC2A(TIMER2_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2A_PORT, OC2A_PIN, DIR_OUTPUT);
	#elif TIMER0_PWM_MODE == PWM_NON_INVERTING
		CLR_BIT(TCCR2A, COM2A0);
		SET_BIT(TCCR2A, COM2A1);

		/*Calculate the dutyCycle*/
		TIM2_vSetDutyCycleOC2A(TIMER2_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2A_PORT, OC2A_PIN, DIR_OUTPUT);
	#else
	#endif
}

static void TIMER_vTimer2_SetupPhaseCorrectPWM	(){
	TCCR2A &= TIMER2_WGM_MASK;
	TCCR2A |= TIMER2_WGM_MODE;

	/*Step 2: Setup the OC2B Pin*/
	#if TIMER2_PWM_MODE == PWM_INVERTING
		SET_BIT(TCCR2A, COM2B0);
		SET_BIT(TCCR2A, COM2B1);

		/*Calculate the dutyCycle*/
		TIM2_vSetDutyCycleOC2B(TIMER2_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2B_PORT, OC2B_PIN, DIR_OUTPUT);

	#elif TIMER2_PWM_MODE == PWM_NON_INVERTING
		CLR_BIT(TCCR2A, COM2B0);
		SET_BIT(TCCR2A, COM2B1);

		/*Calculate the dutyCycle*/
		TIM2_vSetDutyCycleOC2B(TIMER2_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2B_PORT, OC2B_PIN, DIR_OUTPUT);
	#else

	#endif

	/*Step 2: Setup the OC2A Pin*/
	#if TIMER2_PWM_MODE == PWM_INVERTING
		SET_BIT(TCCR2A, COM2A0);
		SET_BIT(TCCR2A, COM2A1);

		/*Calculate the dutyCycle*/
		TIM2_vSetDutyCycleOC2A(TIMER0_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2A_PORT, OC2A_PIN, DIR_OUTPUT);

	#elif TIMER2_PWM_MODE == PWM_NON_INVERTING
		CLR_BIT(TCCR2A, COM2A0);
		SET_BIT(TCCR2A, COM2A1);

		/*Calculate the dutyCycle*/
		TIM2_vSetDutyCycleOC2A(TIMER2_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC2A_PORT, OC2A_PIN, DIR_OUTPUT);
	#else

	#endif
}



/**************   TIMER2 ISR   **************/

/*TIMER2 COMPA*/
void __vector_7(void){
	if(G_PTRF_TIM2_CTC_OCF2A != ADDRESS_NULL){
		G_PTRF_TIM2_CTC_OCF2A();
	} else {
		/*Handle callback error*/
	}
}

/*TIMER2 COMPB*/
void __vector_8(void){
	if(G_PTRF_TIM2_CTC_OCF2B != ADDRESS_NULL){
		G_PTRF_TIM2_CTC_OCF2B();
	} else {
		/*Handle callback error*/
	}
}

/*TIMER2 OVF*/
void __vector_9(void){
	if(G_PTRF_TIM2_OVF != ADDRESS_NULL){
		G_PTRF_TIM2_OVF();
	} else {
		/*Handle callback error*/
	}
}
