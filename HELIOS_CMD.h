#ifndef _HELIOS_CMD_H_
#define _HELIOS_CMD_H_

#define RECEIVE_MAX   80
#define CMD_LEN_MAX   20
#define CMD_NUM_MAX   20
#define CMD_JILU_MAX  5

typedef struct UART_DATA
{
		char DataReceive[RECEIVE_MAX];
	  unsigned char Data_receive_Num;
    unsigned char Data_Receive_flag;
	           char arg_num;
	  char CMD[CMD_NUM_MAX][CMD_LEN_MAX];
	  char CMD_BEFORE[CMD_JILU_MAX][RECEIVE_MAX];
	  char CMD_Point;
	  char Show_Point;
}UART_DATA_TYPE;



extern UART_DATA_TYPE UART_DATA;
extern void UART_IRQ_BANK(char Data);
extern void APP_Rukou(char * Data);
extern void CMD_PUSH(char * Data);
















#endif




