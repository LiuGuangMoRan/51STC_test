#include <REGX52.H>

/**
  * @brief  串口初始化，单片机发送电脑
  * @param  无
  * @retval 配置UART工作状态，传输的波特率(通过定时器进行)，无需中断系统
  */
void UART_Init_Send()
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

    //单片机中不只一个定时器，数量取决于单片机本身，而本单片机有T1.T0两个定时器
	TL1 = 0xF4;		//设定定时器初值
	TH1 = 0xF4;		//设定定时器重装值
	ET1 = 0;        //禁止定时器1中断
	TR1 = 1;		//启动定时器1
	
}

/**
  * @brief  向电脑发送数据帧
  * @param  Byte数据接收变量
  * @retval 中断的功能寄存器硬件自动置1，所以软件置0
  */
void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(T1==0);   //当内容发送结束时，硬件自动置1，就已经向主机请求中断，但中断电路没有配置
	T1=0;			//软件恢复置0；
	
}

/**
  * @brief  串口初始化，电脑向单片机发送控制指令
  * @param  无
  * @retval 配置UART工作状态，传输的波特率(通过定时器进行)，需中断系统进行时时监控,通过中断程序进行控制
  */
void UART_Init_Receive()
{
	SCON=0x50;
	PCON |= 0x80;
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF3;		    //设定定时初值
	TH1 = 0xF3;		    //设定定时器重装值
	ET1 = 0;		    //禁止定时器1中断
	TR1 = 1;		    //启动定时器1
	
    //打开中断，执行中断代码
    EA=1;
	ES=1;
}

/**
  * @brief  向电脑发送数据帧
  * @param  Byte数据接收变量
  * @retval 中断的功能寄存器硬件自动置1，所以软件置0
  */
void UART_ReceiveByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}