/*********************************************************/
/***********		Author: MICHAEL		 	**************/
/***********		Contributer: TaqiEldeen **************/
/***********		Layer: HAL			 	**************/
/***********		Component: ADXL345		**************/
/***********		Version: 1.01		 	**************/
/***********		Date: 11-Nov-22	 		**************/
/*********************************************************/


#ifndef ADXL_INT_H_
#define ADXL_INT_H_

/************************************************************************/
/*					Structure type for reading                          */
/************************************************************************/
typedef struct{
	f32 x_axis;
	f32 y_axis;
	f32 z_axis;
	f32 magnitude;
}adxl_t;


/**********************************************************************************************************
 * Description : Interface Function to initialize the ADXL sensor
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void ADXL_vInit();

/**********************************************************************************************************
 * Description : Interface Function to read all axis to a struct type
 * Outputs     : updates the structure object with the axis values
 * Inputs      : structure object
 ***********************************************************************************************************/
void ADXL_vReadAllAxes(adxl_t* event);

/**********************************************************************************************************
 * Description : Interface Function to put the sensor in sleep mode
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : Still need some work
 ***********************************************************************************************************/
void ADXL_vSleepMode();

/**********************************************************************************************************
 * Description : Interface Function to put the sensor in standby mode
 * Outputs     : void
 * Inputs      : void
 * NOTES	   : Still need some work
 ***********************************************************************************************************/
void ADXL_vStandbyMode();


#endif /* ADXL_INT_H_ */
