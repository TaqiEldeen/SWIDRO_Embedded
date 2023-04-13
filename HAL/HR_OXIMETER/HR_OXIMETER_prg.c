/*
 * HR_OXIMETER_reg.h
 *
 *  Created on: Dec 1, 2022
 *      Author: Ahmed Othman
 *  "THIS FOR MAX30102 Senseor (Heart Rate and Oximeter)"
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/TWI/TWI_int.h"
#include "../HC/HC_int.h"	/* For debugging*/
#include "../ADXL/ADXL_int.h"

#define UART_vSendData HC_vSendData

#include "../../Service/TIME/TIME_int.h"

#include "HR_OXIMETER_reg.h"
#include "HR_OXIMETER_pri.h"
#include "HR_OXIMETER_cfg.h"
#include "HR_OXIMETER_int.h"
#include "filters.h"

#include <math.h>
#include <avr/delay.h>
#define F_CPU 16000000UL

#define DEBUG 	TRUE

/* ************************************* */
/* NEEDED PARMETER*/
/* ************************************* */
#define ALPHA 0.97
#define ACC_SMOOTH_FACTOR	0.5


/* Pulse Detection Parameters */
#define PULSE_MIN_THRESHOLD 20 		/* 300 is good for finger , but wrist you need like 20, and there is too much noise */
#define PULSE_MAX_THRESHOLD 2500
#define PULSE_GO_DOWN_THRESHOLD 1
#define PULSE_BPM_SAMPLE_SIZE 30
#define PROXIMITY_THRESH (u32)20000

#define RESET_SPO2_EVERY_N_PULSES	4

/* Global variables */

adxl_t accelerometer;

/* Filters Variable */
volatile DC_Filter dcFilterIR;
volatile DC_Filter dcFilterRed;
volatile MEANDiff_Filter meanDiffIR;
volatile Butterworth_Filter lpbFilterIR;

FIFO_SAMPLE G_sample;


/* Used by checkBeat function */
static u8 G_u8CurrentPulseDetectorState;
static f32 G_f32CurrentBPM = 0.0;
static f32 G_f32ValuesBPM[PULSE_BPM_SAMPLE_SIZE];
static f32 G_f32ValuesBPMSum;
static u8 G_u8ValuesBPMCount;
static u8 G_u8BPMIndex;
static u32 G_u32LastBeatThreshold;
static u8 G_u8PulsesNum = 0;

/* Used for SPO2 calculation */
static f32 G_f32IrAcValueSqSum = 0;
static f32 G_f32RedAcValueSqSum = 0;
static f32 G_f32CurrentSaO2Value = 0;

//static volatile FIFO_SAMPLE G_u8SamplesBuffer[10];


/* A custom made log function */
static f32 myLog(f32 x) {
    f32 result = 0.0;
    f32 term = (x - 1.0) / x;
    f32 term_squared = term * term;
    u8 i;

    for (i = 1; i <= 50; i += 2) {
        result += term;
        term *= -term_squared;
    }

    return 2.0 * result;
}


void MAX30102_vResetParams(){
    dcFilterIR.w = 0;
    dcFilterIR.result = 0;
    dcFilterRed.w = 0;
    dcFilterRed.result = 0;

    meanDiffIR.count = 0;
    meanDiffIR.index = 0;
    meanDiffIR.sum = 0;

    lpbFilterIR.result = 0;
    lpbFilterIR.values[0] = 0;
    lpbFilterIR.values[1] = 0;

    G_u8CurrentPulseDetectorState = PULSE_IDLE;
    G_f32ValuesBPM[0] = 0;
    G_f32ValuesBPMSum = 0;
    G_u8ValuesBPMCount = 0;
    G_u8BPMIndex = 0;
    G_u32LastBeatThreshold = 0;
}

