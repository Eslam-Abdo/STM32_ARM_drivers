/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 19 NOV 2021                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"



/* define Callback Global variable (pointer to function) */
static void (*EXTI_CallBack[16]) (void);

/*************	 Function OF Initialize EXTI  **************************/

void EXTI_voidInit (uint8 Copy_u8EXTILine, uint8 Copy_u8EXTISenseMode)
{
	switch(Copy_u8EXTISenseMode)
	{
		case RISING_EDGE	:	 SET_BIT(EXTI -> RTSR, Copy_u8EXTILine);	 	break;
		case FALLING_EDGE	:	 SET_BIT(EXTI -> FTSR, Copy_u8EXTILine);	 	break;
		case ON_CHANGE  	:	 SET_BIT(EXTI -> RTSR, Copy_u8EXTILine);
												 SET_BIT(EXTI -> FTSR, Copy_u8EXTILine);	 	break;
		default:							break;
	}
	SET_BIT(EXTI->IMR , Copy_u8EXTILine);
}

/*************	 Function OF Enable EXTI  ***************************/

void EXTI_voidEnableEXTI(uint8 Copy_u8EXTILine)
{
	SET_BIT(EXTI->IMR , Copy_u8EXTILine);
}

/*************	 Function OF Disable EXTI  **************************/

void EXTI_voidDisableEXTI(uint8 Copy_u8EXTILine)
{
	CLR_BIT(EXTI->IMR , Copy_u8EXTILine);
}

/*************	 Function OF SoftWare Trigger  **********************/

void EXTI_voidSoftWareTrigger(uint8 Copy_u8EXTILine)
{
	SET_BIT(EXTI->SWIER , Copy_u8EXTILine);
}

/*************	 Function OF Set CallBack  **********************/

void EXTI_voidSetCallBack (uint8 Copy_u8EXTILine,void (*ptr) (void))
{
	EXTI_CallBack[Copy_u8EXTILine] = ptr;
}

/*************	 Function OF EXTIx_ISQHandler Interrupt  **************************/
/* This is function call a EXTI_CallBack() function to do when interrupt */

void EXTI0_IRQHandler (void)
{
	EXTI_CallBack[EXTI_LINE0]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , EXTI_LINE0);

}
void EXTI1_IRQHandler (void)
{
	EXTI_CallBack[EXTI_LINE1]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , EXTI_LINE1);

}
void EXTI2_IRQHandler (void)
{
	EXTI_CallBack[EXTI_LINE2]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , EXTI_LINE2);

}
void EXTI3_IRQHandler (void)
{
	EXTI_CallBack[EXTI_LINE3]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , EXTI_LINE3);

}
void EXTI4_IRQHandler (void)
{
	EXTI_CallBack[EXTI_LINE4]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI->PR , EXTI_LINE4);

}
void EXTI9_5_IRQHandler (void)
{
	uint8 Local_ExtiDetect=0;
	for(uint8 local_i=EXTI_LINE5; local_i<=EXTI_LINE9; local_i++)
	{
		Local_ExtiDetect = GET_BIT(EXTI->PR,local_i);
		if(Local_ExtiDetect == 1)
		{
			EXTI_CallBack[local_i]();
		}
		Local_ExtiDetect=0;
	}
	EXTI->PR |= 0x03E0; /* clear interrupt pending flag 5~9 */

}
void EXTI15_10_IRQHandler (void)
{
	uint8 Local_ExtiDetect=0;
		for(uint8 local_i=EXTI_LINE10; local_i<=EXTI_LINE15; local_i++)
		{
			Local_ExtiDetect = GET_BIT(EXTI->PR,local_i);
			if(Local_ExtiDetect == 1)
			{
				EXTI_CallBack[local_i]();

			}
			Local_ExtiDetect=0;
		}
	EXTI->PR |= 0xFC00; /* clear interrupt pending flag 10~15 */

}
