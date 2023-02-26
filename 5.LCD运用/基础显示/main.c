#include <regx52.h>
#include <lcd1602.h>

void main()
{
	LCD_Init();
	LCD_ShowChar(1,1,'a');
	LCD_ShowString(1,3,"hello");
	while(1)
	{
	
	}
}