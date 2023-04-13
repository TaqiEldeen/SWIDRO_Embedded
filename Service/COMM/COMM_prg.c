/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: 				 	**************/
/***********		Component: 				**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 27 Feb 2023		 	**************/
/*********************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../HAL/HC/HC_int.h"
#include "../../MCAL/UART/UART_int.h"
#include "../../App/states.h"

#include "COMM_int.h"
#include "COMM_pri.h"

extern u8 G_u8currentState;

void COMM_vInit(){
	/* Init UART*/

	/* Assign callback for RX*/
	UART_vSetCallBackRX( recieveState );
}

static void recieveState(u16 data) {
	if(data == 'E') {	/* Emergency*/
		G_u8currentState = EMRG_STATE;
	}
}

void COMM_vTransmit(u8 *buff){
}


void COMM_strReceive(){
}


u8 COMM_boolIsChannelFree() {
	u8 L_u8Char = 0;
	L_u8Char = HC_u8ReceiveDataSync();

	if(L_u8Char != ' '){	/* Is this right? */
		return FALSE;
	}

	return TRUE;
}
