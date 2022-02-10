/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V02                                                               */
/* Date      : 19 NOV  2021                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_config.h"
#include "STK_private.h"



/* define Callback Global variable (pointer to function) */
static void (*STK_CallBack) (void);

/* define variable for interval mode 		*/
static uint8 STk_u8ModeOfInterval;




/*************	 Function OF Initialize clock Source of STK  **************************/
/* Apply clock choice from configuration file
 * Disable SysTick Interrupt
 * Disable SysTick									 
 */

void STK_voidInit (void)
{
#if STK_CLOCK_SRC == STK_SRC_AHB
	/* Disable STK - Disable STK Interrupt - Set clock source AHB	 */
	WRITE_REG(STK->CTRL,0x00000004);
#elif STK_CLOCK_SRC == STK_SRC_AHB_8
	/* Disable STK - Disable STK Interrupt - Set clock source AHB/8  */
	WRITE_REG(STK->CTRL,0);
#endif
}

/*************	 Function OF Set Busy Wait  **************************/
/* This is function Like delay function stop the code until finish count
 *  for 8/8 MHz
 *  1	 count 	= 1 us
 *  100	 counts = 100 us
 *  1000 counts = 1 ms
 *  and so on ...
 *												
 *  for 72/8 MHz
 *  9	  count  = 1 us
 *  900	  counts = 100 us
 *  9000  counts = 1 ms
 *  and so on ...											 
 */

void STK_voidSetBusyWait (uint32 Copy_u32Ticks)
{
	/* Load ticks to load register */
	WRITE_REG(STK->LOAD,Copy_u32Ticks);

	/* Start Timer */
	SET_BIT(STK->CTRL, 0);

	/* Wait till flag is raised */
	while( (GET_BIT(STK->CTRL, 16)) == 0);

	/* Stop Timer */
	CLR_BIT(STK->CTRL  ,0);
	WRITE_REG(STK->LOAD,0);
	WRITE_REG(STK->VAL ,0);

}

/*************	 Function OF Set Interval Single  **************************/
/* this function take ticks and function to do after ticks finished and do it once
 * but don't stop the code until finish count
 *  1	 count 	= 1 us
 *  100	 counts = 100 us
 *  1000 counts = 1 ms
 *  and so on ...
 *												 
 *  for 72/8 MHz
 *  9	  count  = 1 us
 *  900	  counts = 100 us
 *  9000  counts = 1 ms
 *  and so on ...
 */

void  STK_voidSetIntervalSingle (uint32 Copy_u32Ticks, void (*Copy_ptr) (void))
{
	/* Load ticks to load register */
	WRITE_REG(STK->LOAD,Copy_u32Ticks);

	/* Start Timer */
	SET_BIT(STK->CTRL, 0);

	/* Save CallBack */
	STK_CallBack = Copy_ptr;

	/* Set Mode to Single */
	STk_u8ModeOfInterval = STK_SINGLE_INTERVAL;

	/* Enable STk Interrupt */
	SET_BIT(STK->CTRL, 1);

}

/*************	 Function OF Set Interval Periodic  **************************/
/* this function take ticks and function to do after ticks finished and do it many time until you call a function stop it
 * but don't stop the code until finish count
 *  1	 count 	= 1 us
 *  100	 counts = 100 us
 *  1000 counts = 1 ms
 *  and so on ...
 *
 *  for 72/8 MHz
 *  9	  count  = 1 us
 *  900	  counts = 100 us
 *  9000  counts = 1 ms
 *  and so on ...													 
 */

void  STK_voidSetIntervalPeriodic (uint32 Copy_u32Ticks, void (*Copy_ptr) (void))
{
	/* Load ticks to load register */
		WRITE_REG(STK->LOAD,Copy_u32Ticks);

		/* Start Timer */
		SET_BIT(STK->CTRL, 0);

		/* Save CallBack */
		STK_CallBack = Copy_ptr;

		/* Set Mode to Period */
		STk_u8ModeOfInterval = STK_PERIOD_INTERVAL;

		/* Enable STk Interrupt */
		SET_BIT(STK->CTRL, 1);

}

/*************	 Function OF Stop Interval  **************************/

