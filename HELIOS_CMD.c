#include "HELIOS_Kernel.h"
#include "HELIOS_FS.h"
#include "HELIOS_CMD.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

///////////////////////////////////////////
#include "motor.h"
#include "smartIO.h"
#include "BMS.h"
#include "PDU.h"
#include "instrument.h"


UART_DATA_TYPE UART_DATA;

static void CMD_FENGE(char * pData , char Data )
{
		int i = 0;
	  int length = strlen(pData);
	  int index_p  = 0;
	  int index_pp = 0;
	  if(pData[length] == ' ') {pData[length] = '\0';}
	  for(i=0;i<length;i++)
		{
				if( pData[i] != Data && pData[i] != ' ' && pData[i] != '\r' && pData[i] != '\n')
				{
						UART_DATA.CMD[index_p][index_pp++] = pData[i];
				}
				if(pData[i] == Data)
				{
						index_p++;
					  index_pp = 0;
				}
		}
		UART_DATA.arg_num = index_p;
}


void CMD_PUSH(char * Data)
{
		int i = 0;
	  if(UART_DATA.CMD_Point >= CMD_JILU_MAX )
		{
			  UART_DATA.CMD_Point = CMD_JILU_MAX-1;
				for(i = 0; i< (CMD_JILU_MAX - 1) ; i++)
				{
						memcpy( UART_DATA.CMD_BEFORE[i] , UART_DATA.CMD_BEFORE[i+1] , RECEIVE_MAX);
				}
		}
    strcpy(UART_DATA.CMD_BEFORE[UART_DATA.CMD_Point] , Data);
		UART_DATA.CMD_Point++;
		UART_DATA.Show_Point = UART_DATA.CMD_Point+1;
}

void UART_IRQ_BANK(char Data)
{
		if(Data == '\n' || Data == '\r')
		{
			  ////////////////////////////////////////
			  APP_Rukou(UART_DATA.DataReceive);
			  ////////////////////////////////////////
			  CMD_PUSH(UART_DATA.DataReceive);
				memset(UART_DATA.DataReceive , 0 , RECEIVE_MAX);
			  memset(UART_DATA.CMD , 0 , sizeof(UART_DATA.CMD));
			  UART_DATA.Data_receive_Num = 0;
		}
		else
		{
  			UART_DATA.DataReceive[UART_DATA.Data_receive_Num] = Data;
			  UART_DATA.Data_receive_Num ++;
			  
			  if(Data == 0x08){
					  UART_DATA.Data_receive_Num --;
					  UART_DATA.DataReceive[UART_DATA.Data_receive_Num] = 0x00;
					  UART_DATA.Data_receive_Num --;
					  UART_DATA.DataReceive[UART_DATA.Data_receive_Num] = 0x00;
					  printf("%c",Data);
						printf("\033[K");
				}  		
				else if(Data == 0x1B || Data == 0x5B || (Data >= 0x41 && Data <= 0x44))
				{
					  if(Data == 0x41)
						{
							  UART_DATA.Show_Point--;
							  if((char )UART_DATA.Show_Point <= 1) UART_DATA.Show_Point = 1;
					
						}
						if(Data == 0x42)
						{
							  UART_DATA.Show_Point++;
							  if((char )UART_DATA.Show_Point >= 5) UART_DATA.Show_Point = 5;
						}
						if(Data == 0x41 || Data == 0x42)
						{
								if(UART_DATA.Data_receive_Num>3)
								{
										printf("\033[%dD" , UART_DATA.Data_receive_Num-3);
										printf("\033[K");
								}
								printf("%s",(char *)UART_DATA.CMD_BEFORE[UART_DATA.Show_Point-1]);
								strcpy(UART_DATA.DataReceive , (char *)UART_DATA.CMD_BEFORE[UART_DATA.Show_Point-1]);
								UART_DATA.Data_receive_Num = strlen((char *)UART_DATA.CMD_BEFORE[UART_DATA.Show_Point-1]);
						}
				}
				else 
				{
						printf("%c",Data);
				}
		}
}

static void process_info_APP(UART_DATA_TYPE *pData , task_type *pData_task )
{
	  task_type* pHead = pData_task;
		printf("\r\n----------------------- process info -------------------------\r\n");
	  while(pHead!=NULL)
		{
			  printf("\r\n");
				printf("\033[32m  Task_name    : %s \r\n\033[37m" , pHead->task_name);
			  printf("\033[33m  Task_pid     : %d \r\n" , pHead->pid);
			  printf("  Task_Count   : %ld \r\n" , pHead->count);
			  printf("  Task_Cpu_Src : %f \r\n" , pHead->CPU_src);
			  printf("  Task_Pir     : %d \r\n" , pHead->pri);
			  printf("\r\n\033[37m");
			
			  pHead = pHead->task_next;
		}
		printf("\r\n----------------------- process info -------------------------\r\n");
}

static void ls_APP(UART_DATA_TYPE *pData)
{
	;
}

