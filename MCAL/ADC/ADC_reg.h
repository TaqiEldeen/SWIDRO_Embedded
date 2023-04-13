/*
 * ADC_reg.h
 *
 *  Created on: 31 Aug 2022
 *      Author: 20109
 */

#ifndef MCAL_ADC_ADC_REG_H_
#define MCAL_ADC_ADC_REG_H_

/*ADMUX register*/
#define ADMUX  *( (u8*) 0x7C)
/*pins*/
#define MUX0 0  /*Channel select*/
#define MUX1 1  /*Channel select*/
#define MUX2 2  /*Channel select*/
#define MUX3 3  /*Channel select*/
#define ADLAR 5 /*ADC left adjust result*/
#define REFS0 6 /*select ref*/
#define REFS1 7 /*select ref*/

/*ADCSRA*/
#define ADCSRA  *( (volatile u8*) 0x7A)
/*Pins*/
#define ADPS0 0  /*pre-scale select*/
#define ADPS1 1  /*pre-scale select*/
#define ADPS2 2  /*pre-scale select*/
#define ADIE  3  /*Enable ADC*/
#define ADIF  4 /*ADC flag*/
#define ADATE 5 /*ADC auto trigger enable*/
#define ADSC  6 /*ADC start conversion*/
#define ADEN  7 /*ADC enable*/

/*ADCH*/
#define ADCH  *( (volatile u8*) 0x79)
/*ADCL*/
#define ADCL  *( (volatile u8*) 0x78)
/*ADCW*/
#define ADCW  *( (volatile u16*) 0x78) /*used to read the 10 bits of the result*/

/*ADCSRB:  ADC Control and Status Register B*/
#define ADCSRB *( (u8*) 0x50)
/*BITS*/
#define ADTS0 0  /*Trigger source*/
#define ADTS1 1  /*Trigger source*/
#define ADTS2 2  /*Trigger source*/
#define ACME  6

#endif /* MCAL_ADC_ADC_REG_H_ */
