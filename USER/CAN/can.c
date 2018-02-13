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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//打开端口A时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);//打开CAN总线接口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	//复用功能
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//启动上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 PA11,PA12
	
	//引脚复用映射配置
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_CAN1);
	
	CAN_DeInit(CAN1);
	// CAN Baudrate = 250KBps (CAN clocked at 36 MHz) 
	CAN_InitStructure.CAN_TTCM = DISABLE;//非时间触发通讯模式
	CAN_InitStructure.CAN_ABOM = DISABLE;//软件自动离线管理
	CAN_InitStructure.CAN_AWUM = DISABLE;//睡眠模式通过软件唤醒
	CAN_InitStructure.CAN_NART = ENABLE;//禁止报文自动传送
	CAN_InitStructure.CAN_RFLM = DISABLE;//报文不锁定,新的覆盖旧的
	CAN_InitStructure.CAN_TXFP = DISABLE;//优先级由报文标识符决定
	CAN_InitStructure.CAN_Mode =  mod;//设置模式为回环模式
	CAN_InitStructure.CAN_SJW = CAN_SJW_4tq;//重新同步跳跃宽度为1个时间单位
	CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;//时间段1占用8个时间单位
	CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;//时间段2占用7个时间单位
	CAN_InitStructure.CAN_Prescaler = 8;		//分频系数
	CAN_Init(CAN1, &CAN_InitStructure);//初始化CAN1

	//CAN过滤器设置
	CAN_FilterInitStructure.CAN_FilterNumber = 0;//用过滤器0
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;//标识符屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;//设置为1个32位宽
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;	//32位ID高16位  设置标识符寄存器
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;	//32位ID低16位
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;	//32位MASK-ID高16位		设置标识符屏蔽寄存器
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;	//32位MASK-ID低16位
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;//关联到过滤器0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;	//激活过滤器
	CAN_FilterInit(&CAN_FilterInitStructure);	//过滤器初始化	
	
	
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
    //使能相关时钟
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能PORTA时钟	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);//使能CAN1时钟	
	
    //初始化GPIO
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12| GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化PA11,PA12
	
	  //引脚复用映射配置
	  GPIO_PinAFConfig(GPIOB,GPIO_PinSource12,GPIO_AF_CAN2); //GPIOB5复用为CAN2
	  GPIO_PinAFConfig(GPIOB,GPIO_PinSource13,GPIO_AF_CAN2); //GPIOB6复用为CAN2
	  
  	//CAN单元设置
   // CAN Baudrate = 250KBps (CAN clocked at 36 MHz) 
		CAN_InitStructure.CAN_TTCM = DISABLE;//非时间触发通讯模式
		CAN_InitStructure.CAN_ABOM = DISABLE;//软件自动离线管理
		CAN_InitStructure.CAN_AWUM = DISABLE;//睡眠模式通过软件唤醒
		CAN_InitStructure.CAN_NART = ENABLE;//禁止报文自动传送
		CAN_InitStructure.CAN_RFLM = DISABLE;//报文不锁定,新的覆盖旧的
		CAN_InitStructure.CAN_TXFP = DISABLE;//优先级由报文标识符决定
		CAN_InitStructure.CAN_Mode =  mod;//设置模式为回环模式
		CAN_InitStructure.CAN_SJW = CAN_SJW_4tq;//重新同步跳跃宽度为1个时间单位
		CAN_InitStructure.CAN_BS1 = CAN_BS1_12tq;//时间段1占用8个时间单位
		CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;//时间段2占用7个时间单位
		CAN_InitStructure.CAN_Prescaler = 8;		//分频系数
  	CAN_Init(CAN2, &CAN_InitStructure);   // 初始化CAN1 
    
		//配置过滤器
 	  CAN_FilterInitStructure.CAN_FilterNumber=14;	  //过滤器0
  	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; //32位 
  	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;////32位ID
  	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0x0000;//32位MASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;//过滤器0关联到FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; //激活过滤器0
  	CAN_FilterInit(&CAN_FilterInitStructure);//滤波器初始化
	
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
