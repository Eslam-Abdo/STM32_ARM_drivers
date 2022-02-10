/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 1  FEB  2021                                                      */
/*********************************************************************************/

/******************** 			CAN 		   ***********************************/
#include <stdio.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "STK_interface.h"
#include "NVIC_interface.h"
#include "GPIO_interface.h"
#include "EXTI_interface.h"
#include "USART_INTERFACE.h"
#include "CAN_interface.h"

#define BUTTON   PIN0
#define LED1   	 PIN12
#define LED2   	 PIN13
#define LED3   	 PIN14
#define LED4   	 PIN15
#define Blink  	 PIN13

uint8 LedNum = 11;
uint8 counter = 0;

void GPIO_init(void);
void EXTI_voidCallBack(void);
void EXTI_void__Init(void);
void Timer(void);

void CAN_TX(void);
void CAN_RX(void);
uint16 Std_id_High(uint16 local_u16Std_Id);
void CAN_FilterConfig(void);
void CAN_Interrupt(void);

void LED_Mange_Output(uint8 local_u8LedNum);
void Send_response(uint32 stdId);


int main()
{


	/* Rcc init */
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2, APB2_GPIOA_EN);
	RCC_voidEnableClock(RCC_APB2, APB2_GPIOB_EN);
	RCC_voidEnableClock(RCC_APB2, APB2_GPIOC_EN);
	RCC_voidEnableClock(RCC_APB2, APB2_USART1_EN);
	/* STK init */
	STK_voidInit();
	/* GPIOA INIT */
	GPIO_init();
	/* UART1 init */
	USART_voidInit(UART1,9600);
	/* CAN init */
	CAN_voidInit();
	/* CAN Filter set */
	CAN_FilterConfig();
	CAN_Interrupt();
	/* CAN Start */
	CAN_voidStart();
	/* EXTI init */
	EXTI_void__Init();



	while(1)
	{

	}
	return 0;
}


void GPIO_init(void)
{
	GPIO_voidSetPinDirection(GPIOA,BUTTON,INPUT_PULL_UP_DOWN);
	GPIO_voidSetPinPull(GPIOA,BUTTON, PULL_UP);

	GPIO_voidSetPinDirection(GPIOC,Blink,OUTPUT_SPEED_2MHZ_PP);

	GPIO_voidSetPinDirection(GPIOB,LED1,OUTPUT_SPEED_2MHZ_PP);
	GPIO_voidSetPinDirection(GPIOB,LED2,OUTPUT_SPEED_2MHZ_PP);
	GPIO_voidSetPinDirection(GPIOB,LED3,OUTPUT_SPEED_2MHZ_PP);
	GPIO_voidSetPinDirection(GPIOB,LED4,OUTPUT_SPEED_2MHZ_PP);
}

void EXTI_void__Init(void)
{
	EXTI_voidSetCallBack(EXTI_LINE0,EXTI_voidCallBack);
	EXTI_voidSetSignalLatch(EXTI_LINE0, FALLING_EDGE);
	NVIC_voidEnableInterrupt(6);
}


void EXTI_voidCallBack(void)
{
	STK_voidSetIntervalPeriodic(9000*1000,Timer);//take us and with 72MHz 1ms = 9000
}
void Timer(void)
{
	if (counter == 4)
	{
		uint8 T_MSG[8];
		CAN_TxHeaderTypeDef tx_header;
		tx_header.ExtId = 0x651;
		tx_header.IDE = CAN_ID_EXT;
		tx_header.RTR = CAN_RTR_REMOTE;
		tx_header.DLC = 2;
		tx_header.TransmitGlobalTime=DISABLE;

		CAN_voidAddTxMsg(&tx_header,T_MSG);
		counter = 0;
	}
	else
	{
		CAN_TX();
		counter ++;
	}
}



void CAN_TX(void)
{
	CAN_TxHeaderTypeDef tx_header;
	uint8 T_MSG;

	tx_header.ExtId = 0x65D;
	tx_header.IDE = CAN_ID_EXT;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 1;
	tx_header.TransmitGlobalTime=DISABLE;

	T_MSG = ++LedNum;
	if (LedNum == 15)
	{
		LedNum = 11;
	}
	CAN_voidAddTxMsg(&tx_header,&T_MSG);
	GPIO_voidTogglePinValue(GPIOC,Blink);
}

