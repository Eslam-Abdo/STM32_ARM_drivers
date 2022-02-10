/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 5 OCT  2020                                                       */
/*********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "7_SEG_interface.h"
#include "LED_interface.h"

#define delays   for (int i=0; i<=100; i++) // for deposing in button
#define delay    for (int i=0; i<=500000; i++)
int main(void)
{
	/* Initialize Clock System  */
	RCC_voidInitSysClock();
	/* Enable GPIOA Clock */
	RCC_voidEnableClock(RCC_APB2,2);
	/* Enable GPIOB Clock */
	RCC_voidEnableClock(RCC_APB2,3);
	/* Enable GPIOC Clock */
	RCC_voidEnableClock(RCC_APB2,4);

	/* PIN0 PORT-B INPUT PULL UP */
	GPIO_voidSetPinDirection(GPIOB, PIN0, INPUT_PULL_UP_DOWN);
	GPIO_voidSetPinPull(GPIOB, PIN0, PULL_UP);
	/* led on stm board */
	GPIO_voidSetPinDirection(GPIOC, PIN13, OUTPUT_SPEED_10MHZ_PP);
	/* 7-segmant initialize pins */
	_7_SEG_voidInit(GPIOA);

	uint8 NumDisplay = 0,flag = 0, ButtonValue;
	/* display 0 on 7-SEG */
	_7_SEG_voidDisplay(GPIOA,NumDisplay);

	while(1)
	{

		ButtonValue = GPIO_u8GetPinValue(GPIOB,PIN0); // get value
		if ((ButtonValue == 0) && (flag == 0))
		{	// deposing
			delays;
			if ((ButtonValue == 0) && (flag == 0))
			{
				NumDisplay ++;
				if(NumDisplay >= 10)
				{
					NumDisplay = 0;
				}
				_7_SEG_voidDisplay(GPIOA,NumDisplay);

				flag = 1;
			}
		}
		else if ((ButtonValue == 1) && (flag == 1))
		{
			LED_voidLed_Toggle(GPIOC, PIN13);
			flag = 0;
		}
	}
	return 0;
}



