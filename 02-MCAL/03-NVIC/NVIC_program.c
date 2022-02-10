/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 19 NOV 2021                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "NVIC_interface.h"
#include "NVIC_config.h"
#include "NVIC_private.h"


/*************	 Function OF Enable Interrupt  **************************/

void NVIC_voidEnableInterrupt(IRQn_Type IRQn)
{
	if (IRQn <= 31 )
	{
		SET_BIT(NVIC->ISER[0] , IRQn);
	}
	else if (IRQn <= 59)
	{
		IRQn -= 32;
		SET_BIT(NVIC->ISER[1] , IRQn);
	}
	else
	{
		/* Return error */
	}
}

/*************	 Function OF Disable Interrupt  *************************/

void NVIC_voidDisableInterrupt(IRQn_Type IRQn)
{
	if (IRQn <= 31 )
	{
		SET_BIT(NVIC->ICER[0] , IRQn);
	}
	else if (IRQn <= 59)
	{
		IRQn -= 32;
		SET_BIT(NVIC->ICER[1] , IRQn);
	}
	else
	{
		/* Return error */
	}
}

/*************	 Function OF Set Pending Flag  **************************/

void NVIC_voidSetPendingFlag(IRQn_Type IRQn)
{
	if (IRQn <= 31 )
	{
		SET_BIT(NVIC->ISPR[0] , IRQn);
	}
	else if (IRQn <= 59)
	{
		IRQn -= 32;
		SET_BIT(NVIC->ISPR[1] , IRQn);
	}
	else
	{
		/* Return error */
	}
}

/*************	 Function OF Clear Pending Flag  *************************/

void NVIC_voidClearPendingFlag(IRQn_Type IRQn)
{
	if (IRQn <= 31 )
	{
		SET_BIT(NVIC->ICPR[0] , IRQn);
	}
	else if (IRQn <= 59)
	{
		IRQn -= 32;
		SET_BIT(NVIC->ICPR[1] , IRQn);
	}
	else
	{
		/* Return error */
	}
}

/*************	 Function OF Get Active Flag  *************************/

uint8 NVIC_u8GetActiveFlag(IRQn_Type IRQn)
{
	uint8 Local_u8Result;
	if (IRQn <= 31 )
	{
		Local_u8Result = GET_BIT(NVIC->IABR[0], IRQn);
	}
	else if (IRQn <= 59)
	{
		IRQn -= 32;
		Local_u8Result = GET_BIT(NVIC->IABR[1], IRQn);
	}
	else
	{
		/* Return error */
	}
	return Local_u8Result;
}

/*************	 Function OF Set Priority  *************************/

void  NVIC_voidSetPrioity(IRQn_Type IRQn, uint8 Copy_u8GroupPriority, uint8 Copy_u8SubPriority, uint32 Copy_u8Group)
{
					  /* EX: 0x05FA0400 3 Group & 1 sub priority */ 
					  /* 0x100 Hex  ---> 256 Decimal			 */
	uint8 Local_u8Priority = Copy_u8SubPriority | (Copy_u8GroupPriority << ((Copy_u8Group - 0x05FA0300)/256));

	/* external peripheral		*/ /*EXTI0 = 6*/
	if (IRQn < 60 )
	{
		NVIC->IP[IRQn] = Local_u8Priority << 4;
	}
	else
	{
		/* Report Error */
	}
	
	SCB->AIRCR = Copy_u8Group;
}


