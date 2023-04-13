/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 27 Feb 2023		 	**************/
/*********************************************************/

#ifndef SERVICE_COMM_COMM_INT_H_
#define SERVICE_COMM_COMM_INT_H_

#define DEVICE_ID	0x0000

void COMM_vInit();

void COMM_vTransmit(u8 *buff);

void COMM_strReceive();

u8 COMM_boolIsChannelFree();


#endif /* SERVICE_COMM_COMM_INT_H_ */
