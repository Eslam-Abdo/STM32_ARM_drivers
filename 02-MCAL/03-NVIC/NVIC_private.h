/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 19 NOV 2021                                                       */
/*********************************************************************************/
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H


/*******************   Register Definition     ***********************/
typedef struct
{
	/* Enable External interrupts from 0 to 31 & from 32 to 63 */
	volatile uint32 ISER[2];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
	volatile uint32 RESERVED0[30];
	volatile uint32 ICER[2];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
	volatile uint32 RSERVED1[30];
	volatile uint32 ISPR[2];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
	volatile uint32 RESERVED2[30];
	volatile uint32 ICPR[2];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
	volatile uint32 RESERVED3[30];
	volatile uint32 IABR[2];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
	volatile uint32 RESERVED4[62];
	volatile uint8  IP[60];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
	volatile uint32 RESERVED5[689];
	volatile uint32 STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}NVIC_t;

/* System control block (SCB) */
typedef struct
{
	volatile uint32 CPUID;
	volatile uint32 ICSR;
	volatile uint32 VTOR;
	volatile uint32 AIRCR;
	volatile uint32 SCR;
	volatile uint32 CCR;
	volatile uint32 SHPR1;
	volatile uint32 SHPR2;
	volatile uint32 SHPR3;
	volatile uint32 SHCSR;
	volatile uint32 CFSR;
	volatile uint32 HFSR;
	volatile uint32 RESERVED;
	volatile uint32 MMFAR;
	volatile uint32 BFAR;                  /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}SCB_t;

/*******************   BASE Address Definition    *********************/

#define NVIC_Base_Address      0xE000E100      //define the boundary address of NVIC
#define SCB_Base_Address       0xE000ED00	   //define the boundary address of SCB

#define NVIC 					( ( volatile NVIC_t* ) NVIC_Base_Address )
#define SCB						( ( volatile SCB_t* ) SCB_Base_Address )



#endif // NVIC_PRIVATE_H
