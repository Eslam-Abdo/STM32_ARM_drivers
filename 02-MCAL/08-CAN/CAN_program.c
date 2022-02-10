/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "GPIO_interface.h"
#include "AFIO_interface.h"

#include "CAN_interface.h"
#include "CAN_config.h"
#include "CAN_private.h"
uint32 CAN_ErrorCode = CAN_ERROR_NONE;
/** BoudRate value **/
CAN_BitTimingConfig CAN_bitRateConfig[7];

/*********************** CallBack array of function ***************************/
CAN_Interrupt_Callbacks CAN_TxMailboxCompleteCallback[3] = {&CAN_TxMailbox0CompleteCallback,
															&CAN_TxMailbox1CompleteCallback,
															&CAN_TxMailbox2CompleteCallback};

CAN_Interrupt_Callbacks CAN_TxMailboxAbortCallback[3] = {&CAN_TxMailbox0AbortCallback,
														&CAN_TxMailbox1AbortCallback,
														&CAN_TxMailbox2AbortCallback};




void CAN_voidInit(void)
{
    /**  Enable the CAN interface clock **/
    RCC_voidEnableClock(RCC_APB1, APB1_CAN_EN);
    /** Configure CAN pins **/
    /* Remapping PINS   CAN_RX mapped to PB8,
                        CAN_TX mapped to PB9    */
    RCC_voidEnableClock(RCC_APB2, APB2_AFIO_EN);
    AFIO_voidRemapPeripheralPins (CAN_REMAP);
    /* Enable the clock for the CAN GPIOs */
    RCC_voidEnableClock(RCC_APB2, APB2_GPIOB_EN);
    GPIO_voidSetPinDirection(GPIOB, PIN8, INPUT_FLOATING); //RX
    GPIO_voidSetPinDirection(GPIOB, PIN9, OUTPUT_SPEED_2MHZ_AFPP); //TX
    /**  exit CAN sleep mode **/
    /* CLEAR SLEEP bit (SLEEP) */
    CLR_BIT(CAN->MCR,1);
    /* wait to exit sleep mode */
    while (!(GET_BIT(CAN->MSR,1) == 0));
     /**  Set CAN Initialization mode **/
    /* SET Initialization request BIT (INRQ) */
    SET_BIT(CAN->MCR,0);
    /* wait to enter in Initialization mode */
    while(!(GET_BIT(CAN->MSR,0) == 1));

    /** CHECK Transmit FIFO priority **/
#if TransmitFifoPriority == ENABLE
     /* by the request order */
        SET_BIT(CAN->MCR,2); //TXFP
#else
     /* by the identifier of the message */
        CLR_BIT(CAN->MCR,2); //TXFP
#endif
    /** CHECK Receive FIFO locked mode **/
#if ReceiveFifoLocked == ENABLE
     /* Receive FIFO locked against overrun.
         Once a receive FIFO is full the next incoming message will be discarded. */
        SET_BIT(CAN->MCR,3); //RFLM
#else
     /* Receive FIFO not locked on overrun.
         Once a receive FIFO is full the next incoming message will overwrite the previous one. */
        CLR_BIT(CAN->MCR,3); //RFLM
#endif
    /** CHECK automatic retransmission **/
#if AutoRetransmission == ENABLE
        CLR_BIT(CAN->MCR,4); //NART
#else
        SET_BIT(CAN->MCR,4); //NART
#endif

    /** CHECK automatic wakeup mode **/
#if AutoBussOff == ENABLE
        SET_BIT(CAN->MCR,5); //AWUM
#else
       CLR_BIT(CAN->MCR,5); //AWUM
#endif

    /** CHECK automatic bus-off management **/
#if AutoBussOff == ENABLE
        SET_BIT(CAN->MCR,6); //ABOM
#else
        CLR_BIT(CAN->MCR,6); //ABOM
#endif

    /** CHECK Time triggered communication mode **/
#if TimeTriggeredMode == ENABLE
        SET_BIT(CAN->MCR,7); //TTCM
#else
        CLR_BIT(CAN->MCR,7); //TTCM
#endif


     /** Set the bit timing register **/
  WRITE_REG(CAN->BTR, (uint32) (MODE |
		  ((CAN_bitRateConfig[BOUDRATE].TS2-1) << 20) |
		  ((CAN_bitRateConfig[BOUDRATE].TS1-1) << 16) |
		  (CAN_bitRateConfig[BOUDRATE].BRP-1)));
}


