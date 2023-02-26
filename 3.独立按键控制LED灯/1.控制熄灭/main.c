#include <REGX52.H>

sbit LED = P2^0;

void main()
{
	while(1)
		if(P3_1==0)
		{
			LED=0;
		}
		else
		{
			P2_0=1;
		}
}