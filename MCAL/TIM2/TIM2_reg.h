/*
 * TIM0_reg.h
 *
 *  Created on: 3 Oct 2022
 *      Author: 20109
 */

#ifndef MCAL_TIM2_TIM2_REG_H_
#define MCAL_TIM2_TIM2_REG_H_

/**************   Timer2 Registers   **************/

/*Register TCCR2A*/
#define TCCR2A	 *((volatile u8*) 0xB0)		/* DONE */
/* BITS
 * NOTES:	Bits 3, 2 – Res: Reserved Bits
 * */
#define WGM20	0
#define WGM21	1
#define COM2B0	4
#define COM2B1	5
#define COM2A0	6
#define COM2A1	7

/*Register TCCR2B*/
#define TCCR2B	 *((volatile u8*) 0xB1)		/* DONE */
/* BITS
 * NOTES:	 Bits 5:4 – Res: Reserved Bits
 * */
#define CS20	0
#define CS21	1
#define CS22	2
#define WGM22	3
#define FOC2B	6
#define FOC2A	7


/*register TCNT2 timer counter*/
#define TCNT2	 *((volatile u8*) 0xB2)	/* DONE */

/*Register OCR2A*/
#define OCR2A  *((volatile u8*) 0xB3)	/* DONE */

/*Register OCR0B*/
#define OCR2B  *((volatile u8*) 0xB4)	/* DONE */

/*Register TIMSK0*/
#define TIMSK2	*((volatile u8*) 0x70)	/* DONE */

/*Bits: 2-7 are used by other timers*/
#define TOIE2   0
#define OCIE2A  1
#define OCIE2B  2

/*Register TIFR*/
#define TIFR2  *((volatile u8*) 0x37)	/* DONE */

/* Bits 7..3 – Res: Reserved Bits*/
#define TOV2   0
#define OCF2A  1
#define OCF2B  2

#endif /* MCAL_TIM2_TIM2_REG_H_ */
