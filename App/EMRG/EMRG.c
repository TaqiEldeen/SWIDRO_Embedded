/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 27 Feb 2023		 	**************/
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GIE/GIE_int.h"
#include "../../HAL/HR_OXIMETER/HR_OXIMETER_int.h"
#include "../../HAL/ADXL/ADXL_int.h"
#include "../../HAL/FLASH/FLASH_int.h"

#include <avr/delay.h>
#define F_CPU 16000000UL

void EMRG_vStart(){

	/* Disable GIE */
	GIE_vDisableGlobalInt();

	/* Power-save the MCU */

	/* CLose all unused sensors: MAX, ADXL */
	MAX30102_vShutDown();
	ADXL_vStandbyMode();

	/* Enable the emergency flashlight */

	/* Flag for emergency: Can be used in Main if this while loop for some reason break */

	while(1){
		/* Transmit while you can (How to let life-guards know your location??) */
		FLASH_vTog();
		_delay_ms(500);
	}
}
