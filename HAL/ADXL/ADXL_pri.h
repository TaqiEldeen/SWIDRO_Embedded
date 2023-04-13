/*********************************************************/
/***********		Author: MICHAEL		 	**************/
/***********		Contributer: TaqiEldeen **************/
/***********		Layer: HAL			 	**************/
/***********		Component: ADXL345		**************/
/***********		Version: 1.01		 	**************/
/***********		Date: 11-Nov-22	 		**************/
/*********************************************************/


#ifndef ADXL_PRI_H_
#define ADXL_PRI_H_

/************** 	Enable/disable	  **************/
#define ENABLED		1
#define DISABLED	0

/************** 	Range select	  **************/
#define	RANGE_2G		0
#define	RANGE_4G		1
#define	RANGE_8G		2
#define	RANGE_16G		3

/************** 	Justify mode select	  **************/
#define LEFT_JUSTIFY		1	/*MSB*/
#define RIGHT_JUSTIFY		0	/*LSB*/

/************** 	Interrupt invert state	  **************/
#define ACTIVE_HIGH		0
#define ACTIVE_LOW		1

/************** 	SPI mode	  **************/
#define FOURE_WIRE		0
#define THREE_WIRE		1

/************** 	FIFO MODES	  **************/
#define BYPASS		0
#define FIFO		1
#define STREAM		2
#define TRIGGER		3


#define SENSORS_GRAVITY_EARTH		9.80665F
#define ADXL345_MG2G_MULTIPLIER		0.004

#define WRITE_DATA_SINGLE			0x00
#define WRITE_DATA_MULTI			0b01000000
#define READ_DATA_SINGLE			0b10000000
#define READ_DATA_MULTI				0b11000000

static u8 readData(u8 A_u8Reg, u8 *A_u8Buffer);
static u8 writeData(u8 A_u8Reg, u8 A_u8Data);
static void assert(u8 A_u8ErrCode);

#endif /* ADXL_PRI_H_ */
