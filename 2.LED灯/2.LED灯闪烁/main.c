#include <REGX52.H>
#include <intrins.h>

void sleep500ms()
{
	unsigned char i,j,k;
	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while(--k);
		}while(--j);
	}while(--i);
}

void main()
{
	while(1)
	{
		P2=0xFE;
		sleep500ms();
		P2=0xFF;
		sleep500ms();
	}
}