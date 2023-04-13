/*
 * TIM1_reg.h
 *
 *  Created on: 3 Oct 2022
 *      Author: 20109
 */

#ifndef MCAL_TIM0_TIM0_REG_H_
#define MCAL_TIM0_TIM0_REG_H_

/**************   Timer1 Registers   **************/

/*Register TCCR1A*/
#define TCCR1A	 *((volatile u8*) 0x80)
/*Pins, pins 2,3 are reserved*/
#define WGM10	0
#define WGM11	1
#define COM1B0	4
#define COM1B1	5
#define COM1A0	6
#define COM1A1	7


/*Register TCCR1B*/
#define TCCR1B	 *((volatile u8*) 0x81)
/*Pins,, pin 5 is reserved*/
#define CS10	0
#define CS11	1
#define CS12	2
#define WGM12	3
#define WGM13	4
#define ICES1	6
#define ICNC1	7

/*Register TCCR1C*/
#define TCCR1C	 *((volatile u8*) 0x82)
/*Pins,, other pins are reserved*/
#define FOC1B	6
#define FOC1A	7


/*Register TCNT1H*/
#define TCNT1H	 *((volatile u8*) 0x85)

/*Register TCNT1L*/
#define TCNT1L	 *((volatile u8*) 0x84)

/* Register TCNT1W
 *--> Used to get the whole counting of the Timer1
 * */
#define TCNT1	*((volatile u16*) 0x84)


/*Register OCR1AH*/
#define OCR1AH *((volatile u8*) 0x89)

/*Register OCR1AL*/
#define OCR1AL *((volatile u8*) 0x88)

/*Register OCR1AW
 * --> Used to get the whole counting of the Timer1 OCR1
 */
#define OCR1A *((volatile u16*) 0x88)


/*Register OCR1BH*/
#define OCR1BH *((volatile u8*) 0x8B)

/*Register OCR1BL*/
#define OCR1BL *((volatile u8*) 0x8A)

/*Register OCR1BW
 * --> Used to get the whole counting of the Timer1 OCR1
 */
#define OCR1B *((volatile u16*) 0x8A)


/*Register ICR1H*/
#define ICR1H	*((volatile u8*) 0x87)

/*Register ICR1L*/
#define ICR1L	*((volatile u8*) 0x86)

/*Register ICR1
 * --> Used to get the whole counting of the Timer1 input capture
 */
#define ICR1	*((volatile u16*) 0x86)


/**************   Timer Interrupt states Registers   **************/


/*Register TIMSK1*/
#define TIMSK1	*((volatile u8*) 0x6F)

/*Bits: 3-4 & 6-7 are used in other peripherals*/
#define TOIE1  0
#define OCIE1A 1
#define OCIE1B 2
#define ICIE1  5


/*Register TIFR1*/
#define TIFR1  *((volatile u8*) 0x36)

/*Bits: 3-4 & 6-7 are used in other peripherals*/
#define TOV1  0
#define OCF1A 1
#define OCF1B 2
#define ICF1  5
#endif /* MCAL_TIM0_TIM0_REG_H_ */
