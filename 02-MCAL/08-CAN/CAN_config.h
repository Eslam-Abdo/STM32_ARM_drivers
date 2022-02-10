/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#ifndef CAN_CONFIG_H
#define CAN_CONFIG_H



/** CAN  configuration structure definition **/

 /*!< This parameters can be set to ENABLE or DISABLE. */
#define AutoRetransmission           ENABLE
#define AutoBussOff                  ENABLE
#define AutoWakeUp                   DISABLE
#define TimeTriggeredMode            DISABLE
#define ReceiveFifoLocked            DISABLE
#define TransmitFifoPriority         DISABLE

/********** option : 
 * 					 CAN_MODE_NORMAL
 * 					 CAN_MODE_LOOPBACK
 * 					 CAN_MODE_SILENT
 * 					 CAN_MODE_SILENT_LOOPBACK
 	 	 	 	 	 	 	 	 	 	 	 	 **********************************/
#define MODE			 CAN_MODE_NORMAL
/********** option : CAN_50KBPS
 * 					 CAN_100KBPS
 * 					 CAN_125KBPS
 * 					 CAN_250KBPS
 * 					 CAN_500KBPS
 * 					 CAN_800KBPS,
 * 					 CAN_1MBPS
 	 	 	 	 	 	 	 	 	 	 	 	 *************************/
#define BOUDRATE		CAN_500KBPS


#endif /* CAN_CONFIG_H */
