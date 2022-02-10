/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 17 NOV 2021                                                       */
/*********************************************************************************/
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H



typedef struct {

	volatile uint32 CRL  ;
	volatile uint32 CRH  ;
	volatile uint32 IDR  ;
	volatile uint32 ODR  ;
	volatile uint32 BSRR ;
	volatile uint32 BRR  ;
	volatile uint32 LCKR ;

}GPIO_t;

/*******************   BASE Address Definition    *********************/

#define GPIOA_Base_Address      0x40010800      //define the boundary address of GPIOA
#define GPIOB_Base_Address      0x40010C00      //define the boundary address of GPIOB
#define GPIOC_Base_Address      0x40011000      //define the boundary address of GPIOC

/***********   REGISTER ADDRESSES FOR GPIOx     ***********************/
#define GPIO_A						( ( volatile GPIO_t* ) GPIOA_Base_Address )
#define GPIO_B						( ( volatile GPIO_t* ) GPIOB_Base_Address )
#define GPIO_C						( ( volatile GPIO_t* ) GPIOC_Base_Address )

#endif // GPIO_PRIVATE_H
