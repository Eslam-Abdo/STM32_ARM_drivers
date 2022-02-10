/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 23 SEP 2020                                                       */
/*********************************************************************************/

/******************** 			 BLINK 		   ***********************************/
#include "STD_TYPEs.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"

#define GPIOA_CRL		*((uint32*)0x40010800)
#define GPIOA_ODR		*((uint32*)0x4001080C)

void main(void)
{
	/* Initialize clock system */
	RCC_voidInitSysClock();
	/* Enable GPIOA clock (Peripheral 2 on APB2 bus)  */
	RCC_voidEnableClock(RCC_APB2,2);
	/* configure A0 as output push pull */
	GPIOA_CRL = 0x00000002;
	/* Set A0 output high */
	GPIOA_ODR = 0x00000001;


	while(1)
	{

	}
}



