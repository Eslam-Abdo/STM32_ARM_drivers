/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#ifndef CAN_INTERFACE_H
#define CAN_INTERFACE_H

/** @defgroupCAN CAN_Activation  CAN Activation **/
#define DISABLE			 0
#define ENABLE 			 1

/** @defgroup CAN_identifier_type CAN Identifier Type **/
#define CAN_ID_STD                  ((uint32)(0x0))  /*!< Standard Id */
#define CAN_ID_EXT                  ((uint32)(0x4))  /*!< Extended Id */

/** @defgroup CAN_remote_transmission_request CAN Remote Transmission Request **/
#define CAN_RTR_DATA                ((uint32)(0x0))  /*!< Data frame   */
#define CAN_RTR_REMOTE              ((uint32)(0x2))  /*!< Remote frame */

#define CAN_RTR_REMOTEFLAG          ((uint32)(0x1))  /*!< Remote flag   */


/** @defgroup CAN_receive_FIFO_number CAN Receive FIFO Number **/
#define CAN_RX_FIFO0                ((uint32)(0x0))  /*!< CAN receive FIFO 0 */
#define CAN_RX_FIFO1                ((uint32)(0x1))  /*!< CAN receive FIFO 1 */

/** @defgroup CAN_filter_FIFO CAN Filter FIFO **/
#define CAN_FILTER_FIFO0            ((uint32)(0x0))  /*!< Filter FIFO 0 assignment for filter x */
#define CAN_FILTER_FIFO1            ((uint32)(0x1))  /*!< Filter FIFO 1 assignment for filter x */

/** @defgroup CAN_filter_mode CAN Filter Mode **/
#define CAN_FILTERMODE_IDMASK       ((uint32)(0x0))  /*!< Identifier mask mode */
#define CAN_FILTERMODE_IDLIST       ((uint32)(0x1))  /*!< Identifier list mode */

/** @defgroup CAN_filter_scale CAN Filter Scale */
#define CAN_FILTERSCALE_16BIT       ((uint32)(0x0))  /*!< Two 16-bit filters */
#define CAN_FILTERSCALE_32BIT       ((uint32)(0x1))  /*!< One 32-bit filter  */

/** @defgroup CAN_IRQn **/
#define CAN_TX_IRQn			19 /* CAN TX Interrupts*/
#define CAN_RX0_IRQn		20 /* CAN RX0 (FIFO_0) Interrupts */
#define CAN_RX1_IRQn		21 /* CAN RX1 (FIFO_1) Interrupts */
#define CAN_SCE_IRQn		22 /* CAN SCE (Status Change Error) Interrupts */

/**
 * =============================================================================================
 *     					### CAN INE Bits definition
 *=============================================================================================
 **/
/** @defgroup CAN_Interrupts CAN Interrupts **/

/* Transmit Interrupt */
#define CAN_IER_TX_MAILBOX_EMPTY    	((uint32)(0x1))   /*!< Transmit mailbox empty interrupt */

/* Receive Interrupts */
#define CAN_IER_RX_FIFO0_MSG_PENDING	((uint32)(0x2 ))   /*!< FIFO 0 message pending interrupt */
#define CAN_IER_RX_FIFO0_FULL        	((uint32)(0x4 ))   /*!< FIFO 0 full interrupt            */
#define CAN_IER_RX_FIFO0_OVERRUN     	((uint32)(0x8 ))   /*!< FIFO 0 overrun interrupt         */
#define CAN_IER_RX_FIFO1_MSG_PENDING 	((uint32)(0x10))   /*!< FIFO 1 message pending interrupt */
#define CAN_IER_RX_FIFO1_FULL        	((uint32)(0x20))   /*!< FIFO 1 full interrupt            */
#define CAN_IER_RX_FIFO1_OVERRUN    	((uint32)(0x40))   /*!< FIFO 1 overrun interrupt         */

/* Operating Mode Interrupts */
#define CAN_IER_WAKEUP             	  (uint32)(1<<16))  /*!< Wake-up interrupt                */
#define CAN_IER_SLEEP_ACK            	((uint32)(1<<17))  /*!< Sleep acknowledge interrupt      */

