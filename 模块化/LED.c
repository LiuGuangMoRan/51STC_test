#include <REGX52.H>
#include "tool.h"
//重置命名对应端口号
sbit RCLK_1 = P3^5;			//根据时钟信号使输入缓冲器搬入输出缓冲器
sbit SERCLK = P3^6; 	    //根据时钟信号使数据下移8次
sbit SER  = P3^4; 		    //输入数据断 

/** 
  * @brief   配置74HC595,即控制阳极
  * @param   Byte接收8个比特位，配置阳极
  * @retval  74HC595译码器减少单片机端口
  */
void _74HC595_WriteByte(unsigned char Byte)
{
	unsigned char i=0 ;
	for(i=0;i<8;i++)
	{	
		//SER是位，当它被赋于大1的数，非零即1
		//通过下面算法得到每个位的0/1，算法总结
		SER = Byte & (0x80>>i); //被于有 0x80，0x40，0x20.....
		SERCLK = 1; //打开赋给时钟信号1，使数据向下移
		SERCLK = 0; //恢复0
	}
	
	RCLK_1 = 1;
	RCLK_1 = 0;
	
	//0x80 1000 0000  Byte 1001 1100
	
}

/** 
  * @brief   配置一列亮的LED
  * @param   Date设置哪一列的LED灯亮，Column设置哪个LED灯亮
  * @retval  整体是设置一列的LED灯亮的情况，并消影
  */
void show_LEDcolumn(unsigned char Column,unsigned char Data)
{
	_74HC595_WriteByte(Data); //设置阳极,一列的LED亮
	P0 = ~(0x80>>Column);     //设置阴极,哪一列亮
	//消影
	Delay(1);
	P0 = 0xFF;
}