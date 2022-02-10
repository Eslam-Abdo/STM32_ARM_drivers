/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#ifndef STK_PRIVATE_H
#define STK_PRIVATE_H


/*******************   Register Definition     ***********************/

typedef struct
{
	volatile uint32 CTRL;
	volatile uint32 LOAD;
	volatile uint32 VAL;
	volatile uint32 CALIB;
}STK_t;
/*******************   BASE Address Definition    *********************/

#define STK_BASE_ADDRESS	0xE000E010 		//define the boundary address of STK

#define STK			((volatile STK_t *) STK_BASE_ADDRESS)

#endif /* STK_PRIVATE_H */
