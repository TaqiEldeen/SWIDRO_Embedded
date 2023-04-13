/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: UART			**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 21 Sep 2022	 	**************/
/*********************************************************/

#ifndef MCAL_UART_UART_CFG_H_
#define MCAL_UART_UART_CFG_H_

/* Interrupt settings
 *
 * Options:
 * 1- INT_ENABLE
 * 2- INT_DISABLE
 * */
#define RX_COMPLETE_INTERRUPT	INT_ENABLE
#define TX_COMPLETE_INTERRUPT	INT_DISABLE
#define UDR_EMPTY_INTERRUPT		INT_DISABLE


/* Receiver & transmitter settings
 *
 * Options:
 * 1- ENABLE
 * 2- DISABLE
 * */
#define RECEIVER_STATUS		ENABLE
#define TRANSMITTER_STATUS	ENABLE

/* USART MODE
 *
 * Options:
 * 1- ASYNC_MODE
 * 2- SYNC_MODE
 * */
#define USART_MODE			ASYNC_MODE

/* Parity Mode
 *
 * Options:
 * 1- PARITY_DISABLE
 * 2- PARITY_EVEN
 * 3- PARITY_ODD
 * */
#define PARITY_MODE			PARITY_DISABLE

/* Stop bits select
 *
 * Options:
 * 1- ONE_STOP_BIT
 * 2- TWO_STOP_BITS
 * */
#define STOP_BIT_SELECT		ONE_STOP_BIT

/* Character size
 *
 * Options:
 * 1- BIT_5_DATA
 * 2- BIT_6_DATA
 * 3- BIT_7_DATA
 * 4- BIT_8_DATA
 * 5- BIT_9_DATA
 * */
#define CHARACTER_SIZE		BIT_8_DATA

/* Clock Polarity (ONLY IN SYNC MODE)
 *
 * Options:
 * 1- RISING_XCK_EDGE
 * 2- FALLING_XCK_EDGE
 * */
#define CLK_POLARITY	RISING_XCK_EDGE


#define TX_PORT		PORTD_ID
#define TX_PIN		PIN1_ID

#define RX_PORT     PORTD_ID
#define RX_PIN      PIN0_ID

#endif /* MCAL_UART_UART_CFG_H_ */