void STK_voidStopInterval (void)
{
	/* Disable STk Interrupt */
	CLR_BIT(STK->CTRL, 1);

	/* Stop Timer */
	CLR_BIT(STK->CTRL, 0);
	STK->LOAD = 0 ;
	STK->VAL = 0;
}

/*************	 Function OF Get Elaped Time  **************************/
/* Return the number of thicks that done (load - val) */
uint32 STK_u32GetElapedTime (void)
{
	uint32 Local_u32ElapsedTime;

	Local_u32ElapsedTime = READ_REG(STK->LOAD) - READ_REG(STK->VAL);

	return Local_u32ElapsedTime;
}

/*************	 Function OF Get Remaining Time  **************************/
/* Return the number of thicks that will count (remaining time) (val) */

uint32 STK_u32GetRemainingTime (void)
{
	uint32 Local_u32ElapsedTime;

	Local_u32ElapsedTime = READ_REG(STK->VAL);

	return Local_u32ElapsedTime;
}

/*************	 Function OF STK Interrupt  **************************/
/* This is function call a STK_CallBack() function to do when interrupt */

void SysTick_Handler (void)
{
	uint8 Local_u8Temporary;

	if (STk_u8ModeOfInterval == STK_SINGLE_INTERVAL)
	{ /* Stop Interval */
		STK_voidStopInterval();
	}

	/* CallBack notification */
	STK_CallBack();

	/* Clear Interrupt Flag */
	Local_u8Temporary = GET_BIT(STK->CTRL, 16);
}

/*************	 Function OF Delay_us  **************************/
/* This is function is call from (STK_voidSetBusyWait()), it is delay function stop the code until finish count
 *  1	 count 	= 1 us
 *  100	 counts = 100 us
 *  1000 counts = 1 ms
 *  and so on ...
 *
 *  for 72/8 MHz
 *  9	  count  = 1 us
 *  900	  counts = 100 us
 *  9000  counts = 1 ms
 *  and so on ...												 
 */

void STK_voidDelay_ms (uint32 Copy_u32Ticks)
{
	/* convert from ms to us as
	 * 1 ms = 1000 us for 8MHz
	 * 1 ms = 9000 us for 72MHz */
	Copy_u32Ticks *= 9000;
	STK_voidSetBusyWait(Copy_u32Ticks);
}

/*************	 Function OF START TIMER  **************************/
/* This is function is start timer
 *  1	 count 	= 1 us
 *  100	 counts = 100 us
 *  1000 counts = 1 ms
 *  and so on ...
 *
 *  for 72/8 MHz
 *  9	  count  = 1 us
 *  900	  counts = 100 us
 *  9000  counts = 1 ms
 *  and so on ...												 
 */
void STK_voidStartTimer(u32 Copy_u32Ticks)
{
	/* Load ticks to load register */
	WRITE_REG(STK->LOAD,Copy_u32Ticks);

	/* Start Timer */
	SET_BIT(STK->CTRL, 0);
}
/**********************************************************************/
uint32 finish_micros,old_time_micros,finish_millis,old_time_millis;
uint64 elapsed_time_micros,elapsed_time_millis;

void overflow_micros()
{
elapsed_time_micros += 16000000/9.0 - old_time_micros;
old_time_micros =0;
}

void STK_voidStartMicros(void)
{
	STK_voidSetIntervalPeriodic(16000000,overflow_micros);
}

uint64 Micros(void)
{
finish_micros = STK_u32GetElapedTime()/9.0;
elapsed_time_micros += finish_micros - old_time_micros;
old_time_micros = finish_micros;
return elapsed_time_micros;
}
void overflow_millis(){


elapsed_time_millis += 16000000/9000.0 - finish_millis;
old_time_millis =0;

}
void STK_voidStartMillis(void)
{

	STK_voidSetIntervalPeriodic(16000000,overflow_millis);
	
}
uint64 Millis(void)
{

  finish_millis = STK_u32GetElapedTime()/9000.0;
	elapsed_time_millis += finish_millis - old_time_millis;
  old_time_millis = finish_millis;
	
return elapsed_time_millis;
}