/* ********************************************************************* */
/* ******************************** init ******************************* */
/* ********************************************************************* */
void MAX30102_vInit()
{
    u8 L_u8RegContent;
    /* Init I2C Comm */
    TWI_vMasterInit();

    /* ******************************************** */
    /*
    -------Send Configuration of FIFO Register-------
    -> SMP AVG
    -> FIFO_ROLLOVER_EN
    -> FIFO_A_FULL
     */
    /* Enable ROLL OVER*/
    /* ******************************************** */

    L_u8RegContent = (SAMPLEAVG_SELECTED << SMP_AVE_START_BIT) | (1 << FIFO_ROLL_OVER_EN);

    wrtRegContent(SLAVE_ADDRESS, FIFO_Configuration_address, L_u8RegContent);


    /* ******************************************** */
    /*
    -------Send Configuration of MODE Register-------
    -> SHDN
    -> RESET
    -> MODE
     */
    /* ******************************************** */

    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | (MODE_CONTROL_SELECTED << MODE_START_BIT);
    wrtRegContent(SLAVE_ADDRESS, MODE_Configuration_address, L_u8RegContent);

    /* ******************************************** */
    /*
    -------Send Configuration of SPO2 Register-------
    -> SPO2 ADC Range
    -> SPO2 Sample Rate
    -> LED Pulse Width Control
    */
    /* ******************************************** */

    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | (ADCRANGE_SELECTED << SPO2_ADC_RGE_START_BIT) | (SAMPLERATE_SELECTED << SPO2_SR_START_BIT) | (PULSEWIDTH_SELECTED << LED_PW_START_BIT);
    wrtRegContent(SLAVE_ADDRESS, SpO2_Configuration_address, L_u8RegContent);

    /* ******************************************** */
    /*
    -------Send Configuration of MULTI Control Register-------
    ->SLOT1 IR
    ->SLOT2 LED
    */
    /* ******************************************** */

    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | (SLOT1_LED_SELECTED << SLOT_1_START_BIT) | (SLOT2_LED_SELECTED << SLOT_2_START_BIT);
    wrtRegContent(SLAVE_ADDRESS, MULTI_LED_REG_S1_S2_address, L_u8RegContent);

    /* ******************************************** */
    /*
    -------Send Configuration of LPA Register-------
    ->LED1 IR
    ->LED2 RED
    */
    /* ******************************************** */

    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | LED1_IR_CURRENT_SELECTED;
    wrtRegContent(SLAVE_ADDRESS, LED1_PA_address, L_u8RegContent);
    L_u8RegContent = (L_u8RegContent & REG_MASK_CLEAN) | LED2_RED_CURRENT_SELECTED;
    wrtRegContent(SLAVE_ADDRESS, LED2_PA_address, L_u8RegContent);

    /* ******************************************** */
    /*
    -------Reset FIFO-------
    ->Write Ptr
    ->OverFlow Couter
    ->Read Ptr
    */
    /* ******************************************** */
    wrtRegContent(SLAVE_ADDRESS, FIFO_WR_PTR_address, 0x00);
    wrtRegContent(SLAVE_ADDRESS, OVF_COUNTER_address, 0x00);
    wrtRegContent(SLAVE_ADDRESS, FIFO_RD_PTR_address, 0x00);

    /* ******************************************** */
    /*
    -------Init Variables -------
    */
    /* ******************************************** */
    dcFilterIR.w = 0;
    dcFilterIR.result = 0;
    dcFilterRed.w = 0;
    dcFilterRed.result = 0;

    meanDiffIR.count = 0;
    meanDiffIR.index = 0;
    meanDiffIR.sum = 0;

    lpbFilterIR.result = 0;
    lpbFilterIR.values[0] = 0;
    lpbFilterIR.values[1] = 0;

    G_u8CurrentPulseDetectorState = PULSE_IDLE;
    G_f32ValuesBPM[0] = 0;
    G_f32ValuesBPMSum = 0;
    G_u8ValuesBPMCount = 0;
    G_u8BPMIndex = 0;
    G_u32LastBeatThreshold = 0;
}


