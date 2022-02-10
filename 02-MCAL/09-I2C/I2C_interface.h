/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 7 JUN  2021                                                       */
/*********************************************************************************/

#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

#define MI2C1 1
#define MI2C2 2


#define STD_MODE 2
#define FAST_MODE 3

/******************************************************************************/
/*                                                                            */
/*                                I2C                                         */
/*                        Register Bit Defininitions                          */
/******************************************************************************/

/*******************  Bit definition for I2C_CR1 register  ********************/

#define I2C_REG_CR1_POS					11

#define I2C_REG_CR1_ACK					10
#define I2C_ACK_ENABLE      			1
#define I2C_ACK_DISABLE      			0

#define I2C_REG_CR1_STOP_GEN             9
#define I2C_REG_CR1_START_GEN            8

#define I2C_REG_CR1_NOSTRETCH            7
#define I2C_ENABLE_CLK_STRETCH  		 0
#define I2C_DISABLE_CLK_STRETCH 		 1

#define I2C_REG_CR1_ENABLE_I2C           0

/*******************  Bit definition for I2C_CR2 register  ********************/
#define I2C_REG_CR2_BUF_INT_ENABLE       10
#define I2C_REG_CR2_EVT_INT_ENABLE       9
#define I2C_REG_CR2_ERR_INT_ENABLE       8

#define I2C_PERIPHERAL_CLK_FREQ_36MHZ    ((u32)36 )  
 

/*******************  Bit definition for I2C_OAR1 register  ********************/
#define I2C_REG_OAR1_ADDRMODE       	 15
#define I2C_ADDRMODE_7BIT         		 0
#define I2C_ADDRMODE_10BI        		 1


/*******************  Bit definition for I2C_SR1 register  ********************/
#define I2C_REG_SR1_TIMEOUT_FLAG         14
#define I2C_REG_SR1_OVR_FLAG             11
#define I2C_REG_SR1_AF_FAILURE_FLAG      10
#define I2C_REG_SR1_ARLO_FLAG            9
#define I2C_REG_SR1_BUS_ERROR_FLAG       8
#define I2C_REG_SR1_TXE_FLAG             7
#define I2C_REG_SR1_RXNE_FLAG            6
#define I2C_REG_SR1_STOP_DETECTION_FLAG  4 /*  for slave */
#define I2C_REG_SR1_BTF_FLAG             2
#define I2C_REG_SR1_ADDR_FLAG            1	
#define I2C_REG_SR1_ADDR_SENT_FLAG       1   //For master 
#define I2C_REG_SR1_ADDR_MATCHED_FLAG    1  //For SLAVE 	
#define I2C_REG_SR1_SB_FLAG              0	

/*******************  Bit definition for I2C_SR2 register  ********************/
#define I2C_REG_SR2_BUS_BUSY_FLAG        1	
#define I2C_BUS_IS_BUSY                  1
#define I2C_BUS_IS_FREE                  0

#define I2C_REG_SR2_MSL_FLAG           	 0	
#define I2C_MASTER_MODE        	         1
#define I2C_SLAVE_MODE                   0

#define I2C_REG_SR2_TRA_FLAG       		 2	
#define I2C_RX_MODE                   	 0
#define I2C_TX_MODE                      1

/*******************  Bit definition for I2C_CCR register  ********************/
#define I2C_REG_CCR_ENABLE_FM            15
#define I2C_ENABLE_SM                    0 
#define I2C_ENABLE_FM                    1

#define I2C_REG_CCR_DUTY                 14
#define I2C_FM_DUTY_16BY9                1
#define I2C_FM_DUTY_2                    0
/*******************  Bit definition for I2C_DR register  ********************/
#define I2C_ADDREES_READ				 1
#define I2C_ADDREES_WRITE				 0


/******************************************************************************/
/*                                                                            */
/*                      Driver exposed APIs                                   */
/*                                                                            */
/******************************************************************************/

void I2C_generate_start_condition(u8 I2C_Type);
	
void I2C_generate_stop_condition(u8 I2C_Type);

void I2C_init(u8 I2C_Type,u32 I2C_CLOCK, u16 OwnAddress1);

void I2C_master_tx(u8 I2C_Type,u8 address,u8* data,u8 len);
void I2C_master_rx(u8 I2C_Type, u16 address, u8 *pData, u8 len);

void I2C_slave_tx(u8 I2C_Type,u8* data,u8 len);
void I2C_slave_rx(u8 I2C_Type,u8* buff, u8 len);

void I2C_slave_Check_StopBit(u8 I2C_Type);

/******************************************************************************/
/*                                                                            */
/*                      static function			                                  */
/*                                                                            */
/******************************************************************************/

static void I2C_enable_peripheral(void);
static void I2C_disable_peripheral(void);
static void I2C_rest_peripheral(void);

static void I2C_set_addressing_mode( u32 adr_mode);
static void I2C_set_own_address1( u32 own_address);
static void I2C_send_addr_first( u8 address, u8 addr_type);

static void I2C_manage_clock_stretch( u32 no_stretch);

static void I2C_configure_ccr( u32 pclk, u32 clkspeed, u32 duty_cycle);
static void I2C_rise_time_configuration(u32 pclk, u32 ClockSpeed);
static void I2C_set_clk_mode(u8 I2C_Mode);
static void I2C_set_fm_mode_duty_cycle(u32 duty_cycle);
static void I2C_clk_init ( u32 clkspeed, u32 duty_cycle);


static void I2C_manage_ack( u32 ack_noack);

static u8 is_bus_busy(void);
static u8 i2c_wait_untill_sb_set(void);
static u8 i2c_wait_untill_addr_set(void);

static void clear_addr_flag(void);
static void clear_stop_flag(void);

	 
#endif /* I2C_INTERFACE_H */
