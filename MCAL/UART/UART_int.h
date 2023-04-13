/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: UART			**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 21 Sep 2022	 	**************/
/*********************************************************/

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_


/*Available baud rates, in 8MHZ FCPU*/
#define UART_8MHZ_BAUD_RATE_115200		3
#define UART_8MHZ_BAUD_RATE_57600		8
#define UART_8MHZ_BAUD_RATE_38400		12
#define UART_8MHZ_BAUD_RATE_19200		25
#define UART_8MHZ_BAUD_RATE_9600		51
#define UART_8MHZ_BAUD_RATE_4800		103
#define UART_8MHZ_BAUD_RATE_2400		207
#define UART_8MHZ_BAUD_RATE_1200		415	

/*Available baud rates, in 16MHZ FCPU*/
#define UART_16MHZ_BAUD_RATE_115200		8
#define UART_16MHZ_BAUD_RATE_57600		16
#define UART_16MHZ_BAUD_RATE_38400		25
#define UART_16MHZ_BAUD_RATE_19200		51
#define UART_16MHZ_BAUD_RATE_9600		103
#define UART_16MHZ_BAUD_RATE_4800		207
#define UART_16MHZ_BAUD_RATE_2400		416



/**********************************************************************************************************
 * Description : Interface Function to setup the UART based on the configuration
 * Outputs     : void
 * Inputs      : BaudRate
 * NOTES	   :the Global Interrupt Flag should be cleared (and interrupts globally-disabled)
 * 				when doing the initialization.
 ***********************************************************************************************************/
void UART_vInit(u16 A_u16BaudRate);


/**********************************************************************************************************
 * Description : Interface Function to send the data
 * Outputs     : void
 * Inputs      : Data
 ***********************************************************************************************************/
void UART_vSendCharSync(u16 A_u16Data);


/**********************************************************************************************************
 * Description : Interface Function to send the data
 * Outputs     : void
 * Inputs      : string data
 ***********************************************************************************************************/
void UART_vSendStringSync(u8 *A_u8Str);


/**********************************************************************************************************
 * Description : Interface Function to send the data
 * Outputs     : the data received
 * Inputs      : void
 ***********************************************************************************************************/
u16 UART_u16ReceiveDataSync();

/**********************************************************************************************************
 * Description : Interface Function to receive a string
 * Outputs     : the data received
 * Inputs      : string
 ***********************************************************************************************************/
void UART_vReceiveStringSync(u8 *A_str);


/**********************************************************************************************************
 * Description : Interface Function to Set the callback function for TXC (transmit complete)
 * Outputs     : void
 * Inputs      : the ISR function
 * NOTES	   : to enable using transmitting using interrupts, you must send a data
 ***********************************************************************************************************/
void UART_vSetCallBackTx(void (*ptr)(void));

/**********************************************************************************************************
 * Description : Interface Function to Set the callback function for RXC (receive complete)
 * Outputs     : void
 * Inputs      : the ISR function
 ***********************************************************************************************************/
void UART_vSetCallBackRX(void (*ptr)(u16));

/**********************************************************************************************************
 * Description : Interface Function to Set the callback function for UDRE (USART data register empty)
 * Outputs     : void
 * Inputs      : the ISR function
 ***********************************************************************************************************/
void UART_vSetCallBackUDRE(void (*ptr)(void));

/**********************************************************************************************************
 * Description : Interface Function to Send data asynchronous using TXC flag
 * Outputs     : void
 * Inputs      : data
 ***********************************************************************************************************/
void UART_vSendCharAsync(u16 A_u16Data);


#endif /* MCAL_UART_UART_INT_H_ */
