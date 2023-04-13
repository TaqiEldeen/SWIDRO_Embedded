/*********************************************************/
/***********		Author: MICHAEL		 	**************/
/***********		Contributer: TaqiEldeen **************/
/***********		Layer: HAL			 	**************/
/***********		Component: ADXL345		**************/
/***********		Version: 1.01		 	**************/
/***********		Date: 11-Nov-22	 		**************/
/*********************************************************/

#ifndef ADXL_REG_H_
#define ADXL_REG_H_

#define DEVID_REG		  0x00

#define THRESH_INACT_REG  0x25		/*		Inactivity threshold			*/

#define TIME_INACT_REG    0x26		/*		Inactivity time				    */

#define POWER_CTL_REG	  0x2D		/*		Power-saving features control   */
/*Bits*/
#define Wakeup0		0
#define Wakeup1		1
#define Sleep		2
#define Measure		3
#define AUTO_SLEEP	4
#define Link		5

#define INT_ENABLE_REG    0x2E	 /*		Interrupt enable control       */

#define INT_MAP_REG       0x2F	 /*		Interrupt mapping control	   */

/*		Data format control register		   */
#define DATA_FORMAT_REG   0x31	
/*Bits*/
#define RANGE0		0
#define RANGE1		1
#define JUSTIFY		2
#define FULL_RES	3
#define INT_INVERT	5
#define SPI		    6
#define SELF_TEST	7


#define FIFO_CTL_REG	0x38


#define DATAX0_REG   0x32		/*		LSB Output Data for X-axis 		   */
#define DATAX1_REG   0x33		/*		MSB Output Data for X-axis 		   */

#define DATAY0_REG   0x34		/*		LSB Output Data for Y-axis 		   */
#define DATAY1_REG   0x35		/*		MSB Output Data for Y-axis 		   */

#define DATAZ0_REG   0x36		/*		LSB Output Data for Z-axis 		   */
#define DATAZ1_REG   0x37		/*		MSB Output Data for Z-axis 		   */


#endif /* ADXL_REG_H_ */