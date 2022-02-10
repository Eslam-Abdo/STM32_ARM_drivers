/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 25 SEP 2020                                                       */
/*********************************************************************************/

#ifndef _7_SEG_INTERFACE_H
#define _7_SEG_INTERFACE_H

/***************   Common Type definition         *******************/

#define COMMON_ANODE        0
#define COMMON_CATHODE      1


/***************   Function definition    ******************/

void _7_SEG_voidInit	(uint8 Copy_u8Port);
void _7_SEG_voidDisplay (uint8 Copy_u8Port, uint8 Copy_u8DisplayNum);

#endif // _7_SEG_INTERFACE_H
