#include  "HELIOS_FS.h"
#include  "stdio.h"
#include  "string.h"
#include  "stdlib.h"

unsigned char FS_SPACE[SPACE_FOR_FS];



void memory_write( int start_adress  , unsigned char  pData)
{
	  if(start_adress<0  || start_adress >=  SPACE_FOR_FS) 
		{
			  printf("\r\n[devmem]:wrong addres for write [ 0 : %d]\r\n " , SPACE_FOR_FS);
				return;
		}
		FS_SPACE[start_adress] = pData;
}


void memory_read( int start_adress  , int length  , unsigned char * pData)
{
	  int i = 0;
	  int j = 0;
		memcpy( pData , (char *)(FS_SPACE+start_adress) , length);
	  printf("\r\n");
	  for(i = 0; i<length ; i++)
		{
				printf("%02x  " , pData[i]);
			  j ++;
			  if( j == 16) { j = 0; printf("\r\n");}
		}
}












