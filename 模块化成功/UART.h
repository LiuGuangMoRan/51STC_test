#ifndef __UART_H__
#define __UART_H__

void UART_Init_Sende();
void UART_SendByte(unsigned char Byte);

void UART_Init_Receive();
void UART_ReceiveByte(unsigned char Byte);

#endif
