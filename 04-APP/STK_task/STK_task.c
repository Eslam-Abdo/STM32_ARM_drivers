/*
/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT 2020                                                       */
/*********************************************************************************/

/******************** 			 STK 		   ***********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"

void ping_pong(void);
void fat7y_yawarda(void);
void flashing(void);


void main(void)
{
	/* Initialize Clock System  */
	RCC_voidInitSysClock();
	/* Enable GPIOA Clock */
	RCC_voidEnableClock(RCC_APB2,2);
	/* set pin from 0 to 7 as output_pp */
	GPIO_voidSetPinDirection(GPIOA, PIN0, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(GPIOA, PIN1, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(GPIOA, PIN2, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(GPIOA, PIN3, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(GPIOA, PIN4, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(GPIOA, PIN5, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(GPIOA, PIN6, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(GPIOA, PIN7, OUTPUT_SPEED_10MHZ_PP);

	/* */

	while(1)
	{

		for (uint8 y=0; y<16; y++)
		{
			if (y<4)
			{
				ping_pong();
			}
			else if (y<8)
			{
				fat7y_yawarda();
			}
			else
			{
				flashing();
			}
		}

	}

}

void ping_pong(void)
{
	for (uint8 i=0; i<16; i++)
	{
		if (i<8)
		{
			GPIO_voidSetPinValue(GPIOA, i, HIGH);
			STK_voidDelay_ms(200);
			GPIO_voidSetPinValue(GPIOA, i, LOW);
		}
		else if (i>=8)
		{
			GPIO_voidSetPinValue(GPIOA, (15-i), HIGH);
			STK_voidDelay_ms(200);
			GPIO_voidSetPinValue(GPIOA, (15-i), LOW);
		}
	}
}

void fat7y_yawarda(void)
{
	for (uint8 z=0; z<2; z++)
	{
		if (z == 0)
		{
			for (uint8 i=0; i<=3; i++)
			{
				GPIO_voidSetPinValue(GPIOA, (3-i), HIGH);
				GPIO_voidSetPinValue(GPIOA, (4+i), HIGH);

				STK_voidDelay_ms(200);
			}
		}
		else
		{
			for (uint8 i=0,x=7; i<=3,x>=4; i++,x--)
			{
				GPIO_voidSetPinValue(GPIOA, i, LOW);
				GPIO_voidSetPinValue(GPIOA, x, LOW);
				STK_voidDelay_ms(200);
			}
		}
	}
}

void flashing(void)
{
	for (uint8 z=0; z<=1; z++)
	{
		for (uint8 i=0; i<=7; i++)
		{
			GPIO_voidSetPinValue(GPIOA, i, 1-z);
		}
		STK_voidDelay_ms(500);
	}
}
