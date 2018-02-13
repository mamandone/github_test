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



//���ƣ�FlashSave
//���ܣ�flash ���湦��
//������
//		p	Ҫ��������ݡ�
//		n	Ҫ��������ݸ�����
extern  void FlashSave(char * p , int n );



//���ƣ�FlashSave
//���ܣ���ȡflash������
//������
//		p	��ȡ�����ݴ�ŵĵط�
//		n	Ҫ��ȡ�����ݸ�����
extern void FlashLoad(char * p , int n );

extern void flashtest(void );
extern void STMFLASH_test(void );

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
extern void STMFLASH_Write(unsigned long WriteAddr,unsigned long *pBuffer,unsigned long NumToWrite);

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToRead:��(4λ)��
extern void STMFLASH_Read(unsigned long ReadAddr,unsigned long *pBuffer,unsigned long NumToRead);

extern void logic_code_read (unsigned long *pBuffer , unsigned long Data_length);
extern void logic_code_wirte(unsigned long *pBuffer , unsigned long Data_length);

#endif

