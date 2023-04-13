/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: WDT			**************/
/***********		Version: 1.00		 	**************/
/***********		Date:  20 Sep 2022	 	**************/
/*********************************************************/
#ifndef MCAL_WDT_WDT_INT_H_
#define MCAL_WDT_WDT_INT_H_

/* Sleep options
 * 0 -> 16.3ms
 * 1 -> 32.5ms
 * 2 -> 65ms
 * 3 -> 0.13s
 * 4 -> 0.26s
 * 5 -> 0.52s
 * 6 -> 1.0s
 * 7 -> 2.1s
 * */

#define WDT_SLEEP_16_3_MS	0
#define WDT_SLEEP_32_5_MS	1
#define WDT_SLEEP_65_MS		2
#define WDT_SLEEP_0_13_S	3
#define WDT_SLEEP_0_26_S	4
#define WDT_SLEEP_0_52_S	5
#define WDT_SLEEP_1_0S		6
#define WDT_SLEEP_2_1_S		7

/**********************************************************************************************************
 * Description : Interface Function to Enable the WatchDog timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void WDT_vEnable(void);

/**********************************************************************************************************
 * Description : Interface Function to Disable the WatchDog timer
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void WDT_vDisable(void);

/**********************************************************************************************************
 * Description : Interface Function to setup the WatchDog timer sleep period
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void WDT_vSetSleep(u8 A_u8SleepTime);

#endif /* MCAL_WDT_WDT_INT_H_ */
