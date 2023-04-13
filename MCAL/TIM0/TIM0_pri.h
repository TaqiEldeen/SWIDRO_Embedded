/*********************************************************/
/***********		Author: TaqiEldeen	 	**************/
/***********		Layer: MCAL			 	**************/
/***********		Component: TIMER		**************/
/***********		Version: 1.02		 	**************/
/***********		Date: 13 Sep 2022	 	**************/
/***********		Updated: 17 Sep 2022	**************/
/*********************************************************/

#ifndef MCAL_TIM0_TIM0_PRI_H_
#define MCAL_TIM0_TIM0_PRI_H_

/**************   TIMER0_private   **************/


/* Available WaveForm Generation modes for timer0 */
#define TIMER0_WGM_NORMAL_MODE 		   		0
#define TIMER0_WGM_PWM_PHASE_CORRECT_MODE 	1
#define TIMER0_WGM_CTC_MODE			   		2
#define TIMER0_WGM_FAST_PWM_MODE          	3
/*Mask for the  waveForm Generation modes*/
#define TIMER0_WGM_MASK        				0b11111100


/*Available Compare output modes for timer0*/
#define TIMER0_OC0_DISCONNECT	0b00000000
#define TIMER0_TOG_OC0     		0b00010000
#define TIMER0_CLR_OC0     		0b00100000
#define TIMER0_SET_OC0 	 		0b00110000
/*Mask for the Compare output mode*/
#define TIMER0_COM0A0_MASK		0b11001111
#define TIMER0_COM0A1_MASK		0b00111111


/*Available Clock sources/prescaling for timer0*/
#define TIMER0_PRESCALER_NO_CLK 		0b00000000
#define TIMER0_PRESCALER_NO_PRESCALE    0b00000001
#define TIMER0_PRESCALER_8				0b00000010
#define TIMER0_PRESCALER_64				0b00000011
#define TIMER0_PRESCALER_256			0b00000100
#define TIMER0_PRESCALER_1024			0b00000101
#define TIMER0_EXT_CLK_FALLING_EDGE		0b00000110
#define TIMER0_EXT_CLK_RISING_EDGE      0b00000111
/*Mask for Clock source*/
#define TIMER0_CLK_SELECT_MASK			0b11111000


/**************   TIMER0 MAX COUNT   **************/
#define TIMER0_MAX_COUNT (u16) 255


/**************   TIMER STATES   **************/
#define TIMER_ENABLE 	0
#define TIMER_DISABLE	1


/**************   TIMER PWM   **************/
#define PWM_NON_INVERTING	2
#define PWM_INVERTING		3
#define PWM_OFF				0


/**************   TIMER INT state   **************/
#define INT_ENABLE 	0
#define INT_DISABLE 1


/**************   TIMER ISRs  **************/
void __vector_14(void)__attribute__((signal)); /*TIMER0 COMPA*/
void __vector_15(void)__attribute__((signal)); /*TIMER0 COMPB*/
void __vector_16(void)__attribute__((signal)); /*TIMER0 OVF*/


/**************   TIMER0 POINTER TO FUNCTION  **************/
void (*G_PTRF_TIM0_OVF)(void) = ADDRESS_NULL;
void (*G_PTRF_TIM0_CTC_OCF0B)(void) = ADDRESS_NULL;
void (*G_PTRF_TIM0_CTC_OCF0A)(void) = ADDRESS_NULL;

/**************   TIMER0 GLOBAL Functions  **************/
static void TIM0_vSetupCTC		();
static void TIM0_vSetupFastPWM	();
static void TIM0_vSetupPhaseCorrectPWM	();


/**************   TIMER0 GLOBAL VARIABLES  **************/
u16 G_u16Timer0_Cov = 0;
u8 G_u8Timer0_Preload_Val = 0;
u8 G_u8Timer0_OcrVal = 0;

#endif /* MCAL_TIM0_TIM0_PRI_H_ */
