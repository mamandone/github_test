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
//���ƣ�FlashSave
//���ܣ�flash ���湦��
//������
//		p	Ҫ��������ݡ�
//		n	Ҫ��������ݸ�����
void FlashSave(char * p , int n )
{
	int i;

	FLASH_Unlock(); //����
	FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_OPERR|FLASH_FLAG_WRPERR|
					FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);   //���־
	FLASH_EraseSector(FLASH_OPR_SECTOR , VoltageRange_3); //��������
	for(i = 0 ; i < n ; i++)
	{
		FLASH_ProgramByte(FLASH_SAVE_ADDR + i,p[n]);//д�ֽ�
	}
	FLASH_Lock();//����
}


//���ƣ�FlashSave
//���ܣ���ȡflash������
//������
//		p	��ȡ�����ݴ�ŵĵط�
//		n	Ҫ��ȡ�����ݸ�����
void FlashLoad(char * p , int n )
{
	volatile int i;
	volatile char * addr=(char *)FLASH_SAVE_ADDR;

	FLASH_Unlock(); //����
	//FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_OPERR|FLASH_FLAG_WRPERR| 
	//				FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);    //���־
	//FLASH_EraseSector(FLASH_OPR_SECTOR , VoltageRange_3); //��������
	for(i = 0 ; i < n ; i++)
	{
		p[n] = addr[i];
		//FLASH_LoadByte(FLASH_SAVE_ADDR + i,p[n]);//д�ֽ�
	}
	FLASH_Lock();//����
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
	
	
	FLASH_Unlock(); //����FLASH�������FLASH��д���ݡ�
	
	
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
	      FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	
	// Get the number of the start and end sectors //
	StartSector =FLASH_Sector_10;// GetSector(FLASH_Sector_10);  //��ȡFLASH��Sector���
	EndSector = FLASH_Sector_10;//GetSector(FLASH_Sector_10);
	
	//����FLASH
	for (i = StartSector; i < EndSector; i += 8)  //ÿ��FLASH�������8���ɲο��ϱ�FLASH Sector�Ķ��塣
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
	
	//�������//
	//��ʼд��//
	Address = FLASH_SAVE_ADDR;
	
	while (Address < FLASH_SAVE_ADDR + 64)
	{
		
		if (FLASH_ProgramWord(Address, DATA_32) == FLASH_COMPLETE)   //��DATA_32д����Ӧ�ĵ�ַ��
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
	
	FLASH_Lock();  //��FLASH����ҪFLASH���ڽ���״̬��
	
	//�������� ���д��ֵ�Ƿ���ȷ
	Address = FLASH_SAVE_ADDR;
	MemoryProgramStatus = 0x0;
	while (Address < FLASH_SAVE_ADDR + 64)
	{
		data32 = *(__IO uint32_t*)Address;   //��FLASH�е����ݣ�ֱ�Ӹ�����ַ�����ˡ������ڴ��ж�����һ����
		
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

//��ȡָ����ַ�İ���(16λ����)
//faddr:����ַ
//����ֵ:��Ӧ����.
unsigned long STMFLASH_ReadWord(unsigned long faddr)
{
       return *(vu32*)faddr;
} 
//




//��ȡĳ����ַ���ڵ�flash����
//addr:flash��ַ
//����ֵ:0~11,��addr���ڵ�����
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



//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ر�ע��:��ΪSTM32F4������ʵ��̫��,û�취���ر�����������,���Ա�����
// д��ַ�����0XFF,��ô���Ȳ������������Ҳ�������������.����
// д��0XFF�ĵ�ַ,�����������������ݶ�ʧ.����д֮ǰȷ��������
// û����Ҫ����,��������������Ȳ�����,Ȼ����������д.
//�ú�����OTP����Ҳ��Ч!��������дOTP��!
//OTP�����ַ��Χ:0X1FFF7800~0X1FFF7A0F
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ4�ı���!!)
//pBuffer:����ָ��
//NumToWrite:��(32λ)��(����Ҫд���32λ���ݵĸ���.)
void STMFLASH_Write(unsigned long WriteAddr,unsigned long *pBuffer,unsigned long NumToWrite) 
{
	FLASH_Status status = FLASH_COMPLETE;
	unsigned long addrx=0;
	unsigned long endaddr=0;	
	int SectorStart,SectorEnd;
	if(WriteAddr<STM32_FLASH_BASE||WriteAddr%4)return;	//�Ƿ���ַ
	FLASH_Unlock();									//���� 
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
	
	FLASH_DataCacheCmd(DISABLE);//FLASH�����ڼ�,�����ֹ���ݻ���
	
	addrx=WriteAddr;				//д�����ʼ��ַ
	endaddr=WriteAddr+NumToWrite*4;	//д��Ľ�����ַ
	SectorStart = STMFLASH_GetFlashSector(addrx);
	SectorEnd = STMFLASH_GetFlashSector(endaddr);
	
	if(addrx<0X1FFF0000)			//ֻ�����洢��,����Ҫִ�в�������!!
	{
		//while(addrx<endaddr)		//ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
		while(SectorStart <= SectorEnd)		//ɨ��һ���ϰ�.(�Է�FFFFFFFF�ĵط�,�Ȳ���)
		{
			if(STMFLASH_ReadWord(addrx)!=0XFFFFFFFF)//�з�0XFFFFFFFF�ĵط�,Ҫ�����������
			{   
				status=FLASH_EraseSector(SectorStart,VoltageRange_3);//VCC=2.7~3.6V֮��!!
				if(status!=FLASH_COMPLETE)
					break;	//����������
			}else 
				SectorStart += 8;
		} 
	}
	if(status==FLASH_COMPLETE)
	{
		while(WriteAddr<endaddr)//д����
		{
			if(FLASH_ProgramWord(WriteAddr,*pBuffer)!=FLASH_COMPLETE)//д������
			{ 
				break;	//д���쳣
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
	FLASH_DataCacheCmd(ENABLE);	//FLASH��������,�������ݻ���
	FLASH_Lock();//����
}


//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToRead:��(4λ)��
void STMFLASH_Read(unsigned long ReadAddr,unsigned long *pBuffer,unsigned long NumToRead)        
{
   unsigned long i;
	//FLASH_Unlock(); 
   for(i=0;i<NumToRead;i++)
   {
      pBuffer[i]=STMFLASH_ReadWord(ReadAddr);//��ȡ4���ֽ�.
      ReadAddr+=4;//ƫ��4���ֽ�.   
   }
  // FLASH_Lock();//����

}

unsigned char TEXT_Buffer[2048];
volatile unsigned char datatemp[2048];  
#define TEXT_LENTH sizeof(TEXT_Buffer)                       //���鳤��    
#define SIZE TEXT_LENTH/4+((TEXT_LENTH%4)?1:0)
/*����FLASH �����ַ(����Ϊż��������������,Ҫ���ڱ�������ռ�õ�������.����,
*д������ʱ��,���ܻᵼ�²�����������,�Ӷ����𲿷ֳ���ʧ.��������.*/
 

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