static void uname_APP(UART_DATA_TYPE *pData)
{
		if(strcmp( pData->CMD[1] , "-a") == 0) {  printf("\033[32m\r\nHELIIOS_V1.0 - beta version  ; \033[33m please call heli_pro@163.com \r\n\033[37m"); }
    if(strcmp( pData->CMD[1] , "-r") == 0) {  printf("\r\nHELIIOS_V1.0 \r\n"); }
}

static void MemRead(UART_DATA_TYPE *pData)
{
	  if(pData->arg_num >= 3)
		{
			 if(strcmp(pData->CMD[1], "-r") == 0 )
			 {
				   unsigned char * Temp = (unsigned char *)malloc( atoi(pData->CMD[3]) );
					 memory_read( atoi(pData->CMD[2])  , atoi(pData->CMD[3])  , (unsigned char *)Temp);
					 free(Temp);
			 }
			 else if(strcmp(pData->CMD[1], "-w") == 0 )
			 {
					 memory_write( atoi(pData->CMD[2])  , atoi( pData->CMD[3]) );
			 }
			 else
			 {
						printf("\r\n[MemRead]: wrong arg you may input arg1: -r or -w \r\n");
			 }
		}
		else
		{
				printf("\r\n[MemRead]: wrong arg num\r\n");
		}

}
static void DEMOAPP( UART_DATA_TYPE *pData)
{
	  /*int i = 0;
	  printf("\r\n");
		printf("arg_num:%d\n\r" , pData->arg_num);
	  printf("cmd_is:%s\n\r" , pData->CMD[0]);
	  for(i=0;i<pData->arg_num;i++)
		{
				printf("arg%d_is:%s\n\r" ,i, pData->CMD[i+1]);
		}*/
		if(strcmp( pData->CMD[0] , "processinfo") == 0) process_info_APP(pData , task_head );
		else if(strcmp( pData->CMD[0] , "ls") == 0) ls_APP(pData);
		else if(strcmp( pData->CMD[0] , "uname") == 0) uname_APP(pData);
    else if(strcmp( pData->CMD[0] , "devmem") == 0) MemRead(pData);//ArgeSET(UART_DATA_TYPE *pData)
	  /////////////////////////////////////////////////////////////////////////////////////////
	  else if(strcmp( pData->CMD[0] , "motorset") == 0) ArgeSET(pData);
	  else if(strcmp( pData->CMD[0] , "dispmotor") == 0) DispMotorStatus(pData);
	  else if(strcmp( pData->CMD[0] , "automotor") == 0) autoset();
	  else if(strcmp( pData->CMD[0] , "manumotor") == 0) manuset();
	  else if(strcmp( pData->CMD[0] , "showinstrument") == 0) showinstrument(pData);
	  else if(strcmp( pData->CMD[0] , "setinstrument") == 0) setinstrument(pData);
	  else if(strcmp( pData->CMD[0] , "setsw") == 0)SW_CONTROL_MANUEL(atoi(pData->CMD[1]) , atoi(pData->CMD[2]) , atoi(pData->CMD[3]));
		else if(strcmp( pData->CMD[0] , "resetsw") == 0)SW_CONTROL_GOLABLE_RESET();
		else if(strcmp( pData->CMD[0] , "sethsw") == 0)HSW_CONTROL_MANUEL(atoi(pData->CMD[2]) , atoi(pData->CMD[3]));
		else if(strcmp( pData->CMD[0] , "disp_out") == 0)SmartIO.Debug_Disp_Output = 1;
		else if(strcmp( pData->CMD[0] , "disp_in") == 0)SmartIO.Debug_Disp_Input = 1;
		else if(strcmp( pData->CMD[0] , "detype") == 0) SW_CHANGE_DEBUGE(atoi(pData->CMD[1]));
		else if(strcmp( pData->CMD[0] , "logicen") == 0) SmartIO.Logic_Enable = ENABLE_LOGIC;
		else if(strcmp( pData->CMD[0] , "logicds") == 0) SmartIO.Logic_Enable = DISABLE_LOGIC;
		else if(strcmp( pData->CMD[0] , "setswin") == 0)SW_Input_Manue(atoi(pData->CMD[1]) , atoi(pData->CMD[2]) , atoi(pData->CMD[3]));//SW_Input_Manue(int SW , int input_code , int value);
	  else if(strcmp( pData->CMD[0] , "can1open") == 0)  Task_can.CAN1_Transmit_Enable = 1;
		else if(strcmp( pData->CMD[0] , "can1close") == 0) Task_can.CAN1_Transmit_Enable = 0;
		else if(strcmp( pData->CMD[0] , "dispbms") == 0) BMS_Info_Display();
		//////////////////////////////////////////////////////////////////////////////////////////
	  else { printf("\033[31m\r\n[HE_LI_SHELL]: %s Is Not Found \033[37m" , pData->CMD[0]);}			
} 



void APP_Rukou(char * Data)
{
		if(strlen(Data) > 0)
		{
				CMD_FENGE( Data , ' ' );
			  DEMOAPP(&UART_DATA);
		}
	  printf("\n\rroot@HELIOS:~# ");
}
















