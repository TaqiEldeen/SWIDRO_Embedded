/*********************************************************/
/***********		Author: MICHAEL		 	**************/
/***********		Contributer: TaqiEldeen **************/
/***********		Layer: HAL			 	**************/
/***********		Component: ADXL345		**************/
/***********		Version: 1.01		 	**************/
/***********		Date: 11-Nov-22	 		**************/
/*********************************************************/


#ifndef ADXL_CFG_H_
#define ADXL_CFG_H_

#define ADXL_SET_PORT	PORTC_ID
#define ADXL_SET_PIN	PIN0_ID
#define ADXL_DEVID		0x53


/************************************************************************/
/*						 DATA FORMAT OPTIONS                            */
/************************************************************************/

/*
*	SELF_TEST
*	Options:
*	1- ENABLED
*	2- DISABLED
*/
#define ADXL_SELF_TEST		DISABLED
		
/*
*	SPI_MODE
*	Options:
*	1- FOURE_WIRE
*	2- THREE_WIRE
*/
#define ADXL_SPI_MODE	FOURE_WIRE

/*
*	INT_INVERT
*	1- ACTIVE_HIGH
*	2- ACTIVE_LOW
*/
#define ADXL_INT_INVERT		ACTIVE_HIGH

/*
	FULL_RES
	Options:
	1- ENABLED
	2- DISABLED
*/
#define ADXL_FULL_RES	ENABLED

/*
	Justify bit
	Options:
	1- LEFT_JUSTIFY
	2- RIGHT_JUSTIFY
*/
#define ADXL_JUSTIFY	RIGHT_JUSTIFY

/*
	Range
	Options: (in +-g)
	1- RANGE_2G
	2- RANGE_4G
	3- RANGE_8G
	4- RANGE_16G
*/
#define ADXL_RANGE	RANGE_16G


/************************************************************************/
/*						 FIFO_CTL OPTIONS							    */
/************************************************************************/
/*
	FIFO MODES
	Options: 
	1- BYPASS
	2- FIFO
	3- STREAM
	4- TRIGGER
*/
#define ADXL_FIFO_MODE		STREAM



#endif /* ADXL_CFG_H_ */
