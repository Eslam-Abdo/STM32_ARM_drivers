/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 7 JUN  2021                                                       */
/*********************************************************************************/
#ifndef I2C_PRIVATE_H
#define I2C_PRIVATE_H


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
/*******************   BASE Address Definition    *********************/

#define I2C1_BASE_ADDRESS	0x40005400		//define the boundary address of I2C1
#define I2C2_BASE_ADDRESS	0x40005800		//define the boundary address of I2C2

#define I2C1 ( ( volatile I2C_t* ) I2C1_BASE_ADDRESS )
#define I2C2 ( ( volatile I2C_t* ) I2C2_BASE_ADDRESS )




#endif /* I2C_PRIVATE_H */
