/*
 * HR_OXIMETER_int.h
 *
 *  Created on: Dec 1, 2022
 *      Author: Dell
 */

#ifndef HAL_HR_OXIMETER_HR_OXIMETER_INT_H_
#define HAL_HR_OXIMETER_HR_OXIMETER_INT_H_



/* *********************************************************** */
/* Needed DataTypes*/
/* *********************************************************** */
typedef struct
{
    u32 rawIR;
    u32 rawRED;
} FIFO_SAMPLE;

typedef enum PulseStateMachine
{
    PULSE_IDLE,
    PULSE_TRACE_UP,
    PULSE_TRACE_DOWN
} PulseStateMachine;

typedef struct {
	u8 currentBeat;
	u8 currentSpo2;
} max_t;


/* *********************************************************** */
/* Init
/* *********************************************************** */
void MAX30102_vInit();

/* *********************************************************** */
/* Read FiFo (only get one sample) */
/* *********************************************************** */
FIFO_SAMPLE MAX30102_ReadFIFO();

/* *********************************************************** */
/* Get HeartRate and Oxygen */
/* *********************************************************** */
void MAX30102_vUpdate();

void MAX30102_vUpdate2();

void MAX30102_vFillSamples();

void MAX30102_vResetParams();

/**********************************************************************************************************
 * Description : Interface Function to get the current reading of the MAX30102 sensor
 * Outputs     : BPM and SPO2 in the object
 * Inputs      : MAX_t object
 * Notes	   : You need to enable reading before calling otherwise you get a random data
 ***********************************************************************************************************/
void MAX30102_vGetCurrentReading(max_t *obj);

/**********************************************************************************************************
 * Description : Interface Function to put the MAX30102 in power-saving mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void MAX30102_vShutDown();

/**********************************************************************************************************
 * Description : Interface Function to Wake up the MAX30102
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void MAX30102_vWakeUp();

/**********************************************************************************************************
 * Description : Interface Function to check if the sensor is worn or not
 * Outputs     : TRUE or FALSE
 * Inputs      : void
 * NOTES	   : This function is based on PROXIMITY_THRESH
 * 				 TRUE  -> is in contact
 * 				 FALSE -> is not in contact
 ***********************************************************************************************************/
u8 MAX30102_boolCheckContact();

/* *********************************************************** */
/* Get Sensor info */
/* *********************************************************** */
void MAX30102_vGetPartINFO(u8 *A_u8RevID, u8 *A_u8PartID);


u8 MAX30102_u8CheckBeat(f32 A_f32SensorValue);


#endif /* HAL_HR_OXIMETER_HR_OXIMETER_INT_H_ */
