/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 17 NOV 2021                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_private.h"
#include "GPIO_config.h"


/************* Function OF Set Pin Direction *************************/

void  GPIO_voidSetPinDirection (uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Mode)
{
    switch (Copy_u8Port)
    {
         /*** PORT A ***/

        case GPIOA:
            if (Copy_u8Pin <= 7)
            {//LOW
                GPIO_A->CRL &= ~((0b1111)      << (Copy_u8Pin * 4));
                GPIO_A->CRL |=  ((Copy_u8Mode) << (Copy_u8Pin * 4));
            }
            else if (Copy_u8Pin <= 15)
            {//HIGH
                GPIO_A->CRH &= ~((0b1111)      << ((Copy_u8Pin - 8) * 4));
                GPIO_A->CRH |=  ((Copy_u8Mode) << ((Copy_u8Pin - 8) * 4));
            }
            break;

        /*** PORT B ***/

        case GPIOB:
            if (Copy_u8Pin <= 7)
            {//LOW
                GPIO_B->CRL &= ~((0b1111)      << (Copy_u8Pin * 4));
                GPIO_B->CRL |=  ((Copy_u8Mode) << (Copy_u8Pin * 4));
            }
            else if (Copy_u8Pin <= 15)
            {//HIGH
                GPIO_B->CRH &= ~((0b1111)      << ((Copy_u8Pin - 8) * 4));
                GPIO_B->CRH |=  ((Copy_u8Mode) << ((Copy_u8Pin - 8) * 4));
            }
            break;

        /*** PORT C ***/

        case GPIOC:
            if (Copy_u8Pin <= 7)
            {//LOW
                GPIO_C->CRL &= ~((0b1111)      << (Copy_u8Pin * 4));
                GPIO_C->CRL |=  ((Copy_u8Mode) << (Copy_u8Pin * 4));
            }
            else if (Copy_u8Pin <= 15)
            {//HIGH
                GPIO_C->CRH &= ~((0b1111)      << ((Copy_u8Pin - 8) * 4));
                GPIO_C->CRH |=  ((Copy_u8Mode) << ((Copy_u8Pin - 8) * 4));
            }
            break;
        default:       break;
    }
}

/*************   Function OF Set Pin Value   *************************/
/***************** Options of Copy_u8Value:
                                            HIGH
                                            LOW     ******************/
void  GPIO_voidSetPinValue (uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Value)
{
    switch (Copy_u8Port)
    {
         /*** PORT A ***/

        case GPIOA:
            if (Copy_u8Value == HIGH)
            {
                SET_BIT (GPIO_A->BSRR, Copy_u8Pin);
            }
            else if (Copy_u8Value == LOW)
            {
                SET_BIT (GPIO_A->BRR, Copy_u8Pin);
            }
            break;

        /*** PORT B ***/

        case GPIOB:
            if (Copy_u8Value == HIGH)
            {
                SET_BIT (GPIO_B->BSRR, Copy_u8Pin);
            }
            else if (Copy_u8Value == LOW)
            {
                SET_BIT (GPIO_B->BRR, Copy_u8Pin);
            }
            break;

        /*** PORT C ***/

        case GPIOC:
            if (Copy_u8Value == HIGH)
            {
                SET_BIT (GPIO_C->BSRR, Copy_u8Pin);
            }
            else if (Copy_u8Value == LOW)
            {
                SET_BIT (GPIO_C->BRR, Copy_u8Pin);
            }
            break;

        default :       break;
    }
}

/*************   Function OF Get Pin Value   *************************/

uint8 GPIO_u8GetPinValue (uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
    uint8 LOC_u8Result = 0;
    switch (Copy_u8Port)
    {
         /*** PORT A ***/

        case GPIOA:
            LOC_u8Result = GET_BIT (GPIO_A->IDR, Copy_u8Pin);
            break;

        /*** PORT B ***/

        case GPIOB:
            LOC_u8Result = GET_BIT (GPIO_B->IDR, Copy_u8Pin);
            break;

        /*** PORT C ***/

        case GPIOC:
            LOC_u8Result = GET_BIT (GPIO_C->IDR, Copy_u8Pin);
            break;

        default :       break;
    }
    return LOC_u8Result;
}

/*************   Function OF Toggle Pin Value   **********************/

void  GPIO_voidTogglePinValue (uint8 Copy_u8Port, uint8 Copy_u8Pin)
{
    switch (Copy_u8Port)
	{
		 /*** PORT A ***/

		case GPIOA:
					TOG_BIT(GPIO_A->ODR,Copy_u8Pin);
		  break;

		/*** PORT B ***/

		case GPIOB:
					TOG_BIT(GPIO_B->ODR,Copy_u8Pin);
		  break;

		/*** PORT C ***/

		case GPIOC:
		  TOG_BIT(GPIO_C->ODR,Copy_u8Pin);
		  break;

		default :       break;
	}
}

/*************   Function OF Set Pin PULL   *************************/
/***************** Options of Copy_u8Pull:
                                            PULL_UP
                                            PULL_DOWN ***************/
void  GPIO_voidSetPinPull (uint8 Copy_u8Port, uint8 Copy_u8Pin, uint8 Copy_u8Pull)
{
    switch (Copy_u8Port)
    {
         /*** PORT A ***/

        case GPIOA:
            if (Copy_u8Pull == PULL_UP)
            {
                SET_BIT (GPIO_A->ODR, Copy_u8Pin);
            }
            else if (Copy_u8Pull == PULL_DOWN)
            {
                CLR_BIT (GPIO_A->ODR, Copy_u8Pin);
            }
            break;

        /*** PORT B ***/

        case GPIOB:
            if (Copy_u8Pull == PULL_UP)
            {
                SET_BIT (GPIO_B->ODR, Copy_u8Pin);
            }
            else if (Copy_u8Pull == PULL_DOWN)
            {
                CLR_BIT (GPIO_B->ODR, Copy_u8Pin);
            }
            break;

        /*** PORT C ***/

        case GPIOC:
            if (Copy_u8Pull == PULL_UP)
            {
                SET_BIT (GPIO_C->ODR, Copy_u8Pin);
            }
            else if (Copy_u8Pull == PULL_DOWN)
            {
                CLR_BIT (GPIO_C->ODR, Copy_u8Pin);
            }
            break;

        default :       break;
    }
}