void CAN_voidAddTxMsg( CAN_TxHeaderTypeDef *pTxHeader, uint8 Local_u8Data[])
{
	uint32 local_u8TransmitMailbox; // which mailbox is empty to set Local_u8Data in it (read CODE bit in TSR register)
	uint32 local_u32TSR; //transmit status register
	local_u32TSR = READ_REG(CAN->TSR);
	 /* Check that all the Tx mailboxes are not full */
//	while(1)
//	{
		if ( (GET_BIT(local_u32TSR, 26) != 0x0) || /* TME0 */
			 (GET_BIT (local_u32TSR,27) != 0x0) || /* TME1 */
			 (GET_BIT(local_u32TSR,28) != 0x0) )  /* TME2 */
		{
			/* Select an empty transmit mailbox */
			local_u8TransmitMailbox = ((local_u32TSR >> 24) & 0x3); //(read CODE[1:0] bit in TSR register)
			 /* Check transmit mailbox value */
			if (local_u8TransmitMailbox <=2)
			{
				/* Set up the Id */
				  if (pTxHeader->IDE == CAN_ID_STD)
				  {
					CAN->TxMailBox[local_u8TransmitMailbox].TIR = ((pTxHeader->StdId << 21) |
															pTxHeader->RTR);
				  }
				  else
				  {
					CAN->TxMailBox[local_u8TransmitMailbox].TIR = ((pTxHeader->ExtId << 3) |
																		pTxHeader->IDE | pTxHeader->RTR);
				  }

				  /* Set up the DLC */
				  CAN->TxMailBox[local_u8TransmitMailbox].TDTR = (pTxHeader->DLC);
				  /* Set up the Transmit Global Time mode */
				  if (pTxHeader->TransmitGlobalTime == ENABLE)
				  {
					  SET_BIT(CAN->TxMailBox[local_u8TransmitMailbox].TDTR, 8);
				  }
				  /* Set up the Local_u8Data field */
				WRITE_REG(CAN->TxMailBox[local_u8TransmitMailbox].TDHR,
							  ((uint32)Local_u8Data[7] << 24) |
							  ((uint32)Local_u8Data[6] << 16) |
							  ((uint32)Local_u8Data[5] << 8 ) |
							  ((uint32)Local_u8Data[4]));
				WRITE_REG(CAN->TxMailBox[local_u8TransmitMailbox].TDLR,
							  ((uint32)Local_u8Data[3] << 24) |
							  ((uint32)Local_u8Data[2] << 16) |
							  ((uint32)Local_u8Data[1] << 8 ) |
							  ((uint32)Local_u8Data[0]));
				/* Request transmission */
				SET_BIT(CAN->TxMailBox[local_u8TransmitMailbox].TIR, 0);
  //			while(GET_BIT(CAN->TxMailBox[local_u8TransmitMailbox].TIR, 0) == 1); // clear by hardware when mailbox empty
			}
//			break;
//		}
	}
}


void CAN_voidStart(void)
{
	/* CLEAR Initialization request BIT (INRQ) */
	CLR_BIT(CAN->MCR,0);
	/* wait to enter in Initialization mode */
	while(!(GET_BIT(CAN->MSR,0) == 0));
}


