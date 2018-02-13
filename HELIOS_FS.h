#ifndef _HELIOS_FS_H_
#define _HELIOS_FS_H_


#define SPACE_FOR_FS    4096

extern unsigned char FS_SPACE[SPACE_FOR_FS];

extern void memory_write( int start_adress  , unsigned char  pData);


extern void memory_read( int start_adress  , int length  , unsigned char * pData);














#endif



