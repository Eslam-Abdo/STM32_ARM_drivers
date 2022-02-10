/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 19 NOV  2021                                                      */
/*********************************************************************************/

#ifndef AFIO_INTERFACE_H
#define AFIO_INTERFACE_H

#define SPI1_REMAP					 0
#define I2C1_REMAP 					 1
#define UART1_REMAP					 2
#define UART2_REMAP					 3
#define UART3_REMAP					 4
#define TIM1_REMAP					 6
#define TIM2_REMAP					 8
#define TIM3_REMAP					 10
#define TIM4_REMAP					 12
#define CAN_REMAP  					 13



/***************   Function definition    ******************/

void AFIO_voidSetEXTIConfiguration (uint8 Copy_u8EXTI_Line, uint8 Copy_u8PortMap);
void AFIO_voidRemapPeripheralPins (uint8 Copy_u8Port);

#endif // AFIO_INTERFACE_H
