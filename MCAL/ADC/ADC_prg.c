/*
 * ADC_prg.c
 *
 *  Created on: 31 Aug 2022
 *      Author: 20109
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../DIO/DIO_int.h"
#include "ADC_reg.h"
#include "ADC_pri.h"
#include "ADC_cfg.h"
#include "ADC_int.h"


/*
 * Init the ADC: enable the ADEN bit, select the pre-scale value, select the reference voltage
 * select the ADLAR bit value.
 *
 * if need lower execution time you can use the default values of register
 * */
void ADC_vInit(){
	/*ADCSRA |= ( (1<<ADEN) | (ADC_PRE_SCALE << ADPS0) ); /*Enable ADC & setting PreScaler*/

    /*Set the pre-scaler*/
	ADCSRA &= ADC_PRESCALE_BIT_MASK;
	ADCSRA |= (ADC_PRE_SCALE << ADPS0);

	/*Set the AutoTriggering mode*/
	CLR_BIT(ADCSRA, ADATE); 	/*No auto-triggering*/

	/*Selecting the Vref*/
	ADMUX = ( (ADMUX & (0b00111111)) | (ADC_VREF_SELECT << REFS0) );/*Selecting VREF*/

	/*setup the bits adjust*/
	WRT_BIT(ADMUX, ADLAR, ADC_ADJUST); /*Disable left adjust, although it is by default 0*/

	ADMUX = ( (ADMUX & 0b11110000) | 0b00001110 );	/* Selecting VBG*/

	/*enable the ADC*/
	SET_BIT(ADCSRA, ADEN);

}

/*used only if needed during runtime*/
void ADC_vSetPreScale(u8 A_u8PreScaleVal){
	ADCSRA &= ADC_PRESCALE_BIT_MASK;
	ADCSRA |= (ADC_PRE_SCALE << ADPS0) ;
}

/*Read using interrupt*/
void ADC_vReadDigitalAsync(ptr_func_Iu16_Ov ptr, u8 A_u8ADCId){
	G_ISR_ADC = ptr; /*better to be the first instruction as conversion could be fast*/
	ADMUX = ( (ADMUX & (0b11100000)) | (A_u8ADCId << MUX0));	/*Selecting the channel*/
	ADCSRA |= ((1<<ADIE) | (1<<ADSC));	/*Starting conversion and enable interrupt*/
}

/*Read using polling*/
u16 ADC_u16ReadDigitalSync(){
	SET_BIT(ADCSRA, ADSC);							/*Starting conversion*/
	while(GET_BIT(ADCSRA, ADSC) == 1);	/*Wait till conversion is completed, this will lead to blockage therfore we can use
	time-out concept using timers or increamental variable*/

	return ADCW; /*get the resulted digital value*/
}

void ADC_vTurnOff(){
	CLR_BIT(ADCSRA, ADEN); /*turn off the ADC*/
}

void ADC_vDisable(){
	ADCSRA &= ~ (1<<7);
}
void ADC_vEnable(){
	ADCSRA |= (1<<7);
}

/*ISR for the ADC*/
void __vector_21 (void){
}



