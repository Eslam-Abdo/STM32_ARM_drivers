/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 1  FEB  2021                                                      */
/*********************************************************************************/

/******************** 			CAN 		   ***********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_INTERFACE.h"
#include "CAN_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"

void CAN_TX(void)
{
	CAN_TxHeaderTypeDef tx_header;
	tx_header.StdId = 0x65d;
	tx_header.IDE = CAN_ID_STD;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 8;
	tx_header.TransmitGlobalTime=DISABLE;
	uint8 DATA[5] = {'h','e','l','l','o'};

	CAN_TxHeaderTypeDef tx_header1;
	tx_header1.StdId = 0x65F;
	tx_header1.IDE = CAN_ID_STD;
	tx_header1.RTR = CAN_RTR_DATA;
	tx_header1.DLC = 8;
	uint8 DATA1[5] = {'O','M','A','R'};

	CAN_voidAddTxMsg(&tx_header,DATA);
	CAN_voidAddTxMsg(&tx_header1,DATA1);
}
void CAN_RX(void)
{
	CAN_RxHeaderTypeDef Rx_header;
	//while(CAN_voidRXPending(CAN_RX_FIFO0) == 0);
	uint8 DATA[5];
	CAN_voidGetRxMsg(CAN_RX_FIFO0,&Rx_header,DATA);
	USART_voidTransmit(UART1,DATA,STRING);
	USART_voidTransmit(UART1,"\n",STRING);;
}
uint16 Std_id_High(uint16 local_u16Std_Id)
{
	return (local_u16Std_Id << 5);
}
void CAN_FilterConfig(void)
{
	CAN_FilterTypeDef CAN_FilterInit;
	CAN_FilterInit.FilterActivation = ENABLE;
	CAN_FilterInit.FilterBank = 0;
	CAN_FilterInit.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	CAN_FilterInit.FilterIdHigh = Std_id_High(0x65d);
	CAN_FilterInit.FilterIdLow = 0x0000;
	CAN_FilterInit.FilterMaskIdHigh = 0x0000;
	CAN_FilterInit.FilterMaskIdLow = 0x0000;
	CAN_FilterInit.FilterMode = CAN_FILTERMODE_IDMASK;
	CAN_FilterInit.FilterScale = CAN_FILTERSCALE_32BIT;

	CAN_voidConfigFilter(&CAN_FilterInit);
}

void CAN_Interrupt(void)
{
	CAN_voidInitInterput(CAN_TX_IRQn);
	CAN_voidInitInterput(CAN_RX0_IRQn);
	CAN_voidInitInterput(CAN_RX1_IRQn);
	CAN_voidInitInterput(CAN_SCE_IRQn);

	CAN_voidEnableInterrupt(CAN_IER_TX_MAILBOX_EMPTY | CAN_IER_RX_FIFO0_MSG_PENDING | CAN_IER_ERROR | CAN_IER_LAST_ERROR_CODE | CAN_IER_BUSOFF);
}

void CAN_TxMailbox0CompleteCallback()
{
	/* print MSG on UART1 */
	char MSG[50] = " MSG TRANSMITED m0 \n";
	USART_voidTransmit(UART1,MSG,STRING);
	//NVIC_voidSetPendingFlag(CAN_TX_IRQn);
}
void CAN_RxFifo0MsgPendingCallback()
{
	CAN_RX();
	//NVIC_voidSetPendingFlag(CAN_RX0_IRQn);
}
void CAN_ErrorCallback()
{
	/* print MSG on UART1 */
	char MSG[50] = "Error Code \n";
	u32 x= CAN_voidGetErrorCode();
	USART_voidTransmit(UART1,&x,INT);
	USART_voidTransmit(UART1,"\n",STRING);
}

int main()
{

	/* Rcc init */
	RCC_voidInitSysClock();
	/* UART1 init */
	RCC_voidEnableClock(RCC_APB2,14);
	RCC_voidEnableClock(RCC_APB2,2);
	USART_voidInit(UART1,9600);
	/* CAN init */
	CAN_voidInit();
	/* CAN Filter set */
	CAN_FilterConfig();
	CAN_Interrupt();
	/* CAN Start */
	CAN_voidStart();
	

	while(1)
	{
  /* CAN send Tx */
	CAN_TX();
  //CAN_RX();
  
		STK_voidDelay_ms(1000);
	}
	return 0;
}
