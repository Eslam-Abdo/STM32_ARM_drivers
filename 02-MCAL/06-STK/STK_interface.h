/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 19 NOV  2021                                                      */
/*********************************************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H

/******************   STK Clock Source Definition   ******************/

#define STK_SRC_AHB_8				0
#define STK_SRC_AHB					1

/******************   STK interval mode Definition   ******************/

#define STK_SINGLE_INTERVAL			0
#define STK_PERIOD_INTERVAL			1


/***************   Function definition    ******************/

void   STK_voidInit					(void);
void   STK_voidSetBusyWait			(uint32 Copy_u32Ticks);
void   STK_voidSetIntervalSingle	(uint32 Copy_u32Ticks, void (*Copy_ptr) (void));
void   STK_voidSetIntervalPeriodic	(uint32 Copy_u32Ticks, void (*Copy_ptr) (void));
void   STK_voidStopInterval			(void);
uint32 STK_u32GetElapedTime			(void);
uint32 STK_u32GetRemainingTime		(void);

void   STK_voidDelay_ms				(uint32 Copy_u32Ticks);

void STK_voidStartTimer				(u32 Copy_u32Ticks);

void STK_voidStartMicros(void);
uint64 Micros(void);
void STK_voidStartMillis(void);
uint64 Millis(void);

#endif /* STK_INTERFACE_H */
