/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: TIMER		**************/
/***********		Version: 1.02		 	**************/
/***********		Date: 13 Sep 2022	 	**************/
/***********		Updated: 17 Sep 2022	**************/
/*********************************************************/

#include <math.h>
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"
#include "TIM0_reg.h"
#include "TIM0_pri.h"
#include "TIM0_cfg.h"
#include "TIM0_int.h"


static u16 G_u16ISRCounter = 0;


/**********************************************************************************************************
 * Description : Interface Function to 1-prescaler select, 2-Timer0 mode select, 3-Set OC0 Pin state
 * Outputs     : void
 * Inputs      : void
 * Notes	   : timer is initially off
 ***********************************************************************************************************/
void TIM0_vInit (){
#if TIMER0_STATE == TIMER_ENABLE
	/*Step 1: Choose timer mode*/
	#if TIMER0_WGM_MODE == TIMER0_WGM_NORMAL_MODE
		TCCR0A &= TIMER0_WGM_MASK;
		TCCR0A |= TIMER0_WGM_MODE;

		/*Set the interrupt*/
		#if TIMER0_OVF_INT_STATE == INT_ENABLE
			SET_BIT(TIMSK0, TOIE0);
		#endif

		/*Setup the OC0 Pin*/
		TCCR0A &= TIMER0_COM0A0_MASK;
		TCCR0A |= TIMER0_OC0A_MODE;

		TCCR0A &= TIMER0_COM0A1_MASK;
		TCCR0A |= TIMER0_OC0B_MODE;

	#elif TIMER0_WGM_MODE == TIMER0_WGM_CTC_MODE
		TIM0_vSetupCTC();
	#elif TIMER0_WGM_MODE == TIMER0_WGM_FAST_PWM_MODE
		TIM0_vSetupFastPWM();
	#elif TIMER0_WGM_MODE == TIMER0_WGM_PWM_PHASE_CORRECT_MODE
		TIM0_vSetupPhaseCorrectPWM();
	#endif

	/*Disable force output compare by default*/
	CLR_BIT(TCCR0B, FOC0B);
	CLR_BIT(TCCR0B, FOC0A);

#else

#endif

}

/**********************************************************************************************************
 * Description : Interface Function to Turn on a timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM0_vTurnOn (){
	TCCR0B &= TIMER0_CLK_SELECT_MASK;
	TCCR0B |= TIMER0_CLK_SELECT;
}

/**********************************************************************************************************
 * Description : Interface Function to set a delay for a specific timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM0_vTurnOff	(){
	TCCR0B &= TIMER0_CLK_SELECT_MASK;
	TCCR0B |= TIMER0_PRESCALER_NO_CLK;
}

/**********************************************************************************************************
 * Description : Interface Function to set preload to start counting from this value
 * Outputs     : void
 * Inputs      : Preload value
 ***********************************************************************************************************/
void TIM0_vSetPreload (u8 A_u8PreloadVal){
	TCNT0 = A_u8PreloadVal;
	G_u8Timer0_Preload_Val = A_u8PreloadVal;
}

/**********************************************************************************************************
 * Description : Interface Function to set OCR0A register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM0_vSetOcr0aVal (u8 A_u8OcrVal){
	OCR0A = A_u8OcrVal;
}

/**********************************************************************************************************
 * Description : Interface Function to set OCR0B register
 * Outputs     : void
 * Inputs      : OCR value
 ***********************************************************************************************************/
void TIM0_vSetOcr0bVal (u8 A_u8OcrVal){
	OCR0B = A_u8OcrVal;
}

/**********************************************************************************************************
 * Description : Interface Function to get OCR0A register
 * Outputs     : OCR0
 * Inputs      : void
 ***********************************************************************************************************/
u8 TIM0_vGetOcr0aVal (){
	return OCR0A;
}

/**********************************************************************************************************
 * Description : Interface Function to get OCR0B register
 * Outputs     : OCR0
 * Inputs      : void
 ***********************************************************************************************************/
u8 TIM0_vGetOcr0bVal (){
	return OCR0B;
}

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF0A
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM0_vCallBack_OCF0A (ptr_func_t ptr){
	G_PTRF_TIM0_CTC_OCF0A = ptr;
}

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during OCF0B
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM0_vCallBack_OCF0B (ptr_func_t ptr){
	G_PTRF_TIM0_CTC_OCF0B = ptr;
}

/**********************************************************************************************************
 * Description : Interface Function to set the call back function that will be executed during overflow
 * Outputs     : void
 * Inputs      : pointer to function
 ***********************************************************************************************************/
void TIM0_vCallBack_OVF0	(ptr_func_t ptr){
	G_PTRF_TIM0_OVF = ptr;
}