void CAN_voidGetRxMsg(uint32 local_u8RxFifo, CAN_RxHeaderTypeDef *pRxHeader, uint8 Local_u8Data[])
{
    /* Get Identifier extension */
	pRxHeader->IDE =  GET_BIT(CAN->FIFOMailBox[local_u8RxFifo].RIR,2);
    if (pRxHeader->IDE == CAN_ID_STD)
    {/* GET the Id */
      pRxHeader->StdId = CAN->FIFOMailBox[local_u8RxFifo].RIR >> 21;
    }
    else
    {
      pRxHeader->ExtId = CAN->FIFOMailBox[local_u8RxFifo].RIR >> 3;
    }
    /* GET the RTR */
    pRxHeader->RTR = GET_BIT(CAN->FIFOMailBox[local_u8RxFifo].RIR,1);
    /* GET the DLC */
    pRxHeader->DLC = (CAN->FIFOMailBox[local_u8RxFifo].RDTR & 0xF);
    /* GET the (FMI) Filter Match Index */
    pRxHeader->FilterMatchIndex = (CAN->FIFOMailBox[local_u8RxFifo].RDTR >> 8) & 0xFF;
    /* GET the Time stamp */
    pRxHeader->TimeStamp = (CAN->FIFOMailBox[local_u8RxFifo].RDTR >> 16) & 0XFFFF;

    /* Get the data */
		#if 0
    Local_u8Data[0] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDLR 	  ) & 0XFF);
    Local_u8Data[1] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDLR >> 8 ) & 0XFF);
    Local_u8Data[2] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDLR >> 16) & 0XFF);
    Local_u8Data[3] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDLR >> 24) & 0XFF);
    Local_u8Data[4] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDHR 	  ) & 0XFF);
    Local_u8Data[5] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDHR >> 8 ) & 0XFF);
    Local_u8Data[6] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDHR >> 16) & 0XFF);
    Local_u8Data[7] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDHR >> 24) & 0XFF);
		#else
		for(u8 i=0 ; i < 8 ; i++)
		{/*clear buff*/
			Local_u8Data[i] = 0;
		}
		for(u8 i=0 ; i < pRxHeader->DLC ; i++)
		{
			if (i<4)
				Local_u8Data[i] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDLR >>(i*8) ) & 0XFF);
			else
				Local_u8Data[i] = (uint8)((CAN->FIFOMailBox[local_u8RxFifo].RDHR 	>>((i-4)*8)  ) & 0XFF);
		}
		
		#endif
    /* Release the FIFO */
    if (local_u8RxFifo == CAN_RX_FIFO0)
    {
      /* Release RX FIFO 0 */
      SET_BIT(CAN->RF0R, 5);
    }
    else
    {
      /* Release RX FIFO 1 */
      SET_BIT(CAN->RF1R, 5);
    }
}
/** CAN RX Pending **/
uint8 CAN_voidRXPending(uint8 local_u8RxFifo)
{
	/* return the Rx FIFO  message pending */
	if (local_u8RxFifo == CAN_RX_FIFO0) /* Rx element is assigned to Rx FIFO 0 */
	{
		/* return value of the Rx FIFO 0  */
	 return (CAN->RF0R & 0X3);

	}
	else /* Rx element is assigned to Rx FIFO 1 */
	{
		/* return value of the Rx FIFO 1  */
		return (CAN->RF1R & 0X3);
	}
}
/** CAN CONFIG filter **/
void CAN_voidConfigFilter( CAN_FilterTypeDef *pFilterConfig)
{
	/* Initialization mode for the filter */
	SET_BIT(CAN->FMR, 0);
	/* Convert filter number into bit position */
	uint32 local_u32FilterBitPos = pFilterConfig->FilterBank ;

	/* Filter Deactivation */
	CLR_BIT(CAN->FA1R, pFilterConfig->FilterBank);

	/* Filter Scale */
	if (pFilterConfig->FilterScale == CAN_FILTERSCALE_16BIT)
	{
	  /* 16-bit scale for the filter */
	  CLR_BIT(CAN->FS1R, local_u32FilterBitPos);

	  /* Filter mapping
	     *   15-8          7-5    4   3    2-0
	     * STID[10:3] STID[2:0] RTR IDE EXID[17:15]
	     * */

	  /* First 16-bit identifier and First 16-bit mask */
	  /* Or First 16-bit identifier and Second 16-bit identifier */
	  CAN->FilterBankRegister[pFilterConfig->FilterBank].FR1 =(
			  	  	  	  	  	  	  ((pFilterConfig->FilterMaskIdLow & 0x0000FFFF) << 16) |
									  (pFilterConfig->FilterIdLow	   & 0x0000FFFF) );

	  /* Second 16-bit identifier and Second 16-bit mask */
	  /* Or Third 16-bit identifier and Fourth 16-bit identifier */
	  CAN->FilterBankRegister[pFilterConfig->FilterBank].FR2 =(
			  	  	  	  	  	  	  	  	  	 ((pFilterConfig->FilterMaskIdHigh & 0x0000FFFF) << 16) |
			  									  (pFilterConfig->FilterIdHigh 	   & 0x0000FFFF) );
	}

	else if (pFilterConfig->FilterScale == CAN_FILTERSCALE_32BIT)
	{
	  /* 32-bit scale for the filter */
	  SET_BIT(CAN->FS1R, local_u32FilterBitPos);

	  /* Filter mapping                                   
		 *   31-24      23-21     21-16  		15-8	 7-3	  2   1  0
		 * STID[10:3] STID[2:0] EXID[17:13] EXID[12:5] EXID[4:0] IDE RTR 0
		 * */

	  /* 32-bit identifier or First 32-bit identifier */
	  CAN->FilterBankRegister[pFilterConfig->FilterBank].FR1 =(
											((pFilterConfig->FilterIdHigh & 0x0000FFFF) << 16) |
											 (pFilterConfig->FilterIdLow  & 0x0000FFFF));

	  /* 32-bit mask or Second 32-bit identifier */
	  CAN->FilterBankRegister[pFilterConfig->FilterBank].FR2 =(
												((pFilterConfig->FilterMaskIdHigh & 0x0000FFFF) << 16) |
												 (pFilterConfig->FilterMaskIdLow & 0x0000FFFF));
	}

	/* Filter Mode */
	if (pFilterConfig->FilterMode == CAN_FILTERMODE_IDMASK)
	{
	  /* Id/Mask mode for the filter*/
	  CLR_BIT(CAN->FM1R, local_u32FilterBitPos);
	}
	else
	{
	  /* Identifier list mode for the filter*/
	  SET_BIT(CAN->FM1R, local_u32FilterBitPos);
	}

	/* Filter FIFO assignment */
	if (pFilterConfig->FilterFIFOAssignment == CAN_FILTER_FIFO0)
	{
	  /* FIFO 0 assignation for the filter */
	  CLR_BIT(CAN->FFA1R, local_u32FilterBitPos);
	}
	else
	{
	  /* FIFO 1 assignation for the filter */
	  SET_BIT(CAN->FFA1R, local_u32FilterBitPos);
	}

	/* Filter activation */
	if (pFilterConfig->FilterActivation == ENABLE)
	{
	  SET_BIT(CAN->FA1R, local_u32FilterBitPos);
	}

	/* Leave the initialisation mode for the filter */
	CLR_BIT(CAN->FMR, 0);
}

