/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 14 Apr 2023		**************/
/*********************************************************/

/* LIB inclusion */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

/* MCAL inclusion*/
#include "../../MCAL/EXTI/EXTI_int.h"

/* System states inclusion */
#include "../../App/states.h"

/* Module inclusion */
#include "BTN_pri.h"
#include "BTN_int.h"

/* AVR UTIL */
#include <util/delay.h>

extern u8 G_u8currentState;	/* The main state */

/**********************************************************************************************************
 * Description : Interface Function to initialize the battery
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
void BTN_vInit(){
	/* Initialize external interrupt 0 on PD2 */
    EXTI_vInitINT0();

    EXTI_vReg_Func(BTN_vEmrgHandler, INT0_ID);
}

/**********************************************************************************************************
 * Description : Private Function Handle the emergency button
 * Outputs     : void
 * Inputs      : void
 ***********************************************************************************************************/
static void BTN_vEmrgHandler() {
	/* De-bouncing */
	_delay_ms(25);
	/* Change system state to emergency */
	G_u8currentState = EMRG_STATE;
}