/* Error Interrupts */
#define CAN_IER_ERROR_WARNING        	((uint32)(1<<8 ))   /*!< Error warning interrupt          */
#define CAN_IER_ERROR_PASSIVE        	((uint32)(1<<9 ))   /*!< Error passive interrupt          */
#define CAN_IER_BUSOFF               	((uint32)(1<<10))   /*!< Bus-off interrupt                */
#define CAN_IER_LAST_ERROR_CODE      	((uint32)(1<<11))   /*!< Last error code interrupt        */
#define CAN_IER_ERROR                	((uint32)(1<<15))   /*!< Error Interrupt                  */


/**
 * =============================================================================================
 *     					### CAN ERROR definition
 *=============================================================================================
 **/

/** @defgroup CAN_Error_Code CAN Error Code **/
#define CAN_ERROR_NONE            (0x00000000U)  /*!< No error                                             */
#define CAN_ERROR_EWG             (0x00000001U)  /*!< Protocol Error Warning                               */
#define CAN_ERROR_EPV             (0x00000002U)  /*!< Error Passive                                        */
#define CAN_ERROR_BOF             (0x00000004U)  /*!< Bus-off error                                        */
#define CAN_ERROR_STF             (0x00000008U)  /*!< Stuff error                                          */
#define CAN_ERROR_FOR             (0x00000010U)  /*!< Form error                                           */
#define CAN_ERROR_ACK             (0x00000020U)  /*!< Acknowledgment error                                 */
#define CAN_ERROR_BR              (0x00000040U)  /*!< Bit recessive error                                  */
#define CAN_ERROR_BD              (0x00000080U)  /*!< Bit dominant error                                   */
#define CAN_ERROR_CRC             (0x00000100U)  /*!< CRC error                                            */
#define CAN_ERROR_RX_FOV0         (0x00000200U)  /*!< Rx FIFO0 overrun error                               */
#define CAN_ERROR_RX_FOV1         (0x00000400U)  /*!< Rx FIFO1 overrun error                               */
#define CAN_ERROR_TX_ALST0        (0x00000800U)  /*!< TxMailbox 0 transmit failure due to arbitration lost */
#define CAN_ERROR_TX_TERR0        (0x00001000U)  /*!< TxMailbox 0 transmit failure due to transmit error    */
#define CAN_ERROR_TX_ALST1        (0x00002000U)  /*!< TxMailbox 1 transmit failure due to arbitration lost */
#define CAN_ERROR_TX_TERR1        (0x00004000U)  /*!< TxMailbox 1 transmit failure due to transmit error    */
#define CAN_ERROR_TX_ALST2        (0x00008000U)  /*!< TxMailbox 2 transmit failure due to arbitration lost */
#define CAN_ERROR_TX_TERR2        (0x00010000U)  /*!< TxMailbox 2 transmit failure due to transmit error    */


/**
 * =============================================================================================
 *     					### CAN structures definition
 *=============================================================================================
 **/
/** CAN Tx message header structure definition **/
typedef struct
{
  uint32 StdId;    /*!< Specifies the standard identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF. */

  uint32 ExtId;    /*!< Specifies the extended identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF. */

  uint32 IDE;      /*!< Specifies the type of identifier for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_identifier_type */

  uint32 RTR;      /*!< Specifies the type of frame for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_remote_transmission_request */

  uint32 DLC;      /*!< Specifies the length of the frame that will be transmitted.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 8. */

  uint8 TransmitGlobalTime; 	/*!< Specifies whether the time stamp counter value captured on start
									of frame transmission, is sent in DATA6 and DATA7 replacing pData[6] and pData[7].
									@note: Time Triggered Communication Mode must be enabled.
									@note: DLC must be programmed as 8 bytes, in order these 2 bytes are sent.
									This parameter can be set to ENABLE or DISABLE. */
} CAN_TxHeaderTypeDef;

