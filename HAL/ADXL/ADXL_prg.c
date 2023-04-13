/*********************************************************/
/***********		Author: MICHAEL		 	**************/
/***********		Contributer: TaqiEldeen **************/
/***********		Layer: HAL			 	**************/
/***********		Component: ADXL345		**************/
/***********		Version: 1.01		 	**************/
/***********		Date: 11-Nov-22	 		**************/
/*********************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/TWI/TWI_int.h"

#include "ADXL_reg.h"
#include "ADXL_int.h"
#include "ADXL_cfg.h"
#include "ADXL_pri.h"
#include "../../MCAL/UART/UART_int.h"
#include <math.h>
#include <avr/delay.h>

static u8 writeData(u8 A_u8Reg, u8 A_u8Data){
	TWI_vSendStartCondition();
	if(TWI_u8MasterGetStatus() == TWI_STATUS_START)
		TWI_vMasterWriteSlaveAdd(ADXL_DEVID, TWI_SLAVE_WR);
	else
		return 0;
	if(TWI_u8MasterGetStatus() == TWI_STATUS_MT_SLA_W_ACK)
		TWI_vMasterWriteDataByte(A_u8Reg);
	else
		return 1;
	if(TWI_u8MasterGetStatus() == TWI_STATUS_MT_DATA_ACK)
		TWI_vMasterWriteDataByte(A_u8Data);
	else
		return 2;
	if(TWI_u8MasterGetStatus() == TWI_STATUS_MT_DATA_ACK)
		TWI_vSendStopCondition();
	else
		return 3;
	/*No error*/
	return 9;
}

static u8 readData(u8 A_u8Reg, u8 *A_u8Buffer){
	TWI_vSendStartCondition();
	if(TWI_u8MasterGetStatus() == TWI_STATUS_START)
		TWI_vMasterWriteSlaveAdd(ADXL_DEVID, TWI_SLAVE_WR);
	else
		return 0;
	if(TWI_u8MasterGetStatus() == TWI_STATUS_MT_SLA_W_ACK)
		TWI_vMasterWriteDataByte(A_u8Reg);
	else
		return 1;
	if(TWI_u8MasterGetStatus() == TWI_STATUS_MT_DATA_ACK)
		TWI_vSendStartCondition();
	else
		return 3;
	if(TWI_u8MasterGetStatus() == TWI_STATUS_REP_START)
		TWI_vMasterWriteSlaveAdd(ADXL_DEVID, TWI_SLAVE_RD);
	else
		return 4;
	if(TWI_u8MasterGetStatus() == TWI_STATUS_MT_SLA_R_ACK){
		A_u8Buffer[0] = TWI_u8MasterReadDataByteWith_ACK();
		if(TWI_u8MasterGetStatus() == TWI_STATUS_MR_DATA_ACK)
			A_u8Buffer[1] = TWI_u8MasterReadDataByteWith_ACK();
		else
			return 6;
		if(TWI_u8MasterGetStatus() == TWI_STATUS_MR_DATA_ACK)
			A_u8Buffer[2] = TWI_u8MasterReadDataByteWith_ACK();
		else
			return 7;
		if(TWI_u8MasterGetStatus() == TWI_STATUS_MR_DATA_ACK)
			A_u8Buffer[3] = TWI_u8MasterReadDataByteWith_ACK();
		else
			return 8;
		if(TWI_u8MasterGetStatus() == TWI_STATUS_MR_DATA_ACK)
			A_u8Buffer[4] = TWI_u8MasterReadDataByteWith_ACK();
		else
			return 10;
		if(TWI_u8MasterGetStatus() == TWI_STATUS_MR_DATA_ACK)
			A_u8Buffer[5] = TWI_u8MasterReadDataByteWith_NACK();
		else
			return 11;
		if(TWI_u8MasterGetStatus() == TWI_STATUS_MR_DATA_NACK){
		}else{
			return 12;
		}
	} else
		return 5;
	TWI_vSendStopCondition();
	/*No error*/
	return 9;
}

