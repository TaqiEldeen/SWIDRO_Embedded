/*
 * DIO_reg.h
 *
 *  Created on: 19 Aug 2022
 *      Author: 20109
 */

#ifndef MCAL_DIO_DIO_REG_H_
#define MCAL_DIO_DIO_REG_H_


/*PORTB*/
#define PORTB *( (volatile u8 *) 0x25)
#define DDRB  *( (volatile u8 *) 0x24)
#define PINB  *( (volatile u8 *) 0x23)

/*PORTC*/
#define PORTC *( (volatile u8 *) 0x28)
#define DDRC  *( (volatile u8 *) 0x27)
#define PINC  *( (volatile u8 *) 0x26)

/*PORTD*/
#define PORTD *( (volatile u8 *) 0x2B)
#define DDRD  *( (volatile u8 *) 0x2A)
#define PIND  *( (volatile u8 *) 0x29)


#endif /* MCAL_DIO_DIO_REG_H_ */
