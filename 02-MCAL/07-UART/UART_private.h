/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 11 OCT  2020                                                      */
/*********************************************************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


/*******************   Register Definition     ***********************/

typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}UART_t;

#define UART 		((volatile UART_t *) 0x40010000)

/***********************  USART BAUDRATE **************************/
#define UART1_BAUDRATE_9600         0x1D4C //for 72MHZ on APB2 bus
#define UART1_BAUDRATE_115200       0x271 //for 72MHZ on APB2 bus

#endif // UART_PRIVATE_H
