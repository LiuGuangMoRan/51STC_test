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
		//����Ϊ�ȴӰ��Ƶ�����
		for(Time=0;Time<100;Time++)//��forѭ���ǵȵ���ͬ״̬�ĵ�
		{	
			for(i=0;i<20;i++)//��forѭ�����ò�ͬ״̬�ĵ���ʾʱ��䳤
			{
				//�������ȵƲ������ӳ�ʱ�䳤����˵����״̬Ϊ"����"����֮����"����"
				LED = 0;
				Delay(Time);
				LED = 1;
				Delay(100-Time);
			}
		}
	  //����Ϊ�ȴ����Ƶ�����
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

