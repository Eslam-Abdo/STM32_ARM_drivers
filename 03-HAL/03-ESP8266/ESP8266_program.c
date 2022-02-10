/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 9  MAY 2021                                                       */
/*********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <string.h>

#include "STK_interface.h"
#include "USART_interface.h"

#include "ESP8266_interface.h"
#include "ESP8266_config.h"
#include "ESP8266_private.h"


/**
 * AT Commands:
 1* AT		>> TEST
 2* ATE0		>> STOP ECHO
 3* AT+CWMODE=1 		>>SET STATION MODE
 4* AT+CWJAP="SSID","PASSWORD" 		>> CONNECT TO WIFI
 5* AT+CIPSTART="TCP","IP",80 				>> *replace ip with the website ip* to start connect on server
 6* AT+CIPSEND=numOfBits+1		>>*replace numOfBits with number of http link bits* sto send data
 7* GET http://iot-arm.freevar.com/status.txt	>> put link of website
 * >>> rebeat again from line num 7 OF "AT+CIPSTART" because connection will closed after recive data
 * **note you recive data as form:
 * 		+IPD,LengthOfData:content....CLOSED
 */

uint8 volatile Iterator;
uint8 volatile  DataCome[200];

void ESP8266_voidInit(void)
{
	USART_voidInit(UART1,115200);
	STK_voidInit();
	/* Sending AT Command To Check ESP8266 Is Working Or Not  */
	ESP8266_voidSendCmd("AT\r\n");
	/* Clear ESP8266 Buffer */
	ESP8266_voidClearBuffer();

	/* Stop ECHO */
	ESP8266_voidSendCmd("ATE0\r\n");
	/* Clear ESP8266 Buffer */
	ESP8266_voidClearBuffer();

	/* Set station mode */
	ESP8266_voidSendCmd("AT+CWMODE=1\r\n");
	/* Clear ESP8266 Buffer */
	ESP8266_voidClearBuffer();


}


void ESP8266_voidConnectToWiFi(uint8* SSID , uint8 * Password )
{
	/* Clear ESP8266 Buffer */
	ESP8266_voidClearBuffer();
	ESP8266_voidSendCmd(("AT+CWJAP=" + SSID +',' + Password + "\r\n"),8000);


}






uint8 ESP8266_u8ValidateCmd(void)
{

	uint8 Dummy = 0;

	while (Dummy!=255)
	{
		Dummy = USART_charReceive(UART1);
		DataCome[Iterator] = Dummy;
		Iterator++;
	}
	/* check if receive ok */
	if(DataCome[Iterator-3] == 'O' && DataCome[Iterator-2] == 'K') /* .... ok\n */
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

void ESP8266_voidClearBuffer ( void ){

	u8 LOC_u8Iterator1 = 0 ;
	Iterator     = 0 ;

	for( LOC_u8Iterator1 = 0 ; LOC_u8Iterator1 < 150 ; LOC_u8Iterator1++ ){

		DataCome[ LOC_u8Iterator1 ] = 0 ;

	}

}

void ESP8266_voidSendCmd(uint8* cmd,uint8 delay = 500)
{
	u8 Local_u8Result = 0;
	while(Local_u8Result == 1)
	{
		USART_voidTransmit(UART1,&cmd,STRING);
		STK_voidDelay_ms(delay);
		Local_u8Result = ESP8266_u8ValidateCmd;
	}
}
