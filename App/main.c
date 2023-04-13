/*
 * SWIDRO.c
 *
 * Created: 02/11/2022 09:23:34 PM
 * Author : TaqiEldeen
 */ 

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/ADXL/ADXL_int.h"
#include "../HAL/HR_OXIMETER/HR_OXIMETER_int.h"
#include "../MCAL/UART/UART_int.h"
#include "../HAL/HC/HC_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../Service/TIME/TIME_int.h"
#include "../Service/JSON/JSON_int.h"
#include "../MCAL/TIM1/TIM1_int.h"
#include "../Service/COMM/COMM_int.h"
#include "../HAL/BAT/BAT_int.h"
#include "../HAL/FLASH/FLASH_int.h"
#include "EMRG/EMRG.h"
#include "states.h"

#include <avr/delay.h>
#include <stdio.h>

static adxl_t acceleration;
static max_t pulseOximeter;

/* Based on max chars needed*/
volatile u8 batteryJson[10];
volatile u8 timeJson[25];
volatile u8 maxJson[30];
volatile u8 myJson[200];

u8 G_u8currentState = MAX_STATE;

static volatile u16 G_u16CountToMin = 0;

static void sendAsInteger(s32 A_s32Bpm);

static void sendPayload();

static void doMaxAlgo();

static void sendAccelertation();

static void isMaxDone();

int main(void)
{
	/* Initialize HC module */
	HC_vInit();

	/* Intialize Timer2 for timing reading heartbeats and SPO2 */
	TIME_vInit();
	TIM1_vInit();

	/* Initialize ADXL module */
	ADXL_vInit();

	/* Initialize MAX30102 module */
	MAX30102_vInit();

	/* Battery intialize */
	BAT_vInit();

	/* COMM init for receiving data */
	COMM_vInit();

	/* FLASH init */
	FLASH_vInit();

	/* Assign callback function for timer1 */
//	TIM1_vCallBack_OVF( isMaxDone );
//	TIM1_vSetPreload( 3036 );	/* 4 sec*/
//	TIM1_vTurnOn();

	/* Enable the Global interrupt */
	GIE_vEnableGlobaLInt();

	while(1){
		switch(G_u8currentState){
			case MAX_STATE:{
				MAX30102_vUpdate();

				break;
			}
			case ACC_STATE: {		/* Read Acceleration in a buffer of 32 instances ??*/
				sendAccelertation();
				break;
			}
			case EMRG_STATE: {
				EMRG_vStart();	/* Changed by the COMM module */
				break;
			}
			case SEND_STATE: {
				TIM1_vTurnOff();

				HC_vSendString("X\n");	/* tell the Gateway that this is all data */

				MAX30102_vGetCurrentReading(&pulseOximeter);

				JSON_strMakeBatteryObj ( BAT_u8GetPercentage(), batteryJson, sizeof(batteryJson));
				JSON_strMakeTimeObj	   ( TIME_u32GetTime(), timeJson, sizeof(timeJson));
				JSON_strMakeMaxObj     ( pulseOximeter, maxJson, sizeof(maxJson));
				JSON_strMakeJsonObj    ( timeJson, batteryJson, maxJson, myJson, sizeof(myJson));

				HC_vSendString( myJson );
				HC_vSendData('\n');

				TIM1_vTurnOn();

				MAX30102_vResetParams();
				G_u8currentState = MAX_STATE;
				break;
			}
			case NULL_STATE:
			{
				break;
			}
			default: 				/* Shouldn't be here */	break;
		}
	}
}

static void sendMaxJson();
static void sendAccJson();

static void sendAccelertation(){
	u8 x_axis[5];
	u8 y_axis[5];
	u8 z_axis[5];

	ADXL_vReadAllAxes(&acceleration);

	snprintf(x_axis, sizeof(x_axis) ,"%d.%02u",
			(int) acceleration.x_axis,
			(int) ((acceleration.x_axis - (int) acceleration.x_axis ) * 100) );

	snprintf(y_axis, sizeof(y_axis) ,"%d.%02u",
			(int) acceleration.y_axis,
			(int) ((acceleration.y_axis - (int) acceleration.y_axis ) * 100) );

	snprintf(z_axis, sizeof(z_axis) ,"%d.%02u",
			(int) acceleration.z_axis,
			(int) ((acceleration.z_axis - (int) acceleration.z_axis ) * 100) );

	HC_vSendString("A\n");	/* Tell gateway that this is acceleration data */

	HC_vSendString("X:");
	HC_vSendString(x_axis);
	HC_vSendData(',');

	HC_vSendString("Y:");
	HC_vSendString(y_axis);
	HC_vSendData(',');

	HC_vSendString("Z:");
	HC_vSendString(z_axis);

	HC_vSendData('\n');
}

static void isMaxDone() {
	static u16 maxCounter = 0 ;
	maxCounter++;

	if(maxCounter == 5) {	/* 40 seconds */
		G_u8currentState = ACC_STATE;

	} else if(maxCounter == 6) {		/* 44 seconds*/
		G_u8currentState = SEND_STATE;	/* Send all JSON*/
		maxCounter = 0;
		TIM1_vTurnOff();
	}

	TIM1_vSetPreload( 3036 );
}


static void doMaxAlgo(){
	G_u8currentState = MAX_STATE;
}

static void sendPayload(){
	G_u16CountToMin++;

	if(G_u16CountToMin == 1831){	/* 30 seconds has passed */
		HC_vSendString("OK\n");

		MAX30102_vGetCurrentReading(&pulseOximeter);
		ADXL_vReadAllAxes(&acceleration);

		//JSON_strMakeAccObj	   ( acceleration, accJson, sizeof(accJson));
		JSON_strMakeBatteryObj ( 67, batteryJson, sizeof(batteryJson));
		JSON_strMakeTimeObj	   ( TIME_u32GetTime(), timeJson, sizeof(timeJson));
		JSON_strMakeMaxObj     ( pulseOximeter, maxJson, sizeof(maxJson));
		JSON_strMakeJsonObj    (  timeJson, batteryJson, maxJson, myJson, sizeof(myJson));

		HC_vSendString( myJson );
		HC_vSendData('\n');
		G_u16CountToMin = 0; /* Reset Counter */
	}
}

static void sendAsInteger(s32 A_s32Bpm){
	u8 L_u8Buffer[10] = {0};
	u8 i=0;

	if(A_s32Bpm == 0){
		HC_vSendData('0');
		return;
	}

	if(A_s32Bpm < 0){
		HC_vSendData('-');
		A_s32Bpm *= -1;
	}

	for(i=0; A_s32Bpm !=0; i++){
		L_u8Buffer[i] =  A_s32Bpm % 10;
		A_s32Bpm /= 10;
	}

	for(s8 j = i - 1; j>=0; j--){
		HC_vSendData(L_u8Buffer[j] + '0');
	}

}
