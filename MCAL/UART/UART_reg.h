/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: UART			**************/
/***********		Version: 1.00		 	**************/
/***********		Date: 21 Sep 2022	 	**************/
/*********************************************************/

#ifndef MCAL_UART_UART_REG_H_
#define MCAL_UART_UART_REG_H_


/*USART I/O Data Register*/
#define UDR		*((volatile u8*) 0xC6)

/*USART Control and Status Register A*/
#define UCSRA	*((volatile u8*) 0xC0)
/*Pins*/
#define MPCM 	0 /*Multi-processor Communication Mode*/
#define U2X		1 /*Double the USART Transmission Speed*/
#define PE		2 /*Parity Error*/
#define DOR		3 /*Data OverRun*/
#define FE		4 /*Frame Error*/
#define UDRE	5 /*USART Data Register Empty*/
#define TXC		6 /*USART Transmit Complete*/
#define RXC		7 /*USART Receive Complete*/


/*USART Control and Status Register B */
#define UCSRB	*((volatile u8*) 0xC1)
/*Pins*/
#define TXB8	0 /*Transmit Data Bit 8*/
#define RXB8	1 /*Receive Data Bit 8*/
#define UCSZ2	2 /*Character Size*/
#define TXEN	3 /*Transmitter Enable*/
#define RXEN	4 /*Receiver Enable*/
#define UDRIE	5 /*USART Data Register Empty Interrupt Enable*/
#define TXCIE	6 /*TX Complete Interrupt Enable*/
#define RXCIE	7 /*RX Complete Interrupt Enable*/


/*USART Control and Status Register C */
#define UCSRC	*((volatile u8*) 0xC2)
/*Pins*/
#define UCPOL	0 /*Clock Polarity*/
#define UCSZ0	1 /*Character Size*/
#define UCSZ1	2 /*Character Size*/
#define USBS	3 /*Stop Bit Select*/
#define UPM0	4 /*Parity Mode*/
#define UPM1	5 /*Parity Mode*/
#define UMSEL	6 /*USART Mode Select*/
#define URSEL	7 /*Register Select*/



/*USART Baud Rate Registers*/
#define UBRRH	*((volatile u8*) 0xC5)

/*Pins: 6,5,4 are reserved. 0,1,2,3 are used by UBBR*/
#define URSEL	7 /*Register Select*/

#define UBRRL	*((volatile u8*) 0xC4)


#endif /* MCAL_UART_UART_REG_H_ */
