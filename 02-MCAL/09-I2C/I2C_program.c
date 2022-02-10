/*********************************************************************************/
/* Author    : Islam Abdo                                                        */
/* Version   : V01                                                               */
/* Date      : 7 JUN  2021                                                       */
/*********************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "I2C_private.h"
#include "I2C_config.h"
#include "I2C_interface.h"

volatile I2C_t *i2cx;


void I2C_generate_start_condition(u8 I2C_Type)
{
	if(I2C_Type == MI2C1)
	{
		i2cx = I2C1;
	}else if(I2C_Type == MI2C2)
	{
		i2cx = I2C2;
	}
	SET_BIT(i2cx->CR1, I2C_REG_CR1_START_GEN);
}

void I2C_generate_stop_condition(u8 I2C_Type)
{
	if(I2C_Type == MI2C1)
	{
		i2cx = I2C1;
	}else if(I2C_Type == MI2C2)
	{
		i2cx = I2C2;
	}
	SET_BIT(i2cx->CR1, I2C_REG_CR1_STOP_GEN);	
}

void I2C_slave_Check_StopBit(u8 I2C_Type)
{
	if(I2C_Type == MI2C1)
	{
		i2cx = I2C1;
	}else if(I2C_Type == MI2C2)
	{
		i2cx = I2C2;
	}
	 // for slave rx , with ACK
		while( GET_BIT(i2cx->SR1, I2C_REG_SR1_STOP_DETECTION_FLAG) == 0);
		clear_stop_flag();
	
}

void I2C_init(u8 I2C_Type,u32 I2C_CLOCK, u16 OwnAddress1)
{
	if(I2C_Type == MI2C1)
	{
		i2cx = I2C1;
		/* GPIO init */
		GPIO_voidSetPinDirection(GPIOB,PIN6,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB6 and PB7 as alt. func. open drain */
		GPIO_voidSetPinDirection(GPIOB,PIN7,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB6 and PB7 as alt. func. open drain */	
		I2C_set_addressing_mode(I2C1_ADDRESSING);
		
	}else if(I2C_Type == MI2C2)
	{
		i2cx = I2C2;
		GPIO_voidSetPinDirection(GPIOB,PIN10,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB10 and PB11 as alt. func. open drain */
		GPIO_voidSetPinDirection(GPIOB,PIN11,OUTPUT_SPEED_50MHZ_AFOD); /* configure PB10 and PB11 as alt. func. open drain */
		I2C_set_addressing_mode(I2C2_ADDRESSING);
	}
	
	I2C_disable_peripheral();
	I2C_clk_init( I2C_CLOCK,I2C_FM_DUTY_2);
	I2C_set_addressing_mode(I2C1_ADDRESSING);
	I2C_manage_ack(I2C_ACK_ENABLE);
	I2C_manage_clock_stretch(I2C_ENABLE_CLK_STRETCH);
	I2C_set_own_address1(OwnAddress1);
	
	I2C_enable_peripheral();
}
 
void I2C_master_tx(u8 I2C_Type,u8 address,u8* data,u8 len)
{
	
	if(I2C_Type == MI2C1)
	{
		i2cx = I2C1;
	}else if(I2C_Type == MI2C2)
	{
		i2cx = I2C2;
	}
	
	//while( is_bus_busy() ); //need to include timeout
	
	 /* Disable Pos */
	CLR_BIT(i2cx->CR1, I2C_REG_CR1_POS);
	/* enable ACK */
	I2C_manage_ack(I2C_ACK_ENABLE);
	
	I2C_generate_start_condition(I2C_Type);
	
	/* wait till sb is set */
	
	while( ! i2c_wait_untill_sb_set() );
	
	//clear_sb_flag
	
	I2C_send_addr_first(address,I2C_ADDREES_WRITE);
	
	while ( ! i2c_wait_untill_addr_set() );
	
	clear_addr_flag();
	
	
 u8 size = len; /* reused in onther state */ 
	
	while(size>0)
	{
		u32 timeout = 0;
		while( ( GET_BIT(i2cx->SR1, I2C_REG_SR1_TXE_FLAG) == 0 ) && ( timeout < 100000 ) ) { timeout++; } /* wait TXE =1*/
		i2cx->DR = data[len - size];
		size--;
		if(( GET_BIT(i2cx->SR1,I2C_REG_SR1_BTF_FLAG) == 0 ) && ( size != 0 ) )//BTF
		{
			i2cx->DR = data[len - size];
			size--;
		}
		timeout = 0;
		while( ( GET_BIT(i2cx->SR1,I2C_REG_SR1_BTF_FLAG) == 0 ) && ( timeout < 100000 ) ) { timeout++; } //wait BTF (data send)
	}
  
}


void I2C_master_rx(u8 I2C_Type, u16 address, u8 *pData, u8 len)
{
	
	if(I2C_Type == MI2C1)
	{
		i2cx = I2C1;
	}else if(I2C_Type == MI2C2)
	{
		i2cx = I2C2;
	} 
	//	while( is_bus_busy() ); //need to include timeout
	
	/* Disable Pos */
	CLR_BIT(i2cx->CR1, I2C_REG_CR1_POS);
	/* enable ACK */
	I2C_manage_ack(I2C_ACK_ENABLE);
 

	/* Prepare transfer parameters */
	u8* pBuffPtr    = pData;
	u8 XferCount   = len;
	u8 XferSize    = XferCount;

	
	I2C_generate_start_condition(I2C_Type);
	
	/* wait till sb is set */
	
	while( ! i2c_wait_untill_sb_set() );
	
	//clear_sb_flag
	
	I2C_send_addr_first(address,I2C_ADDREES_READ);
	
	while ( ! i2c_wait_untill_addr_set() );
	
	
	
	/* ---------- Start Read Data -------------------- */
	
	
	if (XferSize == 0U)
	{
		/* Clear ADDR flag */
		clear_addr_flag();

		/* Generate Stop */
		I2C_generate_stop_condition(I2C_Type);
		
	}
	else if (XferSize == 1U)
	{
		/* Disable Acknowledge */
		I2C_manage_ack(I2C_ACK_DISABLE);

		/* Clear ADDR flag */
		clear_addr_flag();
	 
		/* Generate Stop */
		I2C_generate_stop_condition(I2C_Type);
		
	}
	else if (XferSize == 2U)
	{
		/* Enable Pos */
		SET_BIT(i2cx->CR1, I2C_REG_CR1_POS);

		/* Clear ADDR flag */
		clear_addr_flag();

		/* Disable Acknowledge */
		I2C_manage_ack(I2C_ACK_DISABLE);
		
	}
	else
	{ /* XferSize > 2U */
		
		/* Enable Acknowledge */
		I2C_manage_ack(I2C_ACK_ENABLE);

		/* Clear ADDR flag */
		clear_addr_flag();
	}

	while (XferSize > 0U)
	{
		if (XferSize <= 3U)
		{
			/* One byte */
			if (XferSize == 1U)
			{
				/* Wait until RXNE flag is set */
				while ( GET_BIT(i2cx->SR1,I2C_REG_SR1_RXNE_FLAG) == 0 );
				

				/* Read data from DR */
				*pBuffPtr = (u8)i2cx->DR;

				/* Increment Buffer pointer */
				pBuffPtr++;

				/* Update counter */
				XferSize--;
				XferCount--;
			}
			/* Two bytes */
			else if (XferSize == 2U)
			{
				/* Wait until BTF flag is set */
				 while (GET_BIT(i2cx->SR1,I2C_REG_SR1_BTF_FLAG) != 1);

				/* Generate Stop */
				I2C_generate_stop_condition(I2C_Type);

				/* Read data from DR */
				*pBuffPtr = (u8)i2cx->DR;

				/* Increment Buffer pointer */
				pBuffPtr++;

				/* Update counter */
				XferSize--;
				XferCount--;

				/* Read data from DR */
				*pBuffPtr = (u8)i2cx->DR;

				/* Increment Buffer pointer */
				pBuffPtr++;

				/* Update counter */
				XferSize--;
				XferCount--;
			}
			/* 3 Last bytes */
			else
			{
				/* Wait until BTF flag is set */
				u32 timeout=0;
			  while( ( GET_BIT(i2cx->SR1,I2C_REG_SR1_BTF_FLAG) == 0 ) && ( timeout < 100000 ) ) { timeout++; } 

				/* Disable Acknowledge */
				I2C_manage_ack(I2C_ACK_DISABLE);

				/* Read data from DR */
				*pBuffPtr = (u8)i2cx->DR;

				/* Increment Buffer pointer */
				pBuffPtr++;

				/* Update counter */
				XferSize--;
				XferCount--;

				timeout=0;
				/* Wait until BTF flag is set */
				while( ( GET_BIT(i2cx->SR1,I2C_REG_SR1_BTF_FLAG) == 0 ) && ( timeout < 100000 ) ) { timeout++; } 

				/* Generate Stop */
				SET_BIT(i2cx->CR1, 9);

				/* Read data from DR */
				*pBuffPtr = (u8)i2cx->DR;

				/* Increment Buffer pointer */
				pBuffPtr++;

				/* Update counter */
				XferSize--;
				XferCount--;

				/* Read data from DR */
				*pBuffPtr = (u8)i2cx->DR;

				/* Increment Buffer pointer */
				pBuffPtr++;

				/* Update counter */
				XferSize--;
				XferCount--;
			}
		}
		else /* XferSize > 3*/
		{ 
			/* Wait until RXNE flag is set */
			 while (GET_BIT(i2cx->SR1,I2C_REG_SR1_RXNE_FLAG) == 0 );


			/* Read data from DR */
			*pBuffPtr = (u8)i2cx->DR;

			/* Increment Buffer pointer */
			pBuffPtr++;

			/* Update counter */
			XferSize--;
			XferCount--;

		}
	}
}



void I2C_slave_tx(u8 I2C_Type,u8* data,u8 len)
{
	
	if(I2C_Type == MI2C1)
	{
		i2cx = I2C1;
	}else if(I2C_Type == MI2C2)
	{
		i2cx = I2C2;
	}
	
	//while( is_bus_busy() ); //need to include timeout
	 /* Disable Pos */
	CLR_BIT(i2cx->CR1, I2C_REG_CR1_POS);
	/* enable ACK */
	I2C_manage_ack(I2C_ACK_ENABLE);
	
	/* Wait until ADDR flag is set */	
	while(GET_BIT(i2cx->SR1,I2C_REG_SR1_ADDR_MATCHED_FLAG)==0);

	/* Clear ADDR flag */
	clear_addr_flag();
		
	if ( GET_BIT(i2cx->SR2, I2C_REG_SR2_TRA_FLAG ) == I2C_TX_MODE)
	{
		u8  size = len;
		while(size>0)
		{
			i2cx->DR = data[len-size];
			while( GET_BIT(i2cx->SR1 ,I2C_REG_SR1_TXE_FLAG) == 0 ); //waiting for TxE 			
			size--;
		}
	}
	if ( GET_BIT(i2cx->SR1,I2C_REG_SR1_AF_FAILURE_FLAG) == 1 ) //AF bit for tx
	{
		CLR_BIT(i2cx->SR1,I2C_REG_SR1_AF_FAILURE_FLAG); //clear AF bit
	}
}

void I2C_slave_rx(u8 I2C_Type,u8* buff, u8 len)
{
	
	if(I2C_Type == MI2C1)
	{
		i2cx = I2C1;
	}else if(I2C_Type == MI2C2)
	{
		i2cx = I2C2;
	}
	
	//while( is_bus_busy() ); //need to include timeout	
	 /* Disable Pos */
	CLR_BIT(i2cx->CR1, I2C_REG_CR1_POS);
	/* enable ACK */
	I2C_manage_ack(I2C_ACK_ENABLE);
	
	/* Wait until ADDR flag is set */	
	while(GET_BIT(i2cx->SR1,I2C_REG_SR1_ADDR_MATCHED_FLAG)==0);

	/* Clear ADDR flag */
	clear_addr_flag();
	if ( GET_BIT(i2cx->SR2, I2C_REG_SR2_TRA_FLAG ) == I2C_RX_MODE)
	{
		u8  size = len;
		while(size>0)
		{
			while( GET_BIT(i2cx->SR1, I2C_REG_SR1_RXNE_FLAG ) == 0 );  //waiting for RxNE 
			buff[len-size] = i2cx->DR;
			size--;
		}
	}				
}




static void I2C_enable_peripheral(void)
{
	SET_BIT(i2cx->CR1, I2C_REG_CR1_ENABLE_I2C);
}

static void I2C_disable_peripheral(void)
{
	CLR_BIT(i2cx->CR1, I2C_REG_CR1_ENABLE_I2C);
	
}

static void I2C_rest_peripheral(void)
{
	SET_BIT(i2cx->CR1,15);// SWRST: Software reset
	CLR_BIT(i2cx->CR1,15);// SWRST: Software reset
}

static void I2C_set_own_address1( u32 own_address)
{
	i2cx->OAR1 &= ~( 0x7f << 1);
	i2cx->OAR1 |=  (own_address << 1);
}


static void I2C_manage_clock_stretch( u32 no_stretch)
{
	if(no_stretch)
	{
		SET_BIT(i2cx->CR1,I2C_REG_CR1_NOSTRETCH);
	}else
	{
		CLR_BIT(i2cx->CR1,I2C_REG_CR1_NOSTRETCH);
	}
}


static void I2C_configure_ccr( u32 pclk, u32 clkspeed, u32 duty_cycle)
{
	u32 ccr;
	
	if(clkspeed <= 100000)
	{
		/* configure ccr for standard mode */
		ccr = ( pclk * 1000000) / (clkspeed << 1);
		
	}else
	{
		 if(duty_cycle == I2C_FM_DUTY_2)
		 {
			 ccr = ( pclk * 1000000)/(3 * clkspeed);
			 
		 }else if(duty_cycle == I2C_FM_DUTY_16BY9)
		 {
			 /* this is to reach 400khz in fm mode */
			ccr = ( pclk * 1000000)/(25 * clkspeed);
		 }
	
	}
	
	i2cx->CCR |= ccr;

}
	

static void I2C_rise_time_configuration(u32 pclk, u32 ClockSpeed)
{
	  /*---------------------------- I2Cx TRISE Configuration --------------------*/
  /* Configure I2Cx: Rise Time */
//  hi2c->Instance->TRISE = I2C_RISE_TIME(freqrange, hi2c->Init.ClockSpeed);
	
	u32 trise;
	if( ClockSpeed <= 100000)
	{
		trise = pclk +1;
	}else
	{
		trise = (((pclk * 300) / 1000) + 1);
	}

		i2cx->TRISE  &= ~(0x3F);
		i2cx->TRISE  |= trise;
	
}

static void I2C_set_clk_mode(u8 I2C_Mode)
{
	if (I2C_Mode == I2C_ENABLE_FM)
	{
		SET_BIT(i2cx->CCR, I2C_REG_CCR_ENABLE_FM);
	}
	else
	{
		CLR_BIT(i2cx->CCR, I2C_REG_CCR_ENABLE_FM);
	}
	
}

static void I2C_set_fm_mode_duty_cycle(u32 duty_cycle)
{
	if(duty_cycle == I2C_FM_DUTY_16BY9 )
	{
      SET_BIT(i2cx->CCR,I2C_REG_CCR_DUTY);
	}else
  {
		 CLR_BIT(i2cx->CCR,I2C_REG_CCR_DUTY);
	}		
}


static void I2C_clk_init ( u32 clkspeed, u32 duty_cycle)
{
	u32 pclk = I2C_PERIPHERAL_CLK_FREQ_36MHZ;
	i2cx->CR2 |= (pclk );
	I2C_rise_time_configuration(pclk, clkspeed);
	I2C_configure_ccr(pclk,clkspeed,duty_cycle);
	if( clkspeed <= 100000)
	{
		I2C_set_clk_mode(I2C_ENABLE_SM);
	}else
	{
		I2C_set_clk_mode(I2C_ENABLE_FM);
		I2C_set_fm_mode_duty_cycle(duty_cycle);
	}
}

static void I2C_set_addressing_mode( u32 adr_mode)
{
	if(adr_mode == I2C_ADDRMODE_10BI)
		SET_BIT(i2cx->OAR1, I2C_REG_OAR1_ADDRMODE);
	else 
		CLR_BIT(i2cx->OAR1, I2C_REG_OAR1_ADDRMODE);
}



static void I2C_manage_ack( u32 ack_noack)
{
	if(ack_noack == I2C_ACK_ENABLE)
		SET_BIT(i2cx->CR1, I2C_REG_CR1_ACK);
	else
		CLR_BIT(i2cx->CR1, I2C_REG_CR1_ACK);
}


static u8 is_bus_busy(void)
{
	if(GET_BIT(i2cx->SR2, I2C_REG_SR2_BUS_BUSY_FLAG) )
		return 1;
	else
		return 0;
}

static u8 i2c_wait_untill_sb_set(void)
{
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	
	if (GET_BIT(i2cx->SR1 , I2C_REG_SR1_SB_FLAG ))
	{
		return 1 ;
	}
	return 0;
}


static u8 i2c_wait_untill_addr_set(void)
{
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	
	if (GET_BIT(i2cx->SR1 , I2C_REG_SR1_ADDR_SENT_FLAG ))
	{
		return 1 ;
	}
	return 0;
}

static void I2C_send_addr_first( u8 address, u8 addr_type)
{
	if(addr_type == I2C_ADDREES_READ)
	{
		address = ((address << 1) | 0x1); /* addr+Read(1) */
	}
	else
	{
		address = (address << 1);  /* addr+Write(0) */
	}
	
	i2cx->DR = address;
	
}

static void clear_addr_flag(void)
{
	u16 val;
	
	val = i2cx->SR1;
	val = i2cx->SR2;
	
}

static void clear_stop_flag(void)
{ /* (READ SR1 then  WRITE CR1 */
	u16 val;
	val = i2cx->SR1;
	SET_BIT(i2cx->CR1 , I2C_REG_SR1_SB_FLAG);
}


 