/* ********************************************************************* */
/* ********************* Read Data From Fifo ************************    */
/* ********************************************************************* */
FIFO_SAMPLE MAX30102_ReadFIFO()
{
    FIFO_SAMPLE L_sample;
    u32 L_u32RedLedSample = 0;
    u32 L_u32IRLedSample = 0;
    u8 L_u8TempBuff[6];
    getRegContentMulti(SLAVE_ADDRESS, FIFO_DATA_address, 6, L_u8TempBuff);

    /* IR LED */
    L_u32IRLedSample  = ((u32)(L_u8TempBuff[0])) << 16;
    L_u32IRLedSample |= ((u32)L_u8TempBuff[1]) << 8;

    /* RED LED*/
    L_u32RedLedSample = ((u32)(L_u8TempBuff[3])) << 16;
    L_u32RedLedSample |= ((u32)L_u8TempBuff[4]) << 8;

	#if PULSEWIDTH_SELECTED == PULSEWIDTH_69

		L_u32IRLedSample |= ((u32)L_u8TempBuff[2]) << 3;
		L_u32RedLedSample |= ((u32)L_u8TempBuff[5]) << 3;

		L_u32IRLedSample = L_u32IRLedSample >> 3;

		L_u32RedLedSample = L_u32RedLedSample >> 3;

	#elif PULSEWIDTH_SELECTED == PULSEWIDTH_118

		L_u32IRLedSample |= ((u32)L_u8TempBuff[2]) << 2;
		L_u32RedLedSample |= ((u32)L_u8TempBuff[5]) << 2;

		L_u32IRLedSample &= MSB_MASK; // MASK From Bit 18-31
		L_u32RedLedSample &= MSB_MASK; // MASK From Bit 18-31

		L_u32IRLedSample = L_u32IRLedSample >> 2;

		L_u32RedLedSample = L_u32RedLedSample >> 2;

	#elif PULSEWIDTH_SELECTED == PULSEWIDTH_215

		L_u32IRLedSample |= ((u32)L_u8TempBuff[2]) << 1;
		L_u32RedLedSample |= ((u32)L_u8TempBuff[5]) << 1;

		L_u32IRLedSample &= MSB_MASK; // MASK From Bit 18-31
		L_u32RedLedSample &= MSB_MASK; // MASK From Bit 18-31

		L_u32IRLedSample = L_u32IRLedSample >> 1;

		L_u32RedLedSample = L_u32RedLedSample >> 1;

	#elif PULSEWIDTH_SELECTED == PULSEWIDTH_411

		L_u32IRLedSample |= ((u32)L_u8TempBuff[2]) << 0;
		L_u32RedLedSample |= ((u32)L_u8TempBuff[5]) << 0;

		L_u32IRLedSample &= MSB_MASK; // MASK From Bit 18-31
		L_u32RedLedSample &= MSB_MASK; // MASK From Bit 18-31

	#endif

    L_sample.rawIR = L_u32IRLedSample;
    L_sample.rawRED = L_u32RedLedSample;
    /* Set RD PTR to 0x00 */
    // wrtRegContent(SLAVE_ADDRESS, FIFO_RD_PTR_address, 0x00);
    return L_sample;
}

/* ********************************************************************* */
/* ********************* Collect Group Sample *********************** */
/* ********************************************************************* */
static void HR_OXIMETER_vCollectGroupOfSamples()
{
    FIFO_SAMPLE L_sample = MAX30102_ReadFIFO();
    display_data_Collected(L_sample.rawIR, L_sample.rawRED);
}


/* ********************************************************************* */
/* ************************** Calculate Heart Rate ********************* */
/* ********************************************************************* */
void MAX30102_vUpdate()
{
	f32 L_f32IRComponent;
	f32 L_f32EDComponent;
	f32 L_f32RatioRMS;
//    f32 smoothAccel;
//    f32 artifactRemovedValue;

    s8 L_s8SampleNum;
    L_s8SampleNum = readWrtPtr() - readRdPtr() ;
    if(L_s8SampleNum < 0) { // read pointer after write pointer
    	L_s8SampleNum += 32;
    }

    for(u8 i=0; i < L_s8SampleNum; i++){
    	/* G_sample is being updated by MAX30102_boolCheckContact*/
    	if (!MAX30102_boolCheckContact()){ /* Skip sample if the sensor not in contact */
    		continue;
    	}

        //ADXL_vReadAllAxes(&accelerometer);

//        smoothAccel = ACC_SMOOTH_FACTOR * accelerometer.magnitude
//        				+ (1 - ACC_SMOOTH_FACTOR)*smoothAccel;

        dcFilterIR  = HR_OXIMETER_DCRemoval((f32)G_sample.rawIR, dcFilterIR.w, ALPHA);
        dcFilterRed = HR_OXIMETER_DCRemoval((f32)G_sample.rawRED, dcFilterRed.w, ALPHA);

//        artifactRemovedValue = dcFilterIR.result - smoothAccel;

        f32 L_f32meanDiffResIR  = HR_OXIMETER_f32MeanDiff( dcFilterIR.result + 20, &meanDiffIR);
        HR_OXIMETER_vLowPassButterworthFilter(dcFilterIR.result, &lpbFilterIR);

		#if DEBUG == TRUE
				sendAsInteger(TIME_u32GetTime());
				HC_vSendData(',');
				sendAsInteger(G_sample.rawIR);
				HC_vSendData(',');
				sendAsInteger(dcFilterIR.result);
				HC_vSendData(',');
				sendAsInteger(lpbFilterIR.result);
				HC_vSendData(',');
				sendAsInteger(G_f32CurrentBPM);
				HC_vSendData(',');
				sendAsInteger(G_f32CurrentSaO2Value);
				HC_vSendData('\n');
		#endif


        G_f32IrAcValueSqSum += dcFilterIR.result * dcFilterIR.result;
        G_f32RedAcValueSqSum += dcFilterRed.result * dcFilterRed.result;

        if (MAX30102_u8CheckBeat(lpbFilterIR.result) == TRUE) {
        	G_u8PulsesNum++;

            L_f32IRComponent = myLog(sqrt(G_f32IrAcValueSqSum / 32.0));
            L_f32EDComponent = myLog(sqrt(G_f32RedAcValueSqSum / 32.0));
            L_f32RatioRMS    = L_f32EDComponent / L_f32IRComponent;

            G_f32CurrentSaO2Value = 110.0 - 18.0 * L_f32RatioRMS;
        }
    }
    /* Reset after 32 samples */
    G_f32IrAcValueSqSum = 0;
    G_f32RedAcValueSqSum = 0;
}


