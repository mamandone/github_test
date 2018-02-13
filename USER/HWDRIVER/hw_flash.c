#include "stm32f4xx_flash.h"
#include "hw_flsh.h"
#include "iwdg.h"


void flashDelay(int n)
{
	while(n-- > 0)
	{
			MX_IWDG_Reload();
	};
}

/*
//名称：FlashSave
//功能：flash 保存功能
//参数：
//		p	要保存的数据。
//		n	要保存的数据个数。
void FlashSave(char * p , int n )
{
	int i;

	FLASH_Unlock(); //解锁
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_OPERR|FLASH_FLAG_WRPERR|
					FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);   //清标志
	FLASH_EraseSector(FLASH_OPR_SECTOR , VoltageRange_3); //擦除扇区
	for(i = 0 ; i < n ; i++)
	{
		FLASH_ProgramByte(FLASH_SAVE_ADDR + i,p[n]);//写字节
	}
	FLASH_Lock();//加锁
}


//名称：FlashSave
//功能：读取flash内数据
//参数：
//		p	读取的数据存放的地方
//		n	要读取的数据个数。
void FlashLoad(char * p , int n )
{
	volatile int i;
	volatile char * addr=(char *)FLASH_SAVE_ADDR;

	FLASH_Unlock(); //解锁
	//FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_OPERR|FLASH_FLAG_WRPERR| 
	//				FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);    //清标志
	//FLASH_EraseSector(FLASH_OPR_SECTOR , VoltageRange_3); //擦除扇区
	for(i = 0 ; i < n ; i++)
	{
		p[n] = addr[i];
		//FLASH_LoadByte(FLASH_SAVE_ADDR + i,p[n]);//写字节
	}
	FLASH_Lock();//加锁
}







#define DATA_32                 ((uint32_t)0x87654321)


void flashtest(void )
{
	volatile int MemoryProgramStatus;
	int Address;
	int StartSector;
	int EndSector;
	int i;
	volatile int data32;
	
	
	FLASH_Unlock(); //解锁FLASH后才能向FLASH中写数据。
	
	
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
	      FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	
	// Get the number of the start and end sectors //
	StartSector =FLASH_Sector_10;// GetSector(FLASH_Sector_10);  //获取FLASH的Sector编号
	EndSector = FLASH_Sector_10;//GetSector(FLASH_Sector_10);
	
	//擦除FLASH
	for (i = StartSector; i < EndSector; i += 8)  //每次FLASH编号增加8，可参考上边FLASH Sector的定义。
	{
		/// Device voltage range supposed to be [2.7V to 3.6V], the operation will
		//be done by word 
		if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE)
		{ 
			while (1)
			{
			}
		}
	}
	
	//擦除完毕//
	//开始写入//
	Address = FLASH_SAVE_ADDR;
	
	while (Address < FLASH_SAVE_ADDR + 64)
	{
		
		if (FLASH_ProgramWord(Address, DATA_32) == FLASH_COMPLETE)   //将DATA_32写入相应的地址。
		{
			Address = Address + 4;
		}
		else
		{ 
			// Error occurred while writing data in Flash memory. 
			User can add here some code to deal with this error 
			while (1)
			{
			}
		}
	}
	
	FLASH_Lock();  //读FLASH不需要FLASH处于解锁状态。
	
	//读出数据 检查写入值是否正确
	Address = FLASH_SAVE_ADDR;
	MemoryProgramStatus = 0x0;
	while (Address < FLASH_SAVE_ADDR + 64)
	{
		data32 = *(__IO uint32_t*)Address;   //读FLASH中的数据，直接给出地址就行了。跟从内存中读数据一样。
		
		if (data32 != DATA_32)
		{
			MemoryProgramStatus++;  
		}
		
		Address = Address + 4;
	}  
}
*/
//


/////////////////////////////////////////////////////////////////////////////////////////////////

//读取指定地址的半字(16位数据)
//faddr:读地址
//返回值:对应数据.
unsigned long STMFLASH_ReadWord(unsigned long faddr)
{
       return *(vu32*)faddr;
} 
//




