#include <REGX52.H>

sbit LED = P2^2;

void Delay(unsigned int t)
{
	while(t--);
}

void main()
{
	unsigned char Time;
	unsigned char i;
	while(1)
	{	
		//整体为等从暗灯到亮灯
		for(Time=0;Time<100;Time++)//该for循环是等到不同状态的灯
		{	
			for(i=0;i<20;i++)//该for循环是让不同状态的灯显示时间变长
			{
				//灯亮，比灯不亮的延迟时间长，就说明该状态为"亮灯"，反之则是"暗灯"
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(100-Time);
			}
		}
	  //整体为等从亮灯到暗灯
		for(Time=100;Time>0;Time--)
		{	
			for(i=0;i<20;i++)
			{
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(100-Time);
			}
		}
	}
}

