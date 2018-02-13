#ifndef STM32_FLASH
#define STM32_FLASH

#include "stm32f4xx.h"
#include "stm32f4xx_flash.h"


#define  ADDR_FLASH_SECTOR_0	((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */  
#define  ADDR_FLASH_SECTOR_1	((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */ 
#define  ADDR_FLASH_SECTOR_2	((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */ 
#define  ADDR_FLASH_SECTOR_3	((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */ 
#define  ADDR_FLASH_SECTOR_4	((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */ 
#define  ADDR_FLASH_SECTOR_5	((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */ 
#define  ADDR_FLASH_SECTOR_6	((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */ 
#define  ADDR_FLASH_SECTOR_7	((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */  
#define  ADDR_FLASH_SECTOR_8	((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */   
#define  ADDR_FLASH_SECTOR_9	((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */   
#define  ADDR_FLASH_SECTOR_10	((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */ 
#define  ADDR_FLASH_SECTOR_11	((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

#define STM32_FLASH_BASE	ADDR_FLASH_SECTOR_0

#define FLASH_SAVE_ADDR   0x080E0000 //0X0800C004  //0x08060000 



//名称：FlashSave
//功能：flash 保存功能
//参数：
//		p	要保存的数据。
//		n	要保存的数据个数。
extern  void FlashSave(char * p , int n );



//名称：FlashSave
//功能：读取flash内数据
//参数：
//		p	读取的数据存放的地方
//		n	要读取的数据个数。
extern void FlashLoad(char * p , int n );

extern void flashtest(void );
extern void STMFLASH_test(void );

//从指定地址开始写入指定长度的数据
//特别注意:因为STM32F4的扇区实在太大,没办法本地保存扇区数据,所以本函数
// 写地址如果非0XFF,那么会先擦除整个扇区且不保存扇区数据.所以
// 写非0XFF的地址,将导致整个扇区数据丢失.建议写之前确保扇区里
// 没有重要数据,最好是整个扇区先擦除了,然后慢慢往后写.
//该函数对OTP区域也有效!可以用来写OTP区!
//OTP区域地址范围:0X1FFF7800~0X1FFF7A0F
//WriteAddr:起始地址(此地址必须为4的倍数!!)
//pBuffer:数据指针
//NumToWrite:字(32位)数(就是要写入的32位数据的个数.)
extern void STMFLASH_Write(unsigned long WriteAddr,unsigned long *pBuffer,unsigned long NumToWrite);

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToRead:字(4位)数
extern void STMFLASH_Read(unsigned long ReadAddr,unsigned long *pBuffer,unsigned long NumToRead);

extern void logic_code_read (unsigned long *pBuffer , unsigned long Data_length);
extern void logic_code_wirte(unsigned long *pBuffer , unsigned long Data_length);

#endif