/* ********************************************************************* */
/* ************************** Calculate Heart Rate ********************* */
/* ********************************************************************* */
void MAX30102_vUpdate2()
{
	f32 L_f32IRComponent;
	f32 L_f32EDComponent;
	f32 L_f32RatioRMS;

    s8 L_s8SampleNum = readWrtPtr() - readRdPtr() ;
    if(L_s8SampleNum < 0) { // read pointer after write pointer
    	L_s8SampleNum += 32;
    }

    for(u8 i=0; i < L_s8SampleNum; i++ ) {
		G_sample = MAX30102_ReadFIFO();

		dcFilterIR  = HR_OXIMETER_DCRemoval((f32)G_sample.rawIR, dcFilterIR.w, ALPHA);
		dcFilterRed = HR_OXIMETER_DCRemoval((f32)G_sample.rawRED, dcFilterRed.w, ALPHA);

		f32 L_f32meanDiffResIR  = HR_OXIMETER_f32MeanDiff( dcFilterIR.result , &meanDiffIR);
		HR_OXIMETER_vLowPassButterworthFilter(L_f32meanDiffResIR, &lpbFilterIR);

		G_f32IrAcValueSqSum += dcFilterIR.result * dcFilterIR.result;
		G_f32RedAcValueSqSum += dcFilterRed.result * dcFilterRed.result;

		if (MAX30102_u8CheckBeat(lpbFilterIR.result) == TRUE){
			G_u8PulsesNum++;

			L_f32IRComponent = myLog(sqrt(G_f32IrAcValueSqSum / 32.0));
			L_f32EDComponent = myLog(sqrt(G_f32RedAcValueSqSum / 32.0));
			L_f32RatioRMS    = L_f32EDComponent / L_f32IRComponent;

			G_f32CurrentSaO2Value = 110.0 - 18.0 * L_f32RatioRMS;

			if(G_u8PulsesNum == RESET_SPO2_EVERY_N_PULSES) {
				G_f32IrAcValueSqSum = 0;
				G_f32RedAcValueSqSum = 0;
				G_u8PulsesNum = 0;
			}
		}
    }
}

//void MAX30102_vFillSamples(){
//	G_u8SamplesBuffer[G_u8SamplesCounter] = MAX30102_ReadFIFO();
//	G_u8SamplesCounter++;
//	if(G_u8SamplesCounter > (sizeof(G_u8SamplesBuffer) / sizeof(G_u8SamplesBuffer[0]) ) ) {
//		G_u8SamplesCounter = 0; /* Roll over */
//	}
//}