/**********************************************************************************************************
 * Description : interface Function to setup the OC0A pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM0_vSetDutyCycleOC0A (u8 A_u8DutyCycle){
	#if TIMER0_PWM_OC0A_MODE == PWM_NON_INVERTING
		TIM0_vSetOcr0aVal( ( (TIMER0_MAX_COUNT + 1) * A_u8DutyCycle ) / 100);
	#elif TIMER0_PWM_OC0A_MODE == PWM_INVERTING
		TIM0_vSetOcr0aVal( ( -( (A_u8DutyCycle/100) - 1) ) * (TIMER0_MAX_COUNT + 1);
	#endif
}

/**********************************************************************************************************
 * Description : interface Function to setup the OC0B pin duty cycle if in PWM mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIM0_vSetDutyCycleOC0B (u8 A_u8DutyCycle){
	#if TIMER0_PWM_OC0B_MODE == PWM_NON_INVERTING
		TIM0_vSetOcr0bVal( ( (TIMER0_MAX_COUNT + 1) * A_u8DutyCycle ) / 100);
	#elif TIMER0_PWM_MODE == PWM_INVERTING
		TIMER0_PWM_OC0B_MODE( ( -( (A_u8DutyCycle/100) - 1) ) * (TIMER0_MAX_COUNT + 1);
	#endif
}

/**
 * Description : Interface Function to set a delay for a specific timer
 * Outputs     : void
 * Inputs      : Timer ID, required delay in milliseconds, the function to be executed
 * NOTES       : still need some work!
 **/
void  TIM0_vDelayMilli (u16 A_u16DelayMs, u8 A_u8TimerId, ptr_func_t ptr){
    u16 L_u16PrescaleVal = 1;
    f32 L_f32TimeOverFlow;
    f32 L_f32TickTime;
    u16 L_u16OverFlowCounts = 0;
    u8 L_u8PreloadVal = 0;
	/* Resetting the ISR Counter */
	G_u16ISRCounter = 0;

    switch(TIMER0_CLK_SELECT){
        case TIMER0_PRESCALER_8:    L_u16PrescaleVal = 8;     break;
        case TIMER0_PRESCALER_64:   L_u16PrescaleVal = 64;    break;
        case TIMER0_PRESCALER_256:  L_u16PrescaleVal = 256;	  break;
        case TIMER0_PRESCALER_1024: L_u16PrescaleVal = 1024;  break;
    }

    /* Tick time Calculation */
    L_f32TickTime = (f32)L_u16PrescaleVal / TIMER0_InputFreq;

    /* Time required for complete 1 over flow */
    L_f32TimeOverFlow = ((u16)TIMER0_MAX_COUNT + 1.0) * (L_f32TickTime * (1000UL));

    /* Over flow needed by this delay */
    L_u16OverFlowCounts = (u16) ceil(( ((f32)A_u16DelayMs /L_f32TimeOverFlow) ));

    /* Calculating OverFlow counts & preload value */
    L_u8PreloadVal = ( (f32)L_u16OverFlowCounts - ( (f32)A_u16DelayMs /L_f32TimeOverFlow) ) * (TIMER0_MAX_COUNT + 1.0);
    G_u16Timer0_Cov = L_u16OverFlowCounts;


#if  TIMER0_WGM_MODE == TIMER0_WGM_CTC_MODE
        TIM0_vSetOcr0Val((TIMER0_MAX_COUNT - L_u8PreloadVal));
        G_PTRF_TIM0_CTC = ptr;
#elif TIMER0_WGM_MODE == TIMER0_WGM_NORMAL_MODE
        G_PTRF_TIM0_OVF = ptr;
		TIM0_vSetPreload(L_u8PreloadVal);
#endif
}



/**************   TIMER0 mode functions   **************/

static void TIM0_vSetupCTC(){
	/*Setup the mode*/
	TCCR0A &= TIMER0_WGM_MASK;
	TCCR0A |= TIMER0_WGM_MODE;

	/*Setup the OC0 Pin*/
	TCCR0A &= TIMER0_COM0A0_MASK;
	TCCR0A |= TIMER0_OC0A_MODE;

	/*Setup the OC0 Pin*/
	TCCR0A &= TIMER0_COM0A1_MASK;
	TCCR0A |= TIMER0_OC0B_MODE;

	/* OC0A mode */
	#if TIMER0_OC0A_MODE == TIMER0_OC0_DISCONNECT

	#else
		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0A_PORT, OC0A_PIN, DIR_OUTPUT);
	#endif

	#if TIMER0_CTC_INT_STATE == INT_ENABLE
		SET_BIT(TIMSK0, OCIE0A);
	#endif

	/* OC0B mode */
	#if TIMER0_OC0B_MODE == TIMER0_OC0_DISCONNECT

	#else
		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0B_PORT, OC0B_PIN, DIR_OUTPUT);
	#endif

	#if TIMER0_CTC_INT_STATE == INT_ENABLE
		SET_BIT(TIMSK0, OCIE0B);
	#endif
}

