/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 8 Mar 2023		 	**************/
/*********************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_int.h"


/**********************************************************************************************************
 * Description : Interface Function to initialize the battery
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : # Adjust the ADC to AVCC
 * 				 # Connect a decoupling capacitor at AREF
 * 				 # Connect VCC to AVCC
 * 				 # ADMUX to VBG
 ***********************************************************************************************************/
void BAT_vInit(){
	ADC_vInit();
}


u8 BAT_u8GetPercentage(){
	u8 L_u8Battery = 0;
	f32 L_f32Vcc	= 0;
	u16 L_u16AdcVal = 0;

	L_u16AdcVal = ADC_u16ReadDigitalSync();		/* Read the digital value */

	L_f32Vcc = (256.0 *  1.1 )  / L_u16AdcVal;		/* Convert it to analog value, VBG is 1.1v */

	L_u8Battery = L_f32Vcc * 100.0 - 470.0; 			/* Battery voltage is from 4.7 to 5.7 */

	return L_u8Battery;
}