static void assert(u8 A_u8ErrCode){
	switch(A_u8ErrCode){
		case 0:  UART_vSendStringSync("start error!"); break;
		case 1:  UART_vSendStringSync("Slave address+W err!"); break;
		case 2:  UART_vSendStringSync("Reg address err!"); break;
		case 3:  UART_vSendStringSync("Data write err!"); break;
		case 4:  UART_vSendStringSync("REP start err!"); break;
		case 5:  UART_vSendStringSync("Slave address+R err!"); break;
		case 6:  UART_vSendStringSync("Data1 err"); break;
		case 7:  UART_vSendStringSync("Data2 err!"); break;
		case 8:  UART_vSendStringSync("Data3 err!"); break;
		case 10: UART_vSendStringSync("Data4 err!"); break;
		case 11: UART_vSendStringSync("Data5 err!"); break;
		case 12: UART_vSendStringSync("DataNack err!"); break;
		case 9:  UART_vSendStringSync("No err!"); break;
	}
}

void ADXL_vInit(){
	/* TWI init */
	TWI_vMasterInit();

	/*Structure the data format options*/
	u8 L_u8DataFormat= (ADXL_SELF_TEST << SELF_TEST)
				|(ADXL_SPI_MODE		<< SPI)
				|(ADXL_INT_INVERT	<< INT_INVERT)
				|(ADXL_FULL_RES		<< FULL_RES)
				|(ADXL_JUSTIFY		<< JUSTIFY)
				|(ADXL_RANGE	    << RANGE0);

	/*Data Format register values*/
	writeData(DATA_FORMAT_REG, L_u8DataFormat);

	/*Apply measurement mode*/
	writeData(POWER_CTL_REG, 0x08);

	/*Selecting FIFO mode*/
	writeData(FIFO_CTL_REG, ADXL_FIFO_MODE << 6);
}

void ADXL_vReadAllAxes(adxl_t* event){
	u8 L_u8Buffer[6];

	/* Read data x,y,z by using multi-byte mode*/
	readData(DATAX0_REG, L_u8Buffer);

	/*get separate axis reading*/
	f32 x_axis = (L_u8Buffer[0] | (L_u8Buffer[1] << 8));
	f32 y_axis = (L_u8Buffer[2] | (L_u8Buffer[3] << 8));
	f32 z_axis = (L_u8Buffer[4] | (L_u8Buffer[5] << 8));

	/*Convert the axis reading*/
	event->x_axis = x_axis * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_EARTH ;//* 0.00390625;
	event->y_axis = y_axis * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_EARTH ;//* 0.00390625;
	event->z_axis = z_axis * ADXL345_MG2G_MULTIPLIER * SENSORS_GRAVITY_EARTH ;//* 0.00390625;
	event->magnitude = sqrt( pow(event->x_axis, 2) + pow(event->y_axis, 2) + pow(event->z_axis, 2) );

	/*getting the pitch and roll angles*/
//	event->pitch = ( atan2(event->x_axis, sqrt( (event->y_axis * event->y_axis ) +
//												(event->z_axis * event->z_axis ) ) * 180.0) ) / M_PI;
//
//	event->roll = ( atan2(event->y_axis, sqrt( (event->x_axis * event->x_axis ) +
//		   									   (event->z_axis * event->z_axis ) ) * 180.0) ) / M_PI;
}

void ADXL_vSleepMode(){

	/*
	to enable sleep mode,
	set THRESH_INACT register and TIME_INACT register each to a value that signifies inactivity
	*/

	writeData(THRESH_INACT_REG,0);
	writeData(TIME_INACT_REG,0);

	/*
	 then set the AUTO_SLEEP bit ,the link bit and Measure bit in the POWER_CTL register
	*/

	writeData(POWER_CTL_REG,0x38);

}

void ADXL_vStandbyMode(){
	/*In this mode, no measurements are made*/
	/* Enter standby mode by clearing the measure bit in the POWER_CTL register*/

	writeData(POWER_CTL_REG,0);
}
