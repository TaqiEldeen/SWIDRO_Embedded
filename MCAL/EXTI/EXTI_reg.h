/*
 * EXTI_reg.h
 *
 *  Created on: 29 Aug 2022
 *      Author: 20109
 */

#ifndef MCAL_EXTI_EXTI_REG_H_
#define MCAL_EXTI_EXTI_REG_H_


/* External Interrupt Control Register A */
#define EICRA 	*((volatile u8*) 0x69)

#define ISC11	3
#define ISC10	2
#define ISC01	1
#define ISC00	0


/* External Interrupt Mask Register
 *
 * NOTES:  Bit 7..4 – Res: Reserved Bits
 *
 *  */
#define EIMSK	*((volatile u8*) 0x3D)

#define INT1	1
#define INT0	0


/* External Interrupt Flag Register
 *
 * NOTES:  Bit 7..2 – Res: Reserved Bits
 *
 *  */
#define EIFR	*((volatile u8*) 0x3C)

#define INTF1	1
#define INTF0	0


/* External Interrupt Flag Register
 *
 * NOTES: Bit 7..3 - Res: Reserved Bits
 *
 *  */
#define PCICR	*((volatile u8*) 0x68)

#define PCIE2	2
#define PCIE1	1
#define PCIE0	0


/* Pin Change Interrupt Flag Register
 *
 * NOTES: Bit 7..3 - Res: Reserved Bits
 *
 *  */
#define PCIFR	*((volatile u8*) 0x3B)

#define PCIF2	2
#define PCIF1	1
#define PCIF0	0


/* PIN CHANGE IS NOT EMBLEMENTED !*/


#endif /* MCAL_EXTI_EXTI_REG_H_ */