static void TIM0_vSetupFastPWM	(){
	TCCR0A &= TIMER0_WGM_MASK;
	TCCR0A |= TIMER0_WGM_MODE;

	/*Step 2: Setup the OC0B Pin*/
	#if TIMER0_PWM_MODE == PWM_INVERTING
		SET_BIT(TCCR0A, COM0B0);
		SET_BIT(TCCR0A, COM0B1);

		/*Calculate the dutyCycle*/
		TIM0_vSetDutyCycleOC0B(TIMER0_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0B_PORT, OC0B_PIN, DIR_OUTPUT);
	#elif TIMER0_PWM_MODE == PWM_NON_INVERTING
		CLR_BIT(TCCR0A, COM0B0);
		SET_BIT(TCCR0A, COM0B1);

		/*Calculate the dutyCycle*/
		TIM0_vSetDutyCycleOC0B(TIMER0_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0B_PORT, OC0B_PIN, DIR_OUTPUT);
	#else
	#endif

	/*Step 2: Setup the OC0A Pin*/
	#if TIMER0_PWM_MODE == PWM_INVERTING
		SET_BIT(TCCR0A, COM0A0);
		SET_BIT(TCCR0A, COM0A1);

		/*Calculate the dutyCycle*/
		TIM0_vSetDutyCycleOC0A(TIMER0_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0A_PORT, OC0A_PIN, DIR_OUTPUT);
	#elif TIMER0_PWM_MODE == PWM_NON_INVERTING
		CLR_BIT(TCCR0A, COM0A0);
		SET_BIT(TCCR0A, COM0A1);

		/*Calculate the dutyCycle*/
		TIM0_vSetDutyCycleOC0A(TIMER0_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0A_PORT, OC0A_PIN, DIR_OUTPUT);
	#else
	#endif
}

static void TIM0_vSetupPhaseCorrectPWM	(){
	TCCR0A &= TIMER0_WGM_MASK;
	TCCR0A |= TIMER0_WGM_MODE;

	/*Step 2: Setup the OC0B Pin*/
	#if TIMER0_PWM_MODE == PWM_INVERTING
		SET_BIT(TCCR0A, COM0B0);
		SET_BIT(TCCR0A, COM0B1);

		/*Calculate the dutyCycle*/
		TIM0_vSetDutyCycleOC0B(TIMER0_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0B_PORT, OC0B_PIN, DIR_OUTPUT);

	#elif TIMER0_PWM_MODE == PWM_NON_INVERTING
		CLR_BIT(TCCR0A, COM0B0);
		SET_BIT(TCCR0A, COM0B1);

		/*Calculate the dutyCycle*/
		TIM0_vSetDutyCycleOC0B(TIMER0_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0B_PORT, OC0B_PIN, DIR_OUTPUT);
	#else

	#endif

	/*Step 2: Setup the OC0A Pin*/
	#if TIMER0_PWM_MODE == PWM_INVERTING
		SET_BIT(TCCR0A, COM0A0);
		SET_BIT(TCCR0A, COM0A1);

		/*Calculate the dutyCycle*/
		TIM0_vSetDutyCycleOC0A(TIMER0_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0A_PORT, OC0A_PIN, DIR_OUTPUT);

	#elif TIMER0_PWM_MODE == PWM_NON_INVERTING
		CLR_BIT(TCCR0A, COM0A0);
		SET_BIT(TCCR0A, COM0A1);

		/*Calculate the dutyCycle*/
		TIM0_vSetDutyCycleOC0A(TIMER0_DUTY_CYCLE);

		/*Must set the OC0 pin output if in CTC, fast PWM or phase correct PWM modes*/
		DIO_vSetPinDir(OC0A_PORT, OC0A_PIN, DIR_OUTPUT);
	#else

	#endif
}


/*TIMER0 COMPA*/
void __vector_14(void){
	if(G_PTRF_TIM0_CTC_OCF0A != ADDRESS_NULL){
		G_PTRF_TIM0_CTC_OCF0A();
	} else {
		/*Handle callback error*/
	}
}

/*TIMER0 COMPB*/
void __vector_15(void){
	if(G_PTRF_TIM0_CTC_OCF0B != ADDRESS_NULL){
		G_PTRF_TIM0_CTC_OCF0B();
	} else {
		/*Handle callback error*/
	}
}

/* TIMER0 OVF */
void __vector_16(void)
{
	if(G_PTRF_TIM0_OVF != ADDRESS_NULL)
	{
//		G_u16ISRCounter++;
//		if(G_u16ISRCounter == G_u16Timer0_Cov)
//		{
//			G_u16ISRCounter = 0;
//			G_PTRF_TIM0_OVF();
//			TCNT0 = G_u8Timer0_Preload_Val;
//		}
		G_PTRF_TIM0_OVF();
	} else {
		/* Handle callback error */
	}
}
