#ifndef __USART1_H
#define __USART1_H
#include "stdio.h"	
#include "common.h" 

//////////////////////////////////////////////////////////////////////////////////	 

#define USART1_REC_NUM  			100  	//定义最大接收字节数 200
extern u8 uart_byte_count;          //uart_byte_count要小于USART_REC_LEN
extern u8 receive_str[USART1_REC_NUM];  
extern u8 Recv_Buffer[8];
void uart1_init(u32 bound);
void uart1SendChars(u8 *str, u16 strlen);
void uart1SendChar(u8 ch);
#endif


