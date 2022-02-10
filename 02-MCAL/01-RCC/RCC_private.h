/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 17 NOV 2021                                                       */
/*********************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H


/*******************   Register Definition     ***********************/
typedef struct {

	volatile uint32 CR       ;
	volatile uint32 CFGR     ;
	volatile uint32 CIR      ;
	volatile uint32 APB2RSTR ;
	volatile uint32 APB1RSTR ;
	volatile uint32 AHBENR   ;
	volatile uint32 APB2ENR  ;
	volatile uint32 APB1ENR  ;
	volatile uint32 BDCR     ;
	volatile uint32 CSR      ;
}RCC_t;

/*******************   BASE Address Definition    *********************/

#define RCC_BASE_ADDRESS	0x40021000		//define the boundary address of RCC

#define RCC ( ( volatile RCC_t* ) RCC_BASE_ADDRESS)


#endif // RCC_PRIVATE_H
