/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 25 SEP 2020                                                       */
/*********************************************************************************/
#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H



/***************   Function definition    ******************/
void LED_voidLed_ON      (uint8 Copy_u8Port, uint8 Copy_u8Pin);
void LED_voidLed_OFF     (uint8 Copy_u8Port, uint8 Copy_u8Pin);
void LED_voidLed_Toggle  (uint8 Copy_u8Port, uint8 Copy_u8Pin);

#endif // LED_INTERFACE_H
