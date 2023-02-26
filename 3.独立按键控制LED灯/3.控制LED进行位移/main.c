#include <regx52.h>

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

unsigned char LEDNum;

void main()
{
		while(1)
		{
			if(P3_0 == 0)
			{
				Delay(20);
				while(P3_1==0);
				Delay(20);
				LEDNum++;
				if(LEDNum>=8)
					LEDNum=0;
				P2=~(0x01<<LEDNum);
				
				while(1)//检查按键是否松手
				{
					if(P3_0 == 1)
					{
						break;
					}
				}
			}
		}
}