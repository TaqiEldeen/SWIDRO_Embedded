/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: Service			**************/
/***********		Component: TIME			**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 16 feb 2023	 	**************/
/*********************************************************/

#ifndef SERVICE_TIME_TIME_INT_H_
#define SERVICE_TIME_TIME_INT_H_

/**********************************************************************************************************
 * Description : Interface Function to setup TIM0 for counting time since calling TIME_vStartTime
 * Outputs     : void
 * Inputs      : void
 * Notes	   : # This module is using TIM0 so please don't use TIM0 when using this module
 * 				 # Enable GIE to use this module
 * 				 # Adjust prescaler to 64	(16MHZ)
 * 				 # Enable OVF INT
 ***********************************************************************************************************/
void TIME_vInit();

/**********************************************************************************************************
 * Description : Interface function to Start counting time
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIME_vStartTime();

/**********************************************************************************************************
 * Description : Interface Function to stop counting time
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void TIME_vStopTime();

/**********************************************************************************************************
 * Description : Interface Function to stop counting time
 * Outputs     : the current time in u32
 * Inputs      : void
 ***********************************************************************************************************/
u32 TIME_u32GetTime();

#endif /* SERVICE_TIME_TIME_INT_H_ */