//获取某个地址所在的flash扇区
//addr:flash地址
//返回值:0~11,即addr所在的扇区
uint16_t STMFLASH_GetFlashSector(unsigned long addr)
{
       if(addr<ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
       else if(addr<ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
       else if(addr<ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
       else if(addr<ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
       else if(addr<ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
       else if(addr<ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
       else if(addr<ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
       else if(addr<ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
       else if(addr<ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
       else if(addr<ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
       else if(addr<ADDR_FLASH_SECTOR_11)return FLASH_Sector_10;
       return FLASH_Sector_11;    
}



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
void STMFLASH_Write(unsigned long WriteAddr,unsigned long *pBuffer,unsigned long NumToWrite) 
{
	FLASH_Status status = FLASH_COMPLETE;
	unsigned long addrx=0;
	unsigned long endaddr=0;	
	int SectorStart,SectorEnd;
	if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//非法地址
	FLASH_Unlock();									//解锁 
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	
	FLASH_DataCacheCmd(DISABLE);//FLASH擦除期间,必须禁止数据缓存
	
	addrx=WriteAddr;				//写入的起始地址
	endaddr=WriteAddr+NumToWrite*4;	//写入的结束地址
	SectorStart = STMFLASH_GetFlashSector(addrx);
	SectorEnd = STMFLASH_GetFlashSector(endaddr);
	
	if(addrx<0X1FFF0000)			//只有主存储区,才需要执行擦除操作!!
	{
		//while(addrx<endaddr)		//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
		while(SectorStart <= SectorEnd)		//扫清一切障碍.(对非FFFFFFFF的地方,先擦除)
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//有非0XFFFFFFFF的地方,要擦除这个扇区
			{   
				status=FLASH_EraseSector(SectorStart,VoltageRange_3);//VCC=2.7~3.6V之间!!
				if(status!=FLASH_COMPLETE)
					break;	//发生错误了
			}else 
				SectorStart += 8;
		} 
	}
	if(status==FLASH_COMPLETE)
	{
		while(WriteAddr<endaddr)//写数据
		{
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//写入数据
			{ 
				break;	//写入异常
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
	FLASH_DataCacheCmd(ENABLE);	//FLASH擦除结束,开启数据缓存
	FLASH_Lock();//上锁
}


//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToRead:字(4位)数
void STMFLASH_Read(unsigned long ReadAddr,unsigned long *pBuffer,unsigned long NumToRead)        
{
   unsigned long i;
	//FLASH_Unlock(); 
   for(i=0;i<NumToRead;i++)
   {
      pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//读取4个字节.
      ReadAddr+=4;//偏移4个字节.   
   }
  // FLASH_Lock();//上锁

}

unsigned char TEXT_Buffer[2048];
volatile unsigned char datatemp[2048];  
#define TEXT_LENTH sizeof(TEXT_Buffer)                       //数组长度    
#define SIZE TEXT_LENTH/4+((TEXT_LENTH%4)?1:0)
/*设置FLASH 保存地址(必须为偶数，且所在扇区,要大于本代码所占用到的扇区.否则,
*写操作的时候,可能会导致擦除整个扇区,从而引起部分程序丢失.引起死机.*/
 

void logic_code_read (unsigned long *pBuffer , unsigned long Data_length)
{
		STMFLASH_Read(FLASH_SAVE_ADDR, pBuffer ,SIZE);
		flashDelay(500000);
}
void logic_code_wirte(unsigned long *pBuffer , unsigned long Data_length)
{
		STMFLASH_Write(FLASH_SAVE_ADDR, pBuffer ,SIZE);
		flashDelay(500000);
}

void STMFLASH_test(void)
{
	int i = 0;
	
	for(i=0;i<TEXT_LENTH;i++)
	{
		 TEXT_Buffer[i] = i%5;
	}
	
	//STMFLASH_Write(FLASH_SAVE_ADDR,(u32*)TEXT_Buffer,1);
	//delay(10000000);
	STMFLASH_Read(FLASH_SAVE_ADDR,(unsigned long*)datatemp,SIZE);
	flashDelay(50000000);
	STMFLASH_Write(FLASH_SAVE_ADDR,(unsigned long*)TEXT_Buffer,SIZE);
	flashDelay(50000000);
	STMFLASH_Read(FLASH_SAVE_ADDR,(unsigned long*)datatemp,SIZE);
	flashDelay(50000000);
}