/** CAN Rx message header structure definition **/
typedef struct
{
  uint32 StdId;    /*!< Specifies the standard identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x7FF. */

  uint32 ExtId;    /*!< Specifies the extended identifier.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0x1FFFFFFF. */

  uint32 IDE;      /*!< Specifies the type of identifier for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_identifier_type */

  uint32 RTR;      /*!< Specifies the type of frame for the message that will be transmitted.
                          This parameter can be a value of @ref CAN_remote_transmission_request */

  uint32 DLC;      /*!< Specifies the length of the frame that will be transmitted.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 8. */

  uint32 TimeStamp; /*!< Specifies the timestamp counter value captured on start of frame reception.
                          @note: Time Triggered Communication Mode must be enabled.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0xFFFF. */

  uint32 FilterMatchIndex; /*!< Specifies the index of matching acceptance filter element.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0xFF. */

} CAN_RxHeaderTypeDef;


/**
  * @brief  CAN filter configuration structure definition
  */
typedef struct
{
  uint32 FilterIdHigh;          /*!< Specifies the filter identification number (MSBs for a 32-bit
                                       configuration, first one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  uint32 FilterIdLow;           /*!< Specifies the filter identification number (LSBs for a 32-bit
                                       configuration, second one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  uint32 FilterMaskIdHigh;      /*!< Specifies the filter mask number or identification number,
                                       according to the mode (MSBs for a 32-bit configuration,
                                       first one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  uint32 FilterMaskIdLow;       /*!< Specifies the filter mask number or identification number,
                                       according to the mode (LSBs for a 32-bit configuration,
                                       second one for a 16-bit configuration).
                                       This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF. */

  uint32 FilterFIFOAssignment;  /*!< Specifies the FIFO (0 or 1U) which will be assigned to the filter.
                                       This parameter can be a value of @ref CAN_filter_FIFO */

  uint32 FilterBank;            /*!< Specifies the filter bank which will be initialized.
                                       For single CAN instance(14 dedicated filter banks),
                                       this parameter must be a number between Min_Data = 0 and Max_Data = 13. */

  uint32 FilterMode;            /*!< Specifies the filter mode to be initialized.
                                       This parameter can be a value of @ref CAN_filter_mode */

  uint32 FilterScale;           /*!< Specifies the filter scale.
                                       This parameter can be a value of @ref CAN_filter_scale */

  uint32 FilterActivation;      /*!< Enable or disable the filter.
   	   	   	   	   	   	   	   	   	   	This parameter can be a value of @ref CAN_Activation */

} CAN_FilterTypeDef;

/***************   Function definition    ******************/

void CAN_voidInit(void);
void CAN_voidStart(void);
void CAN_voidAddTxMsg( CAN_TxHeaderTypeDef *pTxHeader, uint8 Local_u8Data[]);
void CAN_voidGetRxMsg(uint32 local_u8RxFifo, CAN_RxHeaderTypeDef *pRxHeader, uint8 Local_u8Data[]);
uint8 CAN_voidRXPending(uint8 local_u8RxFifo);
void CAN_voidConfigFilter( CAN_FilterTypeDef *pFilterConfig);

uint32 CAN_voidGetErrorCode(void);

 /********************** Interrupt functions *******************/

void CAN_voidInitInterput(IRQn_Type IRQn);
void CAN_voidDeinterputInit(IRQn_Type IRQn);
void CAN_voidEnableInterrupt(uint32 local_u32ActiveITs);
void CAN_voidDisableInterrupt(uint32 local_u32ActiveITs);

void CAN_voidRX_FIFO0_Interrupt_Handler(void);
void CAN_voidRX_FIFO1_Interrupt_Handler(void);
void CAN_voidSCE_Interrupt_Handler(void); /* Status Change Error Interrupt Handler */

/*************	 Callbacks functions 	************************/

void CAN_TxMailbox0CompleteCallback();
void CAN_TxMailbox1CompleteCallback();
void CAN_TxMailbox2CompleteCallback();
void CAN_TxMailbox0AbortCallback();
void CAN_TxMailbox1AbortCallback();
void CAN_TxMailbox2AbortCallback();
void CAN_RxFifo0MsgPendingCallback();
void CAN_RxFifo0FullCallback();
void CAN_RxFifo1MsgPendingCallback();
void CAN_RxFifo1FullCallback();
void CAN_SleepCallback();
void CAN_WakeUpFromRxMsgCallback();
void CAN_ErrorCallback();


#endif /* CAN_INTERFACE_H */
