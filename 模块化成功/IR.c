#include <REXG52.H>
#include "OutBreak.h"

unsigned int IR_Time;           //表示红外通的不同状态的时间，进行存储
unsigned char IR_State;         //表示红外通信的状态，0为空闲，1为触发状态，2为翻译

//这里我觉得可以进行用指针去弄，优点是节省空间并且增加运算速度

unsigned char IR_Date[4];       //数据存储：地址码+地址反码+命令+命令反码
unsigned char IR_pDate;         //进行移位的参数

unsigned char IR_DataFlag;      //表示完成数据获取操作
unsigned char IR_RepeatFlag;    //当IR_RepeatFlay = 1时，表示的是进入的是RepeatFlay重复上次的数据内容
unsigned char IR_Address;       //红外发送装置的按钮的地址
unsigned char IR_Command;       //红外发送装置的按钮的号

//      红外通信原理
/**
 * 1.红外通信原理：程序编程的是接收端，发送信号为硬件的红外遥控装置
 * 2.红外遥控发送的数据数据帧含:Start,Data(repeat)组成
 * 3.红外接收装置：OUT端连接的是单片机IO口的P3_0端，当是38k红外信号，P3_0会置1，不是38k红外信号，P3_0会置0
 * 4.接收数据通信表示：通过外部中断进入中断函数，触发条件为P3_0断为低电平(下降沿触发)，
 * 而这下降沿触发意味着：触发以后，下一个触发要经过低——高两个阶段，由存在高电平的数据来区分0/1
 * 5.红外发送和接收装置怎么工作无需关心，只要知道得到的是一串脉冲，然后进行翻译得到一组0/1
 * 6.红外发送装置：发送是一串波形(含38k波形)，而在波形不代表0/1状态，滤波电路会转成理想的高低电平信号
 * 7.数据存储：Data含：地址码+地址反码+命令+命令反码，
 * 也就是32字节(本工程是由数组储存，当然也可以用long int，但位运算可能有点问题)
 * 8.数据帧：一次中断程序只能存1个比特位(而在比特位是通过一个高低电平)，
 * 得到的一串波形，不只一个下降沿触发，也就是触发中断至少32次
*/


void IR_Init(void)
{
    Timer0_Init_NoWork();
    OutBreak_Init();
}

/**
  * @brief  返回是否完成数据获取操作
  * @param  无
  * @retval 返回0/1表示是否完成操作
  */
unsigned char IR_GetDataFlag(void)
{
    if(IR_DataFlag)
    {
        return 1;
    }
    return 0;
}

/**
  * @brief  返回是否重复上述操作到主函数中
  * @param  无
  * @retval 返回0/1表示进行了重复操作
  */
unsigned char IR_GetRepeat(void)
{
    if(IR_RepeatFlag)
    {
        return 1;
    }
    return 0;
}

/**
  * @brief  返回地址数据到主函数中
  * @param  无
  * @retval 返回地址数据
  */
unsigned char IR_GetAddress(void)
{
    return IR_Address;
}

/**
  * @brief  返回命令数据到主函数中
  * @param  无
  * @retval 返回命令数据
  */
unsigned char IR_GetCommand(void)
{
    return IR_Command;
}

/**
  * @brief  外部中断函数(进行数据通信)
  * @param  无
  * @retval 无
  */
//完成三中工作状态：0为空闲，1为触发状态，2为翻译
void OutBreak_Routine(void) interrupt 0
{
    if(IR_State == 0)
    {
        Timer0_SetCounter(0);   //重置定时器初值
        Timer0_Run(1);          //启动定时器
        IR_State = 1;           //状态改变
    }
    else if(IR_State == 1)
    {
        IR_Time = Timer0_GetCounter();  //得到计数器的计数值
        Timer0_SetCounter(0);           //重置计数器的值
        if (IR_Time > 13500-500 && IR_Time <13500+500)  //当计数器到达这个9ms+4.5ms时间段时，表示数据通信开始
        {
            IR_State = 2;        //当IR_State = 2 进入翻译状态
        }
        else if (IR_Time > 11250-500 && IR_Time <11250+500)
        {
            IR_RepeatFlag = 1;   //存储表示已经进入重复操作
            Timer0_Run(0);       //关闭定时器
            IR_State = 0;        //将状态置为空闲状态
        }
        else
        {
            IR_State = 1;        //重新调制到触发状态，进行操作
        }
    }
    else if(IR_State == 2)      //进入翻译data信号
    {
        IR_Time = Timer0_GetCounter(); //在IR_State = 1结尾已经将计数器置0了，所以这里得到的就是Date的高低电平存的时间
        Timer0_SetCounter(0);    //将计数器置0
        if(IR_Time > 1120-500 && IR_Time < 1120+500)    //计数器在560us+560us时间段，表示此时数据为0
        {
            IR_Date[IR_pDate/8] &= ~(0x01<<(IR_pDate%8)); //算法整理
            IR_pDate++;
        }
        else if(IR_Time > 2250-500 && IR_Time < 2250+500)//计数器在560us+1690us时间段，表示此时数据为1
        {
            IR_Date[IR_pDate/8] |= ~(0x01<<(IR_pDate%8));
        }
        else        //传输的数据错误
        {
            IR_State = 1;
        }
        if (IR_pDate >= 32)
        {
            IR_pDate = 0;
            if ((IR_Date[0] == ~IR_Date[1]) && (IR_Date[2] == ~IR_Date[3]) )  //通过与反码的比较进行数据验证
            {
                IR_Address = IR_Date[0];    //赋值翻译后的数据
                IR_Command = IR_Date[2];
                IR_DataFlag = 1;
            }
            //若是数据错误，没有解决的办法(需要改进)
        }
        
    }
}




