/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 19 NOV 2021                                                       */
/*********************************************************************************/
#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H


/*******************   LINE Definition     ***************************/

#define EXTI_LINE0				0
#define EXTI_LINE1				1
#define EXTI_LINE2				2
#define EXTI_LINE3				3
#define EXTI_LINE4				4
#define EXTI_LINE5				5
#define EXTI_LINE6				6
#define EXTI_LINE7				7
#define EXTI_LINE8				8
#define EXTI_LINE9				9
#define EXTI_LINE10				10
#define EXTI_LINE11				11
#define EXTI_LINE12				12
#define EXTI_LINE13				13
#define EXTI_LINE14				14
#define EXTI_LINE15				15

/*******************   MODE Definition     ***************************/

#define RISING_EDGE				0
#define FALLING_EDGE			1
#define ON_CHANGE				2

/***************   Function definition    ******************/

void EXTI_voidInit   	 		 (uint8 Copy_u8EXTILine, uint8 Copy_u8EXTISenseMode);
void EXTI_voidEnableEXTI 		 (uint8 Copy_u8EXTILine);
void EXTI_voidDisableEXTI 		 (uint8 Copy_u8EXTILine);
void EXTI_voidSoftWareTrigger	 (uint8 Copy_u8EXTILine);

void EXTI_voidSetCallBack (uint8 Copy_u8EXTILine, void (*ptr) (void));

#endif // EXTI_INTERFACE_H
