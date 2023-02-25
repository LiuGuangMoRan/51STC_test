#include <REGX52.H>

sbit xuanLED(int number)
{
	switch(number)
	{
		case1:sbit LED1 = P2^0;return LED1;break;
		case2:sbit LED2 = P2^1;return LED2;break;
		case3:sbit LED3 = P2^2;return LED3;break;
		case4:sbit LED4 = P2^3;return LED4;break;
		case5:sbit LED5 = P2^4;return LED5;break;
		case6:sbit LED6 = P2^5;return LED6;break;
		case7:sbit LED7 = P2^6;return LED7;break;
		case8:sbit LED8 = P2^7;return LED8;break;
	}
}

void main()
{
	LED = xuanLED(2);
}