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
	DIO_vSetPinDir(PORTC_ID, PIN0_ID, DIR_OUTPUT);
}

void FLASH_vTog(){
	DIO_vTogPin(PORTC_ID, PIN0_ID);
}

void FLASH_vTurnOff(){
	DIO_vSetPinVal(PORTC_ID, PIN0_ID, VAL_LOW);
}
