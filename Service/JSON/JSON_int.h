/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 2 Mar 2023		 	**************/
/*********************************************************/

#ifndef SERVICE_JSON_JSON_INT_H_
#define SERVICE_JSON_JSON_INT_H_


/**********************************************************************************************************
 * Description : Interface function to construct a JSON object in a buffer
 * Outputs     : JSON buffer containing the following:
 * 				# Time
 * 				# Device ID
 * 				# Array of acceleration data
 * 				# MAX30102 Data {HR, SPO2}
 * Inputs      : Battery level
 ***********************************************************************************************************/
void JSON_strMakeJsonObj(u8* timeJson, u8* batteryJson, u8* maxJson, u8* yourBuffer, u8 buffSize);


void JSON_strMakeAccObj(adxl_t acceleration, u8* accJson, u8 buffSize);

void JSON_strMakeBatteryObj(u8 batteryLevel, u8* batteryJson, u8 buffSize);

void JSON_strMakeTimeObj(u32 time, u8* timeJson, u8 buffSize);

void JSON_strMakeMaxObj(max_t maxObj, u8* maxJson, u8 buffSize);


#endif /* SERVICE_JSON_JSON_INT_H_ */
