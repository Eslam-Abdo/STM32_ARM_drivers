/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 19 NOV  2021                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "AFIO_interface.h"
#include "AFIO_config.h"
#include "AFIO_private.h"



/*************	 Function OF Set EXTI Configuration  **************************/

void AFIO_voidSetEXTIConfiguration (uint8 Copy_u8Line, uint8 Copy_u8PortMap)
{
	uint8 Local_u8RegIndex = 0;
	/* Assign to EXTICRx register */
	Local_u8RegIndex = Copy_u8Line / 4;
	Copy_u8Line = Copy_u8Line % 4 ;

	AFIO->EXTICR[Local_u8RegIndex] &= ~((0b1111) 		 << (Copy_u8Line * 4));
	AFIO->EXTICR[Local_u8RegIndex] |=  ((Copy_u8PortMap) << (Copy_u8Line * 4));
}

/*************	 Function OF remapping pins   **************************/

void AFIO_voidRemapPeripheralPins (uint8 Copy_u8Port)
{

	switch(Copy_u8Port){
		 case UART1_REMAP:
			SET_BIT(AFIO->MAPR, UART1_REMAP);
			break;
		case CAN_REMAP:
			/* CAN remap, use PB8, PB9 >> BITS 13,14   = 10*/
			CLR_BIT(AFIO->MAPR, CAN_REMAP); 	/* bit 13 */
			SET_BIT(AFIO->MAPR, (CAN_REMAP+1) ); /* bit 14 */
			break;
		case I2C1_REMAP:
			SET_BIT(AFIO->MAPR, I2C1_REMAP);
			break;
		case SPI1_REMAP:
			SET_BIT(AFIO->MAPR, SPI1_REMAP);
			break;
	}

}