void CAN_RX(void)
{
	CAN_RxHeaderTypeDef Rx_header;
//	while(CAN_voidRXPending(CAN_RX_FIFO0) == 0);
	uint8 R_MSG[8];
	char MSG[50];

	CAN_voidGetRxMsg(CAN_RX_FIFO0,&Rx_header,R_MSG);

	if(Rx_header.ExtId == 0x65D && Rx_header.RTR == CAN_RTR_DATA)
	{
		// This is data frame sent by n1 to n2
		LED_Mange_Output(R_MSG[0]);
		sprintf(MSG,"MSG Recevied : #%x \n",R_MSG[0] );
	}
	else if(Rx_header.ExtId == 0x651 && Rx_header.RTR == CAN_RTR_REMOTEFLAG)
	{
		// This is remote frame sent by n1 to n2
		Send_response(Rx_header.ExtId);
		return;
	}
	else if(Rx_header.ExtId == 0x651 && Rx_header.RTR == CAN_RTR_DATA)
	{
		// This is  replay (data frame )sent by n2 to n1
		sprintf(MSG,"MSG Recevied : #%x \n",R_MSG[0]<<8 | R_MSG[1]);

	}
	USART_voidTransmit(UART1,MSG, STRING);

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
	CAN_FilterInit.FilterIdHigh = 0x0000;
	CAN_FilterInit.FilterIdLow = 0x651<<3|0x04;
	CAN_FilterInit.FilterMaskIdHigh = 0x0000;
	CAN_FilterInit.FilterMaskIdLow = 0x7FFC;
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



void LED_Mange_Output(uint8 local_u8LedNum)
{
	switch(local_u8LedNum)
	{
	case 12:
		GPIO_voidSetPinValue(GPIOB,LED1,HIGH);
		GPIO_voidSetPinValue(GPIOB,LED2,LOW);
		GPIO_voidSetPinValue(GPIOB,LED3,LOW);
		GPIO_voidSetPinValue(GPIOB,LED4,LOW);
		break;
	case 13:
		GPIO_voidSetPinValue(GPIOB,LED1,LOW);
		GPIO_voidSetPinValue(GPIOB,LED2,HIGH);
		GPIO_voidSetPinValue(GPIOB,LED3,LOW);
		GPIO_voidSetPinValue(GPIOB,LED4,LOW);
		break;
	case 14:
		GPIO_voidSetPinValue(GPIOB,LED1,LOW);
		GPIO_voidSetPinValue(GPIOB,LED2,LOW);
		GPIO_voidSetPinValue(GPIOB,LED3,HIGH);
		GPIO_voidSetPinValue(GPIOB,LED4,LOW);
		break;
	case 15:
		GPIO_voidSetPinValue(GPIOB,LED1,LOW);
		GPIO_voidSetPinValue(GPIOB,LED2,LOW);
		GPIO_voidSetPinValue(GPIOB,LED3,LOW);
		GPIO_voidSetPinValue(GPIOB,LED4,HIGH);
		break;
	}
}

void Send_response(uint32 stdId)
{
	CAN_TxHeaderTypeDef tx_header;
	uint8 Response_MSG[2]={0xAB,0xCD};

	tx_header.ExtId = stdId;
	tx_header.IDE = CAN_ID_EXT;
	tx_header.RTR = CAN_RTR_DATA;
	tx_header.DLC = 2;
	tx_header.TransmitGlobalTime=DISABLE;

	CAN_voidAddTxMsg(&tx_header,Response_MSG);
	GPIO_voidTogglePinValue(GPIOC,Blink);
}



/**************************************************/
void CAN_TxMailbox0CompleteCallback()
{
	/* print MSG on UART1 */
	char MSG[50] = " MSG TRANSMITED m0 \n";
	USART_voidTransmit(UART1,MSG, STRING);
}

void CAN_RxFifo0MsgPendingCallback()
{
	CAN_RX();
}

void CAN_ErrorCallback()
{
	/* print MSG on UART1 */
	char MSG[50] = "Error Code \n";
	USART_voidTransmit(UART1,MSG, STRING);
}
