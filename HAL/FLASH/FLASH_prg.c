/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 12 Mar 2023		 	**************/
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"



void FLASH_vInit(){
	DIO_vSetPinDir(PORTB_ID, PIN0_ID, DIR_OUTPUT);
}

void FLASH_vTog(){
	DIO_vTogPin(PORTB_ID, PIN0_ID);
}
