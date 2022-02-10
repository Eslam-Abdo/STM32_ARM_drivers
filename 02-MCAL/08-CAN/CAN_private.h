/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 17 OCT  2020                                                      */
/*********************************************************************************/
#ifndef CAN_PRIVATE_H
#define CAN_PRIVATE_H

typedef void (*CAN_Interrupt_Callbacks)(void);/**  CAN Operating Mode **/


#define CAN_MODE_NORMAL           			  ((uint32)(0x0))                        			       /*!< Normal mode   */
#define CAN_MODE_LOOPBACK        		 	  ((uint32)(0x1<<30))                					   /*!< Loopback mode BIT 30 < 0x40000000 > */
#define CAN_MODE_SILENT            			  ((uint32)(0x1<<31))                					   /*!< Silent mode  BIT 31 < 0x80000000 > */
#define CAN_MODE_SILENT_LOOPBACK  			  ((uint32)(CAN_MODE_LOOPBACK | CAN_MODE_SILENT)) 	 	   /*!< Loopback combined with silent mode */


/*******************   BoudRate Definition     ***********************/
enum BITRATE{CAN_50KBPS, CAN_100KBPS, CAN_125KBPS, CAN_250KBPS, CAN_500KBPS, CAN_800KBPS, CAN_1MBPS};

typedef const struct
{
	uint8 TS2;
	uint8 TS1;
	uint8 BRP;
} CAN_BitTimingConfig;

/******** BoudRate value rating to table at web site {http://www.bittiming.can-wiki.info/}
 * 1. select ST Microelectronics bxCAN
 * 2. put freq with 36Mhz (APB1 freq)
 * 3. click Request Table						        ***********************************/
CAN_BitTimingConfig CAN_bitRateConfig[7] = {{2, 13, 45}, {2, 15, 20}, {2, 13, 18}, {2, 13, 9}, {2, 15, 4},{2, 12, 3}, {2, 15, 2}};


/*******************   Register Definition     ***********************/

/** Controller Area Network TxMailBox **/

typedef struct
{
  volatile uint32 TIR;
  volatile uint32 TDTR;
  volatile uint32 TDLR;
  volatile uint32 TDHR;

} CAN_TxMailBox_TypeDef;

/** Controller Area Network FIFOMailBox **/

typedef struct
{
  volatile uint32 RIR;
  volatile uint32 RDTR;
  volatile uint32 RDLR;
  volatile uint32 RDHR;
} CAN_FIFOMailBox_TypeDef;

/** Controller Area Network FilterRegister **/

typedef struct
{
  volatile uint32 FR1;
  volatile uint32 FR2;
} CAN_FilterRegister_TypeDef;

/** Controller Area Network  **/
typedef struct
{
	volatile uint32 MCR;
	volatile uint32 MSR;
	volatile uint32 TSR;
	volatile uint32 RF0R;
	volatile uint32 RF1R;
	volatile uint32 IER;
	volatile uint32 ESR;
	volatile uint32 BTR;
	uint32 RESERVED0[88];
	CAN_TxMailBox_TypeDef TxMailBox[3];
    CAN_FIFOMailBox_TypeDef FIFOMailBox[2];
    uint32  RESERVED1[12];
    volatile uint32 FMR;
    volatile uint32 FM1R;
    uint32  RESERVED2;
    volatile uint32 FS1R;
    uint32  RESERVED3;
    volatile uint32 FFA1R;
    uint32  RESERVED4;
    volatile uint32 FA1R;
    uint32  RESERVED5[8];
    CAN_FilterRegister_TypeDef FilterBankRegister[14];

}CAN_t;

/*******************   BASE Address Definition    *********************/
#define CAN_BASE_ADDRESS	0x40006400 		//define the boundary address of CAN
#define CAN			((volatile CAN_t *) CAN_BASE_ADDRESS)





#endif /* CAN_PRIVATE_H */
