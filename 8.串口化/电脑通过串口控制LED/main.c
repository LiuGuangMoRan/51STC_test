#include <REGX52.H>

void UART_Init()
{ 
	SCON = 0x50; 
	PCON |= 0x80;
	TMOD &= 0x0F;
	TMOD |= 0x20;
	TL1 = 0xF4;		
	TH1 = 0xF4;		
	ET1 = 0;      
	TR1 = 1;			
	
	//���жϣ�ִ���жϴ���
	EA=1;
	ES=1;
	
}

void main()
{
	UART_Init();
	while(1)
	{
	
	}
}

//���ô����������ݽ��в�������
void UART_Routine() interrupt 4
{
	if(RI=1)
	{
		P2=SBUF;
		RI=0;
	}
}

