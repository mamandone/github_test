#include "can.h"
#include "task_can.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


void  MX_CAN1_Init(uint8_t mod)
{
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//�򿪶˿�Aʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);//��CAN���߽ӿ�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//���ù���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� PA11,PA12
	
	//���Ÿ���ӳ������
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);
	
	CAN_DeInit(CAN1);
	// CAN Baudrate = 250KBps (CAN clocked at 36 MHz) 
	CAN_InitStructure.CAN_TTCM = DISABLE;//��ʱ�䴥��ͨѶģʽ
	CAN_InitStructure.CAN_ABOM = DISABLE;//����Զ����߹���
	CAN_InitStructure.CAN_AWUM = DISABLE;//˯��ģʽͨ���������
	CAN_InitStructure.CAN_NART = ENABLE;//��ֹ�����Զ�����
	CAN_InitStructure.CAN_RFLM = DISABLE;//���Ĳ�����,�µĸ��Ǿɵ�
	CAN_InitStructure.CAN_TXFP = DISABLE;//���ȼ��ɱ��ı�ʶ������
	CAN_InitStructure.CAN_Mode =  mod;//����ģʽΪ�ػ�ģʽ
	CAN_InitStructure.CAN_SJW = CAN_SJW_4tq;//����ͬ����Ծ���Ϊ1��ʱ�䵥λ
	CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;//ʱ���1ռ��8��ʱ�䵥λ
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;//ʱ���2ռ��7��ʱ�䵥λ
	CAN_InitStructure.CAN_Prescaler = 8;		//��Ƶϵ��
	CAN_Init(CAN1, &CAN_InitStructure);//��ʼ��CAN1

	//CAN����������
	CAN_FilterInitStructure.CAN_FilterNumber = 0;//�ù�����0
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//��ʶ������λģʽ
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//����Ϊ1��32λ��
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;	//32λID��16λ  ���ñ�ʶ���Ĵ���
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;	//32λID��16λ
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;	//32λMASK-ID��16λ		���ñ�ʶ�����μĴ���
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;	//32λMASK-ID��16λ
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;//������������0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;	//���������
	CAN_FilterInit(&CAN_FilterInitStructure);	//��������ʼ��	
	
	
	 CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);				//FIFO0????????.		    
	 NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;     // ?????1
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // ?????0
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	 NVIC_Init(&NVIC_InitStructure);
}

void CAN1_RX0_IRQHandler(void)
{   
	CanRxMsg RxMessage;
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	Task_CAN1_IRQ( RxMessage.ExtId , RxMessage.DLC, RxMessage.Data);
}

void  MX_CAN2_Init(uint8_t mod)
{
	 	GPIO_InitTypeDef GPIO_InitStructure; 
	  CAN_InitTypeDef        CAN_InitStructure;
  	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
   	NVIC_InitTypeDef  NVIC_InitStructure;
    //ʹ�����ʱ��
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��PORTAʱ��	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);//ʹ��CAN1ʱ��	
	
    //��ʼ��GPIO
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12| GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��PA11,PA12
	
	  //���Ÿ���ӳ������
	  GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_CAN2); //GPIOB5����ΪCAN2
	  GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_CAN2); //GPIOB6����ΪCAN2
	  
  	//CAN��Ԫ����
   // CAN Baudrate = 250KBps (CAN clocked at 36 MHz) 
		CAN_InitStructure.CAN_TTCM = DISABLE;//��ʱ�䴥��ͨѶģʽ
		CAN_InitStructure.CAN_ABOM = DISABLE;//����Զ����߹���
		CAN_InitStructure.CAN_AWUM = DISABLE;//˯��ģʽͨ���������
		CAN_InitStructure.CAN_NART = ENABLE;//��ֹ�����Զ�����
		CAN_InitStructure.CAN_RFLM = DISABLE;//���Ĳ�����,�µĸ��Ǿɵ�
		CAN_InitStructure.CAN_TXFP = DISABLE;//���ȼ��ɱ��ı�ʶ������
		CAN_InitStructure.CAN_Mode =  mod;//����ģʽΪ�ػ�ģʽ
		CAN_InitStructure.CAN_SJW = CAN_SJW_4tq;//����ͬ����Ծ���Ϊ1��ʱ�䵥λ
		CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;//ʱ���1ռ��8��ʱ�䵥λ
		CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;//ʱ���2ռ��7��ʱ�䵥λ
		CAN_InitStructure.CAN_Prescaler = 8;		//��Ƶϵ��
  	CAN_Init(CAN2, &CAN_InitStructure);   // ��ʼ��CAN1 
    
		//���ù�����
 	  CAN_FilterInitStructure.CAN_FilterNumber=14;	  //������0
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//������0������FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //���������0
  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
	
	  CAN_ITConfig(CAN2,CAN_IT_FMP0,ENABLE);				//FIFO0????????.		    
	  NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;     // ?????1
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;            // ?????0
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
}

void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;
  CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);
	Task_CAN2_IRQ( RxMessage.ExtId , RxMessage.DLC, RxMessage.Data);
	if( (RxMessage.ExtId &0xFFFFFF00) == 0x141ff500)
	printf("ID:%02x [%d] [%d] [%d] [%d] [%d] [%d] [%d] [%d] \r\n",RxMessage.ExtId , RxMessage.Data[0] , RxMessage.Data[1] , RxMessage.Data[2] , RxMessage.Data[3], RxMessage.Data[4], RxMessage.Data[5], RxMessage.Data[6], RxMessage.Data[7]);
}
