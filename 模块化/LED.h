#ifndef __LED_H__
#define __LED_H__

void _74HC595_WriteByte(unsigned char Byte);
void show_LEDcolumn(unsigned char Column,unsigned char Data);

#endif