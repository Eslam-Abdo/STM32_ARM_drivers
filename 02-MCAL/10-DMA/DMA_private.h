/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2021                                                      */
/*********************************************************************************/
#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

#include "STD_TYPES.h"

typedef struct {

	volatile u32 CR1     ;
	volatile u32 CR2     ;
	volatile u32 OAR1      ;
	volatile u32 OAR2      ;
	volatile u32 DR   ;
	volatile u32 SR1  ;
	volatile u32 SR2  ;
	volatile u32 CCR ;
	volatile u32 TRISE   ;

}I2C_t;

#define I2C1 ( ( volatile I2C_t* ) 0x40005400 )
#define I2C2 ( ( volatile I2C_t* ) 0x40005800 )




#endif /* I2C_PRIVATE_H_ */
