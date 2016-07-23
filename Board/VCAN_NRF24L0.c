
#include "common.h"
#include "MK60_port.h"
#include "MK60_gpio.h"
#include "MK60_spi.h"
#include "VCAN_NRF24L0.h"

extern u8 NRF_flag;
extern u8 NRF_rxbuf[32];
// 用户配置 发送和 接收地址，频道

const uint8 TX_ADDRESS[5] = {0x12,0x34,0x56,0x78,0x9a };   // 定义一个静态发送地址
const uint8 RX_ADDRESS[5] = {0x12,0x34,0x56,0x78,0x9a };

uint8 nrf_writereg(uint8 reg, uint8 dat)
{
    uint8 buff[2];
    buff[0] = reg;          //先发送寄存器
    buff[1] = dat;          //再发送数据
    spi_mosi(NRF_SPI, NRF_CS, buff, buff, 2); //发送buff里数据，并采集到 buff里
    /*返回状态寄存器的值*/
    return buff[0];
}

uint8 nrf_readreg(uint8 reg, uint8 *dat)
{
    uint8 buff[2];
    buff[0] = reg;          //先发送寄存器
    spi_mosi(NRF_SPI, NRF_CS, buff, buff, 2); //发送buff数据，并保存到buff里
    *dat = buff[1];                         //提取第二个数据
    /*返回状态寄存器的值*/
    return buff[0];
}
uint8 nrf_writebuf(uint8 reg , uint8 *pBuf, uint32 len)
{
    spi_mosi_cmd(NRF_SPI, NRF_CS, &reg , NULL, pBuf, NULL, 1 , len); //发送 reg ，pBuf 内容，不接收
    return reg;    //返回NRF24L01的状态
}

uint8 nrf_readbuf(uint8 reg, uint8 *pBuf, uint32 len)
{
    spi_mosi_cmd(NRF_SPI, NRF_CS, &reg , NULL, NULL, pBuf, 1 , len); //发送reg，接收到buff
    return reg;    //返回NRF24L01的状态
}



u8 NRF_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	nrf_writebuf(NRF_WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
	nrf_readbuf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 //检测到24L01
}	 	 

void nrf_init(u8 model)
{
    spi_init(NRF_SPI, NRF_CS, MASTER,12500*1000);                     //初始化SPI,主机模式
    gpio_init(NRF_CE_PTXn, GPO, LOW);                               //初始化CE，默认进入待机模式
    gpio_init(NRF_IRQ_PTXn, GPI, LOW);                              //初始化IRQ管脚为输入
    //配置NRF寄存器
    NRF_CE_LOW();

    nrf_writebuf(NRF_WRITE_REG + RX_ADDR_P0,(u8*)RX_ADDRESS, RX_ADR_WIDTH); //写RX节点地址
    nrf_writebuf(NRF_WRITE_REG + TX_ADDR, (u8*)TX_ADDRESS, TX_ADR_WIDTH); //写TX节点地址    
    nrf_writereg(NRF_WRITE_REG + EN_AA, 0x01);                      //使能通道0的自动应答
    nrf_writereg(NRF_WRITE_REG + EN_RXADDR, 0x01);                  //使能通道0的接收地址 
    nrf_writereg(NRF_WRITE_REG + SETUP_RETR, 0x1a);                 //设置自动重发间隔时间:250us + 86us;最大自动重发次数:15次
    nrf_writereg(NRF_WRITE_REG + RF_CH, 40);                    //设置RF通道为CHANAL
    nrf_writereg(NRF_WRITE_REG + RF_SETUP, 0x0f);                   //设置TX发射参数,0db增益,2Mbps,低噪声增益开启

    if(model==RX_MODE)				//RX
    {
            nrf_writereg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);								//选择通道0的有效数据宽度 
            nrf_writereg(NRF_WRITE_REG + CONFIG, 0x0f);   		 //CONFIG 0000 1111 IRQ收发完成中断开启,16位CRC,主接收
    }
    else if(model==TX_MODE)		//TX
    {
            nrf_writereg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);								//选择通道0的有效数据宽度 
            nrf_writereg(NRF_WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断开启,16位CRC,主发送
    }
    else if(model==RX2_MODE)		//RX2
    {
            nrf_writereg(FLUSH_TX,0xff);
            nrf_writereg(FLUSH_RX,0xff);
            nrf_writereg(NRF_WRITE_REG + CONFIG, 0x0f);   		 // IRQ收发完成中断开启,16位CRC,主接收
            
            nrf_writereg(0x50,0x73);
    
            nrf_writereg(NRF_WRITE_REG+0x1c,0x01); //DYNPD DPL_P0 
            nrf_writereg(NRF_WRITE_REG+0x1d,0x06);	//FEATURE 0000 0110 
    }
    else								//TX2
    {
            nrf_writereg(NRF_WRITE_REG + CONFIG, 0x0e);   		 // IRQ收发完成中断开启,16位CRC,主发送
            nrf_writereg(FLUSH_TX,0xff);
            nrf_writereg(FLUSH_RX,0xff);
            
            nrf_writereg(0x50,0x73);

            nrf_writereg(NRF_WRITE_REG+0x1c,0x01);
            nrf_writereg(NRF_WRITE_REG+0x1d,0x06);
    }
        
        
    NRF_CE_HIGH();

}


u8 NRF_TxPacket(u8 *txbuf)
{
  u8 sta=0;
  u8 rx_len=8;
  
  NRF_CE_LOW();
  
  nrf_writebuf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
  
  NRF_CE_HIGH();//启动发送	   
  
  while(gpio_get(NRF_IRQ_PTXn)==1);//等待发送完成
  
  nrf_readreg(0x07,&sta);  //读取状态寄存器的值	  
  nrf_writereg(NRF_WRITE_REG+0x07,sta); //清除TX_DS或MAX_RT中断标志  
  
  NRF_flag=sta;
  
  if(sta& MAX_RT)//达到最大重发次数
  {
    nrf_writereg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
    return MAX_RT; 
  }

  
  if(sta == 46)//0010 1110 发送中断置位 RX FIFO空
  {
          return TX_DS;
          
  }	
  if(sta == 32)//0010 0000 发送中断置位 RX FIFO 通道0 
  {
      nrf_readreg(0x60,&rx_len);
      if(rx_len<33)
      {
        // read receive payload from RX_FIFO buffer
        //0110 0001 读取接收端发送的过载数据 过载数据从FIFO读出后被删除。 用在RX模式？？？
        nrf_readbuf(RD_RX_PLOAD,NRF_rxbuf,rx_len);// read receive payload from RX_FIFO buffer
      
      }
      else 
      {
              //1110 0010 删除接收端 FIFO数据  用于RX模式？
              nrf_writereg(FLUSH_RX,0xff);//清空缓冲区
      }
      
      return 0xdd;
  }

    return 0xff;//其他原因发送失败
}


u8 NRF_RxPacket(u8 *rxbuf)
{
  u8 sta;		    							   

  nrf_readreg(0x07,&sta);  //读取状态寄存器的值    	 
  nrf_writereg(NRF_WRITE_REG+0x07,sta); //清除TX_DS或MAX_RT中断标志
  if(sta& RX_DR)//接收到数据
  {
      nrf_readbuf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
      return sta; 
  }
  return sta;//没收到任何数据
}


























