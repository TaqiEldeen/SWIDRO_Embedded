/*
 * HR_OXIMETER_reg.h
 *
 *  Created on: Dec 1, 2022
 *      Author: Ahmed Othman
 *  "THIS FOR MAX30102 Senseor (Heart Rate and Oximeter)"
 */
#ifndef HAL_HR_OXIMETER_HR_OXIMETER_PRI_H_
#define HAL_HR_OXIMETER_HR_OXIMETER_PRI_H_

/* *********************************************************** */
/* Needed Masks*/
/* *********************************************************** */
#define REG_MASK_CLEAN 0x00
#define MSB_MASK 0x0003FFFF

/* ************************************* */
/* Sensor Device Address */
/* ************************************* */
#define SLAVE_ADDRESS 0xAE

/* *********************************************************** */
/* FIFO CONFIGURATION */
/* *********************************************************** */
/* SAMPLE Averaging Options */
#define SAMPLEAVG_1 0
#define SAMPLEAVG_2 1
#define SAMPLEAVG_4 2
#define SAMPLEAVG_8 3
#define SAMPLEAVG_16 4
#define SAMPLEAVG_32 5

/* *********************************************************** */
/* Mode CONFIGURATION */
/* *********************************************************** */
/* MODE Options */
#define RED_ONLY 2
#define RED_IR 3
#define MULTI_RED_IR 7

/* *********************************************************** */
/* SpO2 CONFIGURATION */
/* *********************************************************** */
/* SpO2 ADC Range Control Options*/
#define ADCRANGE_2048 0
#define ADCRANGE_4096 1
#define ADCRANGE_8192 2
#define ADCRANGE_16384 3

/* SpO2 Sample Rate Control */
#define SAMPLERATE_50 0
#define SAMPLERATE_100 1
#define SAMPLERATE_200 2
#define SAMPLERATE_400 3
#define SAMPLERATE_800 4
#define SAMPLERATE_1000 5
#define SAMPLERATE_1600 6
#define SAMPLERATE_3200 7

/* LED Pulse Width Control and ADC Resolution */
#define PULSEWIDTH_69 0  /* (ADC RESOLUTION 15-BIT) */
#define PULSEWIDTH_118 1 /* (ADC RESOLUTION 16-BIT) */
#define PULSEWIDTH_215 2 /* (ADC RESOLUTION 17-BIT) */
#define PULSEWIDTH_411 3 /* (ADC RESOLUTION 18-BIT) */

/* *********************************************************** */
/* LED Pulse Amplitude (These bits set the current level of each LED)*/
/* *********************************************************** */
#define LEDCURRENT_0_0 		0x00
#define LEDCURRENT_0_2 		0x01
#define LEDCURRENT_0_4 		0x02
#define LEDCURRENT_3_0 		0x0F
#define LEDCURRENT_6_2 		0x1F
#define LEDCURRENT_12_6 	0x3F
#define LEDCURRENT_25_4 	0x7F
#define LEDCURRENT_WRIST	0xDF
#define LEDCURRENT_51_0 	0xFF

/* *********************************************************** */
/* MULTI MODE Control register*/
/* *********************************************************** */
#define IR_LED 1
#define RED_LED 2



static u8 readRdPtr();
static u8 readWrtPtr();
static u8 isSamplesReady();
static void sendAsInteger(s32 A_s32Bpm);

/* *********************************************************** */
/* Functions to collect group of samples */
/* *********************************************************** */
static void HR_OXIMETER_vCollectGroupOfSamples();

/* *********************************************************** */
/* I2C Functions */
/* *********************************************************** */
static u8 getRegContentOnce(u8 A_u8SlaveAdd, u8 A_u8Reg);
static void getRegContentMulti(u8 A_u8SlaveAdd, u8 A_u8Reg, u8 A_u8NofBytes, u8 *A_uBuffptr);
static void wrtRegContent(u8 A_u8SlaveAdd, u8 A_u8Reg, u8 A_u8RegContent);


/* Functions i will remove later */
void display_red_ir(u32 ir, u32 red, u8 samples);
void toggle_led();
void display_data_Collected(u32 A_u32IRReading, u32 A_u32RedReading);
void display_HeartRate_Oxygen(u32 A_u32HeartRate, u32 A_u32Oxygen);
void sendToDebugSw(u8 data);
void sendStringToDebugSw(u8 *string);
void send32BitDatatoDebugger(u32 data);
void sendCharTOSw(u8 data);

#endif /* HAL_HR_OXIMETER_HR_OXIMETER_PRI_H_ */