uint32 CAN_voidGetErrorCode(void)
{
	return CAN_ErrorCode;
}


/****************************************************************************
*
==============================================================================
                     ##### CAN Interrupt functions #####
==============================================================================
*/
/*********** OPTION OF IRQn:
 * 										CAN_TX_IRQn  	=>>>> CAN TX Interrupts
 * 										CAN_RX0_IRQn	=>>>> CAN RX0 (FIFO_0) Interrupts
 * 										CAN_RX1_IRQn	=>>>> CAN RX1 (FIFO_1) Interrupts
 * 										CAN_SCE_IRQn	=>>>> CAN SCE (Status Change Error) Interrupts
 	 	 	 	 	 	 	 	 	 	 	 	 	****************************/
/** Enable NVIC Interrupt **/
void CAN_voidInitInterput(IRQn_Type IRQn)
{ /* init interrput*/
	NVIC_voidEnableInterrupt(IRQn);
	NVIC_voidSetPendingFlag(IRQn);
}
/** Disanable NVIC Interrupt **/
void CAN_voidDeiniterputInit(IRQn_Type IRQn)
{ /* deinit interrput*/
	NVIC_voidDisableInterrupt(IRQn);
	NVIC_voidClearPendingFlag(IRQn);
}

void CAN_voidEnableInterrupt(uint32 local_u32ActiveITs)
{
	CAN->IER |= local_u32ActiveITs;
}

