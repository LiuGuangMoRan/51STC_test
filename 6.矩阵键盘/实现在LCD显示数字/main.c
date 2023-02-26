#include <regx52.h>
#include <lcd1602.h>

unsigned char KeyNum;

void main()
{
	LCD_Init();
	LCD_ShowString(1,1,"password");
	while(1)
	{
		KeyNum = KEY();
		if(KeyNum)
		{
			LCD_ShowNum(2,1,KeyNum,2);
		}
	}
}