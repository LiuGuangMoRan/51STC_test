#include <REGX52.H>
#include <INTRINS.H>

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
		P2 = 0xFE;
		sleep500ms();
		P2 = 0xFD;
		sleep500ms();
		P2 = 0xFB;
		sleep500ms();
		P2 = 0xF7;
		sleep500ms();
		P2 = 0xEF;
		sleep500ms();
		P2 = 0xDF;
		sleep500ms();
		P2 = 0xBF;
		sleep500ms();
		P2 = 0x7F;
		sleep500ms();
	}
}