void CAN_voidDisableInterrupt(uint32 local_u32ActiveITs)
{
	CAN->IER &= ~ local_u32ActiveITs;
}

/****************************************************************************
*
==============================================================================
                     ##### CAN Handler functions #####
==============================================================================
*/

/*************************** 	CAN TX Interrupt Handler	 *********************/
void CAN_voidTX_Interrupt_Handler(void)
{
	 CAN_ErrorCode  = CAN_ERROR_NONE;
	uint32 tsrflags  = READ_REG(CAN->TSR);

	/* Transmit Mailbox [0:2] management *****************************************/
	for (uint8 local_u8TxBitPos = 0 ; local_u8TxBitPos <= 16 ; local_u8TxBitPos += 8 ) // local_u8TxBitPos refer to Position of RQCPx bit in TSR Register
	{
		if (GET_BIT(tsrflags, (local_u8TxBitPos)) != 0) /* RQCP: Request completed mailbox [0:2] */
		{
		  /* Clear the Transmission Complete flag (and TXOK,ALST,TERR0 bits) */
		  SET_BIT(CAN->TSR, local_u8TxBitPos);     /* RQCP: Request completed mailbox [0:2] */

		  if (GET_BIT(tsrflags, (local_u8TxBitPos + 1)) != 0) /* TXOK: Transmission OK of mailbox [0:2] */
		  {
			/* Transmission Mailbox complete callback */

			/* Call weak (surcharged) callback */
			CAN_TxMailboxCompleteCallback[local_u8TxBitPos/8]();
		  }
		  else
		  {
			if (GET_BIT(tsrflags, (local_u8TxBitPos + 2)) != 0) /* ALST: Arbitration lost for mailbox [0:2] */
			{
			  /* Update error code */
				switch (local_u8TxBitPos/8)
				{
				case 0 :
					CAN_ErrorCode |= CAN_ERROR_TX_ALST0; break;
				case 1 :
					CAN_ErrorCode |= CAN_ERROR_TX_ALST1; break;
				case 2 :
					CAN_ErrorCode |= CAN_ERROR_TX_ALST2; break;
				}
			}
			else if (GET_BIT(tsrflags, (local_u8TxBitPos + 3)) != 0) /* TERR: Transmission error of mailbox [0:2] */
			{
			  /* Update error code */
			  CAN_ErrorCode |= CAN_ERROR_TX_TERR0;
			  switch (local_u8TxBitPos/8)
			{
			case 0 :
				CAN_ErrorCode |= CAN_ERROR_TX_TERR0; break;
			case 1 :
				CAN_ErrorCode |= CAN_ERROR_TX_TERR1; break;
			case 2 :
				CAN_ErrorCode |= CAN_ERROR_TX_TERR2; break;
			}

			}
			else /* ABRQ: Abort request for mailbox [0:2] */
			{
			  /* Transmission Mailbox  abort callback */

			  /* Call weak (surcharged) callback */
			  CAN_TxMailboxAbortCallback[local_u8TxBitPos/8]();
			}
		  }
		}
	}
	/* Call the Error call Back in case of Errors */
	if (CAN_ErrorCode != CAN_ERROR_NONE)
	{
		/* Call Error callback function */
		CAN_ErrorCallback();
	}
}

/*************************  CAN RX FIFO 0 Interrupt Handler *****************************/
void CAN_voidRX_FIFO0_Interrupt_Handler(void)
{
	uint32 CAN_ErrorCode  = CAN_ERROR_NONE;
	uint32 interrupts = READ_REG(CAN->IER);
	uint32 rf0rflags = READ_REG(CAN->RF0R);
	/* Receive FIFO 0 overrun interrupt management *****************************/
	if (GET_BIT(interrupts,3) != 0) /* FOVIE0: FIFO overrun interrupt enable */
	{
		if (GET_BIT(rf0rflags,4) != 0) /* FOVR0: FIFO 0 overrun */
		{
		  /* Set CAN error code to Rx Fifo 0 overrun error */
		  CAN_ErrorCode |= CAN_ERROR_RX_FOV0;

		  /* Clear FIFO0 Overrun Flag */
		  SET_BIT(CAN->RF0R, 4);
		}
	}

	/* Receive FIFO 0 full interrupt management ********************************/
	if (GET_BIT(interrupts,2) != 0) /* FFIE0: FIFO full interrupt enable */
	{
		if (GET_BIT(rf0rflags,3) != 0) /* FULL0: FIFO 0 full */
		{
		  /* Clear FIFO 0 full Flag */
			SET_BIT(CAN->RF0R, 3);

		  /* Receive FIFO 0 full Callback */
		  /* Call weak (surcharged) callback */
		  CAN_RxFifo0FullCallback();
		}
	}

	/* Receive FIFO 0 message pending interrupt management *********************/
	if (GET_BIT(interrupts,1) != 0) /* FMPIE0: FIFO message pending interrupt enable */
	{
		/* Check if message is still pending */
		if ((CAN->RF0R & 0x3) != 0) /* FMP0[1:0]: FIFO 0 message pending */
		{
		  /* Receive FIFO 0 mesage pending Callback */
		  /* Call weak (surcharged) callback */
		  CAN_RxFifo0MsgPendingCallback();
		}
	}
	/* Call the Error call Back in case of Errors */
	if (CAN_ErrorCode != CAN_ERROR_NONE)
	{
		/* Call Error callback function */
		CAN_ErrorCallback();
	}
}

/*************************  CAN RX FIFO 1 Interrupt Handler *****************************/
void CAN_voidRX_FIFO1_Interrupt_Handler(void)
{
	  uint32 CAN_ErrorCode  = CAN_ERROR_NONE;
	  uint32 interrupts = READ_REG(CAN->IER);
	  uint32 rf1rflags = READ_REG(CAN->RF1R);
	  /* Receive FIFO 1 overrun interrupt management *****************************/
	  if (GET_BIT(interrupts,6) != 0) /* FOVIE1: FIFO overrun interrupt enable */
	  {
		if (GET_BIT(rf1rflags,4) != 0) /* FOVR1: FIFO 1 overrun */
		{
		  /* Set CAN error code to Rx Fifo 1 overrun error */
		  CAN_ErrorCode |= CAN_ERROR_RX_FOV1;

		  /* Clear FIFO1 Overrun Flag */
		  SET_BIT(CAN->RF1R, 4);
		}
	  }

	  /* Receive FIFO 1 full interrupt management ********************************/
	  if (GET_BIT(interrupts,5) != 0) /* FFIE1: FIFO full interrupt enable */
	  {
		if (GET_BIT(rf1rflags,3) != 0) /* FULL1: FIFO 1 full */
		{
		  /* Clear FIFO 1 full Flag */
			SET_BIT(CAN->RF1R, 3);

		  /* Receive FIFO 1 full Callback */
		  /* Call weak (surcharged) callback */
		  CAN_RxFifo1FullCallback();
		}
	  }

	  /* Receive FIFO 1 message pending interrupt management *********************/
	if (GET_BIT(interrupts,4) != 0) /* FMPIE1: FIFO message pending interrupt enable */
	{
		/* Check if message is still pending */
		if ((CAN->RF1R & 0x3) != 0) /* FMP1[1:0]: FIFO 0 message pending */
		{
		  /* Receive FIFO 1 mesage pending Callback */
		  /* Call weak (surcharged) callback */
		  CAN_RxFifo1MsgPendingCallback();
		}
	}
	  /* Call the Error call Back in case of Errors */
	if (CAN_ErrorCode != CAN_ERROR_NONE)
	{
		/* Call Error callback function */
		CAN_ErrorCallback();
	}
}


/*************************** CAN SCE (Status Change Error) Interrupt Handler *********************/
void CAN_voidSCE_Interrupt_Handler(void)
{
	  CAN_ErrorCode  = CAN_ERROR_NONE;
	  uint32 interrupts = READ_REG(CAN->IER);
	  uint32 msrflags  = READ_REG(CAN->MSR);
	  uint32 esrflags = READ_REG(CAN->ESR);


	  /* Sleep interrupt management *********************************************/
	  if (GET_BIT(interrupts,17) != 0) /* SLKIE: Sleep interrupt enable */
	  {
	    if (GET_BIT(msrflags,4) != 0) /* SLAKI: Sleep acknowledge interrupt */
	    {
	      /* Clear Sleep interrupt Flag */
	      SET_BIT(CAN->MSR, 4); /* SLAKI: Sleep acknowledge interrupt */

	      /* Sleep Callback */
	      CAN_SleepCallback();
	    }
	  }

	  /* WakeUp interrupt management *********************************************/
	  if (GET_BIT(interrupts,16) != 0) /* WKUIE: Wakeup interrupt enable */
	  {
	    if (GET_BIT(msrflags,3) != 0) /* WKUI: Wakeup interrupt */
	    {
	      /* Clear WakeUp Flag */
	    	SET_BIT(CAN->MSR, 3); /* WKUI: Wakeup interrupt */

	      /* WakeUp Callback */
	      CAN_WakeUpFromRxMsgCallback();
	    }
	  }

	  /* Error interrupts management *********************************************/
	  if (GET_BIT(interrupts,15) != 0) /* ERRIE: Error interrupt enable */
	  {
	    if (GET_BIT(msrflags,2) != 0) /* ERRI: Error interrupt */
	    {
	      /* Check Error Warning Flag */
	      if ((GET_BIT(interrupts,8) != 0) && /* EWGIE: Error warning interrupt enable*/
	          (GET_BIT(esrflags,0) != 0)) /* EWGF: Error warning flag */
	      {
	        /* Set CAN error code to Error Warning */
	        CAN_ErrorCode |= CAN_ERROR_EWG;

	        /* No need for clear of Error Warning Flag as read-only */
	      }

	      /* Check Error Passive Flag */
	      if ((GET_BIT(interrupts,9) != 0) && /* EPVIE: Error passive interrupt enable*/
	          (GET_BIT(esrflags,1) != 0)) /* EPVF: Error passive flag */
	      {
	        /* Set CAN error code to Error Passive */
	        CAN_ErrorCode |= CAN_ERROR_EPV;

	        /* No need for clear of Error Passive Flag as read-only */
	      }

	      /* Check Bus-off Flag */
	      if ((GET_BIT(interrupts,10) != 0) && /* BOFIE: Bus-off interrupt enable */
	          (GET_BIT(esrflags,2) != 0)) /* BOFF: Bus-off flag */
	      {
	        /* Set CAN error code to Bus-Off */
	        CAN_ErrorCode |= CAN_ERROR_BOF;

	        /* No need for clear of Error Bus-Off as read-only */
	      }

	      /* Check Last Error Code Flag */
	      if ((GET_BIT(interrupts,11) != 0) && /* LECIE: Last error code interrupt enable */
	          (((esrflags >> 4) & 0x7) != 0)) /* LEC[2:0]: Last error code */
	      {
	        switch ((esrflags >> 4) & 0x7)  // 7=0b111 /* LEC[2:0]: Last error code */
	        {
	          case (0x1):
	            /* Set CAN error code to Stuff error */
	            CAN_ErrorCode |= CAN_ERROR_STF;
	            break;
	          case (0x2):
	            /* Set CAN error code to Form error */
	            CAN_ErrorCode |= CAN_ERROR_FOR;
	            break;
	          case (0x3):
	            /* Set CAN error code to Acknowledgement error */
	            CAN_ErrorCode |= CAN_ERROR_ACK;
	            break;
	          case (0x4):
	            /* Set CAN error code to Bit recessive error */
	            CAN_ErrorCode |= CAN_ERROR_BR;
	            break;
	          case (0x5):
	            /* Set CAN error code to Bit Dominant error */
	            CAN_ErrorCode |= CAN_ERROR_BD;
	            break;
	          case (0x6):
	            /* Set CAN error code to CRC error */
	            CAN_ErrorCode |= CAN_ERROR_CRC;
	            break;
	          default:
	            break;
	        }

	        /* Clear Last error code Flag */
	        CAN->ESR &= ~0x70; /* ERRI: Error interrupt */
	      }
	    }

	    /* Clear ERRI Flag */
	    SET_BIT(CAN->MSR, 2); /* ERRI: Error interrupt */
	  }

	  /* Call the Error call Back in case of Errors */
	  if (CAN_ErrorCode != CAN_ERROR_NONE)
	  {
	    /* Call Error callback function */
	    CAN_ErrorCallback();
	  }
}


/*
==============================================================================
                         ##### Callback functions #####
 ==============================================================================
   [..]
   This subsection provides the following callback functions:
     (+) CAN_TxMailboxCompleteCallback[3]
     (+) CAN_TxMailboxAbortCallback[3]
     (+) HAL_CAN_RxFifo0MsgPendingCallback
     (+) HAL_CAN_RxFifo0FullCallback
     (+) HAL_CAN_RxFifo1MsgPendingCallback
     (+) HAL_CAN_RxFifo1FullCallback
     (+) CAN_SleepCallback
     (+) CAN_WakeUpFromRxMsgCallback
     (+) CAN_ErrorCallback
*/
/*************	 Callbacks functions 	************************/

__weak void CAN_TxMailbox0CompleteCallback()
{
 
}

__weak void CAN_TxMailbox1CompleteCallback()
{

}
__weak void CAN_TxMailbox2CompleteCallback()
{

}
__weak void CAN_TxMailbox0AbortCallback()
{

}
__weak void CAN_TxMailbox1AbortCallback()
{

}
__weak void CAN_TxMailbox2AbortCallback()
{

}
__weak void CAN_RxFifo0MsgPendingCallback()
{

}
__weak void CAN_RxFifo0FullCallback()
{

}
__weak void CAN_RxFifo1MsgPendingCallback()
{

}
__weak void CAN_RxFifo1FullCallback()
{

}
__weak void CAN_SleepCallback()
{

}
__weak void CAN_WakeUpFromRxMsgCallback()
{

}
__weak void CAN_ErrorCallback()
{

}

/*
 * #######################################################################
 * 						CAN_Interrupt_IRQHandler
 * #######################################################################
 */
void USB_HP_CAN1_TX_IRQHandler(void) /* USB High Priority or CAN1 TX */
{
	CAN_voidTX_Interrupt_Handler();
}
void USB_LP_CAN1_RX0_IRQHandler(void) /* USB Low  Priority or CAN1 RX0 */
{
	CAN_voidRX_FIFO0_Interrupt_Handler();
}
void CAN1_RX1_IRQHandler(void) /* CAN1 RX1 */
{
	CAN_voidRX_FIFO1_Interrupt_Handler();
}
void CAN1_SCE_IRQHandler(void) /* CAN1 SCE */
{
	CAN_voidSCE_Interrupt_Handler();
}


