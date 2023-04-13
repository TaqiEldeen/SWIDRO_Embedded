/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: UART			**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 21 Sep 2022	 	**************/
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/UART/UART_pri.h"
#include "../../MCAL/UART/UART_cfg.h"
#include "../../MCAL/UART/UART_reg.h"
#include "../../MCAL/UART/UART_int.h"


/**********************************************************************************************************
 * Description : Interface Function to setup the UART based on the configuration
 * Outputs     : void
 * Inputs      : BaudRate
 * NOTES	   :the Global Interrupt Flag should be cleared (and interrupts globally-disabled)
 * 				when doing the initialization.
 ***********************************************************************************************************/
void UART_vInit(u16 A_u16BaudRate){
	/*Applying the configured modes in Register UCSRB*/
	UCSRB = 0x00;
	UCSRB |= (RX_COMPLETE_INTERRUPT << RXCIE)
			|(TX_COMPLETE_INTERRUPT << TXCIE)
			|(UDR_EMPTY_INTERRUPT   << UDRIE)
			|(RECEIVER_STATUS 		<< RXEN)
			|(TRANSMITTER_STATUS 	<< TXEN);


	/*Applying the configured modes in Register UCSRA*/

	/*The URSEL must be one when writing the UCSRC.*/
	UCSRC = 0x00;/*Clear the UCSRC register*/
	UCSRC  = (USART_MODE 		<< UMSEL)
			|(PARITY_MODE 		<< UPM0)
			|(STOP_BIT_SELECT 	<< USBS);


	/*Choosing the character size*/
	#if CHARACTER_SIZE == BIT_9_DATA
		SET_BIT(UCSRB, UCSZ2);
		UCSRC |= | (1<<UCSZ1) | (1<<UCSZ2);
	#else
		UCSRC |= (CHARACTER_SIZE << UCSZ0);
	#endif


	/*Choosing CLK polarity if in SYNC mode*/
	#if USART_MODE == SYNC_MODE
		UCSRC |= (CLK_POLARITY	<< UCPOL);
	#endif

	/*BAUD rate configuration*/
	UBRRH =  ( (0<<URSEL) | (A_u16BaudRate >> 8) );
	UBRRL = (u8)A_u16BaudRate;

	/*Setup the TX & RX pins*/
	DIO_vSetPinDir(TX_PORT, TX_PIN, DIR_OUTPUT);
	DIO_vSetPinDir(RX_PORT, RX_PIN, DIR_INPUT);
}


/**********************************************************************************************************
 * Description : Interface Function to send the data
 * Outputs     : void
 * Inputs      : Data
 ***********************************************************************************************************/
void UART_vSendCharSync(u16 A_u16Data){


	/*Wait till UDR is empty*/
	while( !(UCSRA & (1<<UDRE)) );

	/*Handle 9-bits character mode*/
	#if CHARACTER_SIZE == BIT_9_DATA
		if(A_u16Data & (1<<8)) {
			SET_BIT(UCSRB, TXB8);
		} else {
			CLR_BIT(UCSRB, TXB8);
		}
	#endif

	/*Sending the lower byte*/
	UDR = (u8)A_u16Data;


	/*
	 * WE can also use the Transmit complete flag

	while(!(UCSRA & (1<<TXC)));
	CRL_BIT(UCSRA, TXC);

	*/

	return;
}


/**********************************************************************************************************
 * Description : Interface Function to send the data
 * Outputs     : void
 * Inputs      : string data
 ***********************************************************************************************************/
void UART_vSendStringSync(u8 *A_u8Str){
	u8 L_u8Iterator = 0;
	while(A_u8Str[L_u8Iterator] != '\0') {
		UART_vSendCharSync(A_u8Str[L_u8Iterator]);
		L_u8Iterator++;
	}
	//UART_vSendCharSync('\0');
	return;
}


/**********************************************************************************************************
 * Description : Interface Function to send the data
 * Outputs     : the data received
 * Inputs      : void
 ***********************************************************************************************************/
u16 UART_u16ReceiveDataSync(){
	u16 L_u16Data = 0;

	/*Wait till Receiving the Data*/
	while( !(UCSRA & (1<<RXC)) );

	/*Handle 9-bits character mode*/
	#if CHARACTER_SIZE == BIT_9_DATA
		L_u16Data = (RXB8<<8);
	#endif

	L_u16Data = UDR;

	return L_u16Data;
}

/**********************************************************************************************************
 * Description : Interface Function to receive a string
 * Outputs     : the data received
 * Inputs      : string
 ***********************************************************************************************************/
void UART_vReceiveStringSync(u8 *A_str){
	for(u8 i=0; ; i++){
		A_str[i] = (u8)UART_u16ReceiveDataSync();
		if(A_str[i] == '\0')
			break;
	}
}

/**********************************************************************************************************
 * Description : Interface Function to Set the callback function for TXC (transmit complete)
 * Outputs     : void
 * Inputs      : the ISR function
 * NOTES	   : to enable using transmitting using interrupts, you must send a data
 ***********************************************************************************************************/
void UART_vSetCallBackTx(void (*ptr)(void)){
	G_TX_COMPLETE_PTR_Iv_Ov = ptr;
}

/**********************************************************************************************************
 * Description : Interface Function to Set the callback function for RXC (receive complete)
 * Outputs     : void
 * Inputs      : the ISR function
 ***********************************************************************************************************/
void UART_vSetCallBackRX(void (*ptr)(u16)){
	G_RX_COMPLETE_PTR_Iu16_Ov = ptr;
}

/**********************************************************************************************************
 * Description : Interface Function to Set the callback function for UDRE (USART data register empty)
 * Outputs     : void
 * Inputs      : the ISR function
 ***********************************************************************************************************/
void UART_vSetCallBackUDRE(void (*ptr)(void)){
	G_UDRE_PTR_Iv_Ov = ptr;
}


/**********************************************************************************************************
 * Description : Interface Function to Send data asynchronous using TXC flag
 * Outputs     : void
 * Inputs      : data
 ***********************************************************************************************************/
void UART_vSendCharAsync(u16 A_u16Data){
	/*Handle 9-bits character mode*/
	#if CHARACTER_SIZE == BIT_9_DATA
		if(A_u16Data & (1<<8)) {
			SET_BIT(UCSRB, TXB8);
		} else {
			CLR_BIT(UCSRB, TXB8);
		}
	#endif

	/*Sending the lower byte*/
	UDR = (u8)A_u16Data;
}


/*USART, RX Complete*/
void __vector_18(void) {
	if(G_RX_COMPLETE_PTR_Iu16_Ov != ADDRESS_NULL) {
		G_RX_COMPLETE_PTR_Iu16_Ov(UDR);
	}
}

/*USART Data Register Empty*/
void __vector_19(void){
	if(G_UDRE_PTR_Iv_Ov != ADDRESS_NULL) {
		G_UDRE_PTR_Iv_Ov();
	}
}

/*USART, TX Complete*/
void __vector_20(void){
	if(G_TX_COMPLETE_PTR_Iv_Ov != ADDRESS_NULL) {
		G_TX_COMPLETE_PTR_Iv_Ov();
	}
}
