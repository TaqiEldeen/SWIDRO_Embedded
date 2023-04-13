/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: Service			**************/
/***********		Component: TIME			**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 16 feb 2023	 	**************/
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/TIM0/TIM0_int.h"

static u32 G_u32Time = 0;
static void increaseTime();

/**********************************************************************************************************
 * Description : Interface Function to setup TIM0 for counting time since calling TIME_vStartTime
 * Outputs     : void
 * Inputs      : void
 * Notes	   : # This module is using TIM0 so please don't use TIM0 when using this module
 * 				 # Enable GIE to use this module
 * 				 # Adjust prescaler to 64	(16MHZ)
 * 				 # Enable OVF INT
 ***********************************************************************************************************/
void TIME_vInit(){
	/* Initialise the Timer */
	TIM0_vInit();

	/* Assign callback function */
	TIM0_vCallBack_OVF0( increaseTime );

	/* Set preload to get 1ms */
	TIM0_vSetPreload(6);

	/* Start the timer */
	TIM0_vTurnOn();
}

/**********************************************************************************************************
 * Description : Interface function to Start counting time
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIME_vStartTime(){
	TIM0_vTurnOn();
}

/**********************************************************************************************************
 * Description : Interface Function to stop counting time
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIME_vStopTime(){
	TIM0_vTurnOff();
}

/**********************************************************************************************************
 * Description : Interface Function to stop counting time
 * Outputs     : the current time in u32
 * Inputs      : void
 ***********************************************************************************************************/
u32 TIME_u32GetTime(){
	return G_u32Time;
}

static void increaseTime(){
	G_u32Time ++;
	/* reset preload */
	TIM0_vSetPreload(6);
}
