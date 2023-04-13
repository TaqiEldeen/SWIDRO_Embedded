/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: WDT			**************/
/***********		Version: 1.00		 	**************/
/***********		Date:  20 Sep 2022	 	**************/
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "WDT_reg.h"
#include "WDT_int.h"


/**********************************************************************************************************
 * Description : Interface Function to Enable the WatchDog timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void WDT_vEnable(void){
	SET_BIT(WDTCR, WDE);
}

/**********************************************************************************************************
 * Description : Interface Function to Disable the WatchDog timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void WDT_vDisable(void){
	WDTCR = 0b00011000;
	WDTCR = 0x00;
}

/**********************************************************************************************************
 * Description : Interface Function to setup the WatchDog timer sleep period
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void WDT_vSetSleep(u8 A_u8SleepTime){
	WDTCR &= 0b11111000;
	WDTCR |= (A_u8SleepTime << WDP0);
}
