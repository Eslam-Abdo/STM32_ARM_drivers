/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 25 SEP 2020                                                       */
/*********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "7_SEG_interface.h"
#include "7_SEG_config.h"
#include "7_SEG_private.h"


void _7_SEG_voidInit(uint8 Copy_u8Port)
{
	GPIO_voidSetPinDirection(Copy_u8Port, PIN0, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(Copy_u8Port, PIN1, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(Copy_u8Port, PIN2, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(Copy_u8Port, PIN3, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(Copy_u8Port, PIN4, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(Copy_u8Port, PIN5, OUTPUT_SPEED_10MHZ_PP);
	GPIO_voidSetPinDirection(Copy_u8Port, PIN6, OUTPUT_SPEED_10MHZ_PP);

}

/**********   Copy_u8Port       : select  port GPIOA or GPIOB
              Copy_u8CommonType : select 7-SEG type COMMON_CATHODE or COMMON_ANODE
              Copy_u8DisplayNum : display number from 0 to 9

    NOTE:   if need you change pins number check "7_SEG_config.h"
                                                                    **************/
void _7_SEG_voidDisplay(uint8 Copy_u8Port, uint8 Copy_u8DisplayNum)
{
    switch(Copy_u8DisplayNum)
    {
        case 0:
            /******************      _
                                    | |
                                    |_|      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_LOW);
            break;

        case 1:
            /******************
                                     |
                                     |      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_LOW);
            break;

        case 2:
            /******************      _
                                     _|
                                    |_      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_HIGH);
            break;

        case 3:
            /******************      _
                                     _|
                                     _|      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_HIGH);
            break;

        case 4:
            /******************
                                    |_|
                                      |      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_HIGH);
            break;

        case 5:
            /******************      _
                                    |_
                                     _|      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_HIGH);
            break;

        case 6:
            /******************      _
                                    |_
                                    |_|      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_HIGH);
            break;

        case 7:
            /******************     _
                                     |
                                     |      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_LOW);
            break;

        case 8:
            /******************      _
                                    |_|
                                    |_|      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_HIGH);
            break;
        case 9:
            /******************      _
                                    |_|
                                     _|      ****************/
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN0, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN1, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN2, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN3, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN4, SEVEN_SEG_LOW);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN5, SEVEN_SEG_HIGH);
            GPIO_voidSetPinValue(Copy_u8Port, SEVEN_SEG_PIN6, SEVEN_SEG_HIGH);
            break;
        default :   break;
    }
}

