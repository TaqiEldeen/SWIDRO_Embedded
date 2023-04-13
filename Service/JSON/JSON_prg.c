/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 2 Mar 2023		 	**************/
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../Service/TIME/TIME_int.h"
#include "../COMM/COMM_int.h"
#include "../../HAL/ADXL/ADXL_int.h"
#include "../../HAL/HR_OXIMETER/HR_OXIMETER_int.h"
#include <stdio.h>

/**********************************************************************************************************
 * Description : Interface function to construct a JSON object in a buffer
 * Outputs     : JSON buffer containing the following:
 * 				# Time
 * 				# Device ID
 * 				# Array of acceleration data
 * 				# MAX30102 Data {HR, SPO2}
 * Inputs      : Battery level
 * NOTES	   : The JSON format is as follow:
 * 				 A -> Device ID
 * 				 B -> Accelerometer data in x, y, z as the JSON_strMakeAccObj function formated
 * 				 C -> Time in ms
 * 				 D -> Battery level
 * 				 E -> MAX30102 data in H, S as the JSON_strMakeMaxObj function formated
 ***********************************************************************************************************/
void JSON_strMakeJsonObj(u8* timeJson, u8* batteryJson, u8* maxJson, u8* yourBuffer, u8 buffSize){
	snprintf(
			yourBuffer,
			sizeof(yourBuffer[0]) * buffSize,
			"{\"A\":\"%s\",\"C\":%s,\"D\":%s,\"E\":%s }",
			"1212",
			timeJson,
			batteryJson,
			maxJson
	);
}


void JSON_strMakeAccObj(adxl_t acceleration, u8* accJson, u8 buffSize){
	u8 x_axis[5];
	u8 y_axis[5];
	u8 z_axis[5];

	snprintf(x_axis, sizeof(x_axis) ,"%d.%02u",
			(int) acceleration.x_axis,
			(int) ((acceleration.x_axis - (int) acceleration.x_axis ) * 100) );

	snprintf(y_axis, sizeof(y_axis) ,"%d.%02u",
			(int) acceleration.y_axis,
			(int) ((acceleration.y_axis - (int) acceleration.y_axis ) * 100) );

	snprintf(z_axis, sizeof(z_axis) ,"%d.%02u",
			(int) acceleration.z_axis,
			(int) ((acceleration.z_axis - (int) acceleration.z_axis ) * 100) );

	snprintf(
			accJson,
			sizeof(accJson[0]) * buffSize,
			"{\"x\":%s,\"y\":%s,\"z\":%s}",
			x_axis,
			y_axis,
			z_axis
	);
}


void JSON_strMakeBatteryObj(u8 batteryLevel, u8* batteryJson, u8 buffSize) {
	snprintf(
			batteryJson,
			sizeof(batteryJson[0]) * buffSize,
			"%d",
			batteryLevel
	);
}

void JSON_strMakeTimeObj(u32 time, u8* timeJson, u8 buffSize) {
	snprintf(
			timeJson,
			sizeof(timeJson[0]) * buffSize,
			"%lu",
			time
	);
}

void JSON_strMakeMaxObj(max_t maxObj, u8* maxJson, u8 buffSize) {
	snprintf(
			maxJson,
			sizeof(maxJson[0]) * buffSize,
			"{\"H\":%d,\"S\":%d}",
			maxObj.currentBeat,
			maxObj.currentSpo2
	);
}