/* ********************************************************************* */
/* ************************** Check Beat ********************* */
/* ********************************************************************* */
u8 MAX30102_u8CheckBeat(f32 A_f32SensorValue)
{
    static f32 L_f32PrevSensorValue = 0;
    static u8 L_u8ValuesWentDown = 0;
    static u32 L_u32CurrentBeat = 0;
    static u32 L_u32LastBeat = 0;

    if (A_f32SensorValue > PULSE_MAX_THRESHOLD)
    {
        G_u8CurrentPulseDetectorState = PULSE_IDLE;
        L_f32PrevSensorValue = 0;
        L_u32LastBeat = 0;
        L_u32CurrentBeat = 0;
        L_u8ValuesWentDown = 0;
        G_u32LastBeatThreshold = 0;
        return FALSE;
    }

    switch (G_u8CurrentPulseDetectorState)
    {
    case PULSE_IDLE:
        if (A_f32SensorValue >= PULSE_MIN_THRESHOLD)
        {
            G_u8CurrentPulseDetectorState = PULSE_TRACE_UP;
            L_u8ValuesWentDown = 0;
        }
        break;
    case PULSE_TRACE_UP:
        if (A_f32SensorValue > L_f32PrevSensorValue)
        {
            L_u32CurrentBeat = TIME_u32GetTime(); // This Variable has the counts of the time passed since the micro is on
            G_u32LastBeatThreshold = A_f32SensorValue;
        }
        else
        {
            u32 L_u32BeatDuration = L_u32CurrentBeat - L_u32LastBeat;
            L_u32LastBeat = L_u32CurrentBeat;
            f32 L_f32RawBPM = 0;

            if (L_u32BeatDuration > 0)
            {
                L_f32RawBPM = 60000.0 / (f32)L_u32BeatDuration;
            }


            G_f32ValuesBPM[G_u8BPMIndex] = L_f32RawBPM;
            G_f32ValuesBPMSum = 0;

            for (u32 i = 0; i < PULSE_BPM_SAMPLE_SIZE; i++)
            {
                G_f32ValuesBPMSum += G_f32ValuesBPM[i];
            }

            G_u8BPMIndex++;
            G_u8BPMIndex = G_u8BPMIndex % PULSE_BPM_SAMPLE_SIZE;

            if (G_u8ValuesBPMCount < PULSE_BPM_SAMPLE_SIZE)
                G_u8ValuesBPMCount++;

            G_f32CurrentBPM = G_f32ValuesBPMSum / G_u8ValuesBPMCount;

            G_u8CurrentPulseDetectorState = PULSE_TRACE_DOWN;
            return TRUE;
        }
        break;

    case PULSE_TRACE_DOWN:
        if (A_f32SensorValue < L_f32PrevSensorValue)
        {
            L_u8ValuesWentDown++;
        }
        if (A_f32SensorValue < PULSE_MIN_THRESHOLD)
        {
            G_u8CurrentPulseDetectorState = PULSE_IDLE;
        }
        break;
    }

    L_f32PrevSensorValue = A_f32SensorValue;
    return FALSE;
}

/**********************************************************************************************************
 * Description : Interface Function to get the current reading of the MAX30102 sensor
 * Outputs     : BPM and SPO2 in the object
 * Inputs      : MAX_t object
 * Notes	   : You need to enable reading before calling otherwise you get a random data
 ***********************************************************************************************************/
void MAX30102_vGetCurrentReading(max_t *obj){
	obj->currentBeat = (u8) G_f32CurrentBPM;
	obj->currentSpo2 = (u8) G_f32CurrentSaO2Value;
}


/* ********************************************************************* */
/* *********************** Read Multiple Bytes ************************* */
/* ********************************************************************* */
static void getRegContentMulti(u8 A_u8SlaveAdd, u8 A_u8Reg, u8 A_u8NofBytes, u8 *A_uBuffptr)
{
    u8 L_u8Stauts;
    TWI_vSendStartCondition(); // send start condition

    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 0); // send slave address with write
    /* 	Check the ack from sensor	*/
    L_u8Stauts = TWI_u8MasterGetStatus();
    if (L_u8Stauts != TWI_STATUS_MT_SLA_W_ACK)
    {
    	return;
    };

    /* Send register address */
    TWI_vMasterWriteDataByte(A_u8Reg);
    L_u8Stauts = TWI_u8MasterGetStatus();
    if (L_u8Stauts != TWI_STATUS_MT_DATA_ACK)
    {
    	return;
    };

    TWI_vSendStartCondition();                        // Sned Repeated Start
    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 1); // send slave address with Read
    /*while (L_u8Stauts != TWI_STATUS_MT_SLA_R_ACK)
    {
    };*/
    for (u32 k = 0; k < (A_u8NofBytes - 1); k++)
    {
        A_uBuffptr[k] = TWI_u8MasterReadDataByteWith_ACK();
    }
    A_uBuffptr[A_u8NofBytes - 1] = TWI_u8MasterReadDataByteWith_NACK();
    TWI_vSendStopCondition();
}


