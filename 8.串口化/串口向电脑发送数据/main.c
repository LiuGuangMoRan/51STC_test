#include <REGX52.H>


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

void UART_Init()
{ 
	//���ô��ڵĹ�����ʽ��Ϊ��ʽ1����ض˿�SM0/FE,S1,��T1,R1�����ж�
	SCON = 0x40;  //0100 0000
	
	//���ô���Ĳ����ʣ��ɶ�ʱ����PCON����
	//PCON������ض˿�SMOD(������ѡ��λ�������ʼӱ�),SMOD0(������)
	PCON |= 0x80;
	//��ʱ�����ò�����	
	//���ö�ʱ��ģʽ0
	TMOD &= 0x0F;
	TMOD |= 0x20;
	TL1 = 0xF4;		//�趨��ʱ����ֵ
	TH1 = 0xF4;		//�趨��ʱ����װֵ
	ET1 = 0;      //��ֹ��ʱ��1�ж�
	TR1 = 1;			//������ʱ��1
	
}

void UART_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(T1==0); //�����ݷ��ͽ���ʱ��Ӳ���Զ���1�����Ѿ������������жϣ����жϵ�·û������
	T1=0;					//����ָ���0��
	
}

void main()
{
	UART_Init();
	UART_SendByte(0x66);
	while(1)
	{
	
	}
}