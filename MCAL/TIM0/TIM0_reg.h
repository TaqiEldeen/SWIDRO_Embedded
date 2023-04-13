/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: TIMER		**************/
/***********		Version: 1.02		 	**************/
/***********		Date: 13 Sep 2022	 	**************/
/***********		Updated: 17 Sep 2022	**************/
/*********************************************************/

#ifndef MCAL_TIM0_TIM0_REG_H_
#define MCAL_TIM0_TIM0_REG_H_

/**************   Timer0 Registers   **************/

/*Register TCCR0A*/
#define TCCR0A	 *((volatile u8*) 0x44)
/* BITS
 * NOTES:	Bits 3, 2 – Res: Reserved Bits
 * */
#define WGM00	0
#define WGM01	1
#define COM0B0	4
#define COM0B1	5
#define COM0A0	6
#define COM0A1	7

/*Register TCCR0B*/
#define TCCR0B	 *((volatile u8*) 0x45)
/* BITS
 * NOTES:	 Bits 5:4 – Res: Reserved Bits
 * */
#define CS00	0
#define CS01	1
#define CS02	2
#define WGM02	3
#define FOC0B	6
#define FOC0A	7


/*register TCNT0 timer counter*/
#define TCNT0	 *((volatile u8*) 0x46)	/* DONE */

/*Register OCR0A*/
#define OCR0A  *((volatile u8*) 0x47)	/* DONE */

/*Register OCR0B*/
#define OCR0B  *((volatile u8*) 0x48)	/* DONE */

/*Register TIMSK0*/
#define TIMSK0	*((volatile u8*) 0x6E)	/* DONE */

/*Bits: 2-7 are used by other timers*/
#define TOIE0   0
#define OCIE0A  1
#define OCIE0B  2

/*Register TIFR*/
#define TIFR0  *((volatile u8*) 0x35)	/* DONE */

/* Bits 7..3 – Res: Reserved Bits*/
#define TOV0   0
#define OCF0A  1
#define OCF0B  2


#endif /* MCAL_TIM0_TIM0_REG_H_ */