/* ********************************************************************* */
/* ************************** Read One Byte **************************** */
/* ********************************************************************* */
static u8 getRegContentOnce(u8 A_u8SlaveAdd, u8 A_u8Reg)
{
    u8 L_u8Stauts;
    u8 L_u8RegContent;
    TWI_vSendStartCondition();                        // send start condition
    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 0); // send slave address with write
    /* Check the ack from sensor*/
    L_u8Stauts = TWI_u8MasterGetStatus();
    if (L_u8Stauts != TWI_STATUS_MT_SLA_W_ACK)
    {
    	return 0;
    };
    /* Send register address */
    TWI_vMasterWriteDataByte(A_u8Reg);
    L_u8Stauts = TWI_u8MasterGetStatus();
    if (L_u8Stauts != TWI_STATUS_MT_DATA_ACK)
    {
    	return 0;
    };

    TWI_vSendStartCondition();                        // Sned Repeated Start
    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 1); // send slave address with Read
    /*while (L_u8Stauts != TWI_STATUS_MT_SLA_R_ACK)
    {
    };*/

    L_u8RegContent = TWI_u8MasterReadDataByteWith_NACK();
    TWI_vSendStopCondition();
    return L_u8RegContent;
}


/* ********************************************************************* */
/* ************************** Write On Register ************************ */
/* ********************************************************************* */
static void wrtRegContent(u8 A_u8SlaveAdd, u8 A_u8Reg, u8 A_u8RegContent)
{
    u8 L_u8Stauts;
    TWI_vSendStartCondition();                        // send start condition
    TWI_vMasterWriteSlaveAdd((A_u8SlaveAdd >> 1), 0); // send slave address with write
    /* Check the ack from sensor*/
    L_u8Stauts = TWI_u8MasterGetStatus();
    if (L_u8Stauts != TWI_STATUS_MT_SLA_W_ACK)
    {
    };

    /* Send register address */
    TWI_vMasterWriteDataByte(A_u8Reg);
    L_u8Stauts = TWI_u8MasterGetStatus();
    if (L_u8Stauts != TWI_STATUS_MT_DATA_ACK)
    {
    }
    /* put data in the reg */
    TWI_vMasterWriteDataByte(A_u8RegContent);
    L_u8Stauts = TWI_u8MasterGetStatus();
    if (L_u8Stauts != TWI_STATUS_MT_DATA_ACK)
    {
    }
    TWI_vSendStopCondition();
}


void MAX30102_vGetPartINFO(u8 *A_u8RevID, u8 *A_u8PartID)
{
    *A_u8RevID = getRegContentOnce(SLAVE_ADDRESS, REVISION_ID_address);
    *A_u8PartID = getRegContentOnce(SLAVE_ADDRESS, PART_ID_address);
}


/**********************************************************************************************************
 * Description : Interface Function to put the MAX30102 in power-saving mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void MAX30102_vShutDown(){
	u8 L_u8RegContent = getRegContentOnce(SLAVE_ADDRESS, MODE_Configuration_address);
	SET_BIT(L_u8RegContent, SHDN);
    wrtRegContent(SLAVE_ADDRESS, MODE_Configuration_address, L_u8RegContent);
}


/**********************************************************************************************************
 * Description : Interface Function to put the MAX30102 in power-saving mode
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void MAX30102_vWakeUp(){
	u8 L_u8RegContent = getRegContentOnce(SLAVE_ADDRESS, MODE_Configuration_address);
	CLR_BIT(L_u8RegContent, SHDN);
    wrtRegContent(SLAVE_ADDRESS, MODE_Configuration_address, L_u8RegContent);
}


/**********************************************************************************************************
 * Description : Interface Function to check if the sensor is worn or not
 * Outputs     : TRUE or FALSE
 * Inputs      : void
 * NOTES	   : This function is based on PROXIMITY_THRESH
 * 				 TRUE  -> is in contact
 * 				 FALSE -> is not in contact
 ***********************************************************************************************************/
u8 MAX30102_boolCheckContact(){

	G_sample = MAX30102_ReadFIFO();
	if(G_sample.rawIR < PROXIMITY_THRESH) {
		return FALSE;
	}
	return TRUE;
}



static u8 readWrtPtr(){
	return getRegContentOnce(SLAVE_ADDRESS, FIFO_WR_PTR_address);
}

static u8 readRdPtr(){
	return getRegContentOnce(SLAVE_ADDRESS, FIFO_RD_PTR_address);
}

static u8 isSamplesReady(){
	/*Read the A_FULL flag*/
	return ( getRegContentOnce(SLAVE_ADDRESS, INT_STATUS1_Address) & 0x80 );
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
