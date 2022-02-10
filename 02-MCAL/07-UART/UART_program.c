/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 Jan  2021                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_config.h"
#include "UART_private.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

void printMsg_init(void )
{
	/* AFIO Enable RCC */
	RCC_voidEnableClock(RCC_APB2,0);
	/* GPIOA Enable RCC */
	 RCC_voidEnableClock(RCC_APB2,2);
	/* UASRT Enable RCC */
	RCC_voidEnableClock(RCC_APB2,14);
	/* PA9 : USART1_TX  */
	/* PA10 : USART1_RX */
	/* pin configurations:
				PA9- TX is set to OUTPUT ALternate-push-pull and 50MHz
				PA10- RX is set to INPUT Floating (defult state)*/
	GPIO_voidSetPinDirection(GPIOA, PIN9, OUTPUT_SPEED_50MHZ_AFPP);
	//GPIO_voidSetPinDirection(GPIOA, PIN10, INPUT_FLOATING);
	/* set BAUDRATEvalue */
	UART->BRR = BAUDRATE;
	/*  UART enable */
	SET_BIT(UART->CR1,13);
	/*  TX enable */
	SET_BIT(UART->CR1,3);
	/*  RX enable */
	//SET_BIT(UART->CR1,2);

}
void printMsg(uint8 *msg)
{
	u8 LOC_u8Iterator = 0;
	while(msg[LOC_u8Iterator] != '\0')
	{
		UART->DR = msg[LOC_u8Iterator];
		while( GET_BIT(UART->SR,6) == 0);
		CLR_BIT(UART->SR,6);
		LOC_u8Iterator++;
	}
}

