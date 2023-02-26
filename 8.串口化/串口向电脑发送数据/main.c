#include <REGX52.H>


void Delay(unsigned int xms)		//@12.000MHz
{
	unsigned char i, j;
	while(xms)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		}while (--i);
		xms--;
	}	
}

void UART_Init()
{ 
	//配置串口的工作方式，为方式1，相关端口SM0/FE,S1,而T1,R1配置中断
	SCON = 0x40;  //0100 0000
	
	//配置传输的波特率，由定时器和PCON控制
	//PCON控制相关端口SMOD(波特率选择位，波特率加倍),SMOD0(错误检测)
	PCON |= 0x80;
	//定时器配置波特率	
	//配置定时器模式0
	TMOD &= 0x0F;
	TMOD |= 0x20;
	TL1 = 0xF4;		//设定定时器初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;      //禁止定时器1中断
	TR1 = 1;			//启动定时器1
	
}

void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(T1==0); //当内容发送结束时，硬件自动置1，就已经向主机请求中断，但中断电路没有配置
	T1=0;					//软件恢复置0；
	
}

void main()
{
	UART_Init();
	UART_SendByte(0x66);
	while(1)
	{
	
	}
}