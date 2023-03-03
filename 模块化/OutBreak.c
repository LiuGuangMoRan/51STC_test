#include <rexg52.h>

//1.设置外部中断
void OutBreak_Init(void)
{
	IT0 = 1;		//设置下降沿触发，触发端P3_2,P3_3,对应的是按键，开始为高电平，上沿触发意义不同
	IE0 = 0;		//以下是设置中断系统的条件
	EX0 = 1;
	EA  = 1;
	PX0 = 1;
}

/*
void OutBreak_Routine(void) interrupt 0
{
    
}
*/