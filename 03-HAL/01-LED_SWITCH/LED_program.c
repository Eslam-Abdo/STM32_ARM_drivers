/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 25 SEP 2020                                                       */
/*********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "LED_interface.h"
#include "LED_config.h"
#include "LED_private.h"

/*******************      TURN LED ON      *****************/

void LED_voidLed_ON (uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
    GPIO_voidSetPinValue (Copy_u8Port, Copy_u8Pin, HIGH);
}

/*******************      TURN LED OFF      *****************/
void LED_voidLed_OFF     (uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
    GPIO_voidSetPinValue (Copy_u8Port, Copy_u8Pin, LOW);
}

/*******************      TOGGELE LED       *****************/
void LED_voidLed_Toggle  (uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
    GPIO_voidTogglePinValue (Copy_u8Port, Copy_u8Pin);
}
