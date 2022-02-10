/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 11 OCT  2020                                                      */
/*********************************************************************************/
#ifndef EXTI_PRIVATE_H
#define EXTI_PRIVATE_H



/*******************   Register Definition     ***********************/

typedef struct
{
	volatile uint32 IMR;
	volatile uint32 EMR;
	volatile uint32 RTSR;
	volatile uint32 FTSR;
	volatile uint32 SWIER;
	volatile uint32 PR;

}EXTI_t;

/*******************   BASE Address Definition    *********************/

#define EXTI_BASE_ADDRESS	0x40010400		//define the boundary address of EXTI

#define EXTI 		((volatile EXTI_t *) EXTI_BASE_ADDRESS)




#endif // EXTI_PRIVATE_H
