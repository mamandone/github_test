/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* Data Buffer__--------------------------------------------------------------*/
CanTxMsg            TxMsg;     		/*!< transmit structure  */
CanRxMsg            RxMsg;     		/*!< reception structure */

/* Data Buffer__--------------------------------------------------------------*/
CanTxMsg            TxMsg_2;     		/*!< transmit structure  */
CanRxMsg            RxMsg_2;     		/*!< reception structure */

//#define CAN_ID_STD             ((uint32_t)0x00000000U)  /*!< Standard Id */
//#define CAN_ID_EXT             ((uint32_t)0x00000004U)  /*!< Extended Id */

/* Function------------------------------------------------------------------*/
uint32_t 	CanTx(unsigned long ID, uint8_t DLC, uint8_t *pData)
{
		uint8_t mbox;
		uint16_t i;
		TxMsg.ExtId = ID;
		TxMsg.DLC = DLC;
		TxMsg.Data[0] = pData[0];
		TxMsg.Data[1] = pData[1];
		TxMsg.Data[2] = pData[2];
		TxMsg.Data[3] = pData[3];
		TxMsg.Data[4] = pData[4];
		TxMsg.Data[5] = pData[5];
		TxMsg.Data[6] = pData[6];
		TxMsg.Data[7] = pData[7];
		TxMsg.IDE = CAN_ID_EXT;
		TxMsg.RTR = CAN_RTR_DATA;
		//hcan1.pTxMsg = &TxMsg;
		 mbox= CAN_Transmit(CAN1, &TxMsg);   
		 i=0;
		 while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
     if(i>=0XFFF){
			 return 0;
	   }
     return 1;		
}

uint32_t  	CanRx(unsigned long *pID, uint8_t *pDLC, uint8_t *pData)
{
			uint32_t result ;
			result = 0;
			if(CAN_MessagePending(CAN1,CAN_FIFO0))		              //查询是否有挂号的消息接收进来
			{
					CAN_Receive(CAN1,CAN_FIFO0,&RxMsg);
					result = 1;
			}
			
			if(RxMsg.IDE != CAN_ID_EXT)   return 0;
			if(RxMsg.RTR != CAN_RTR_DATA) return 0;

			*pID = RxMsg.ExtId;
			*pDLC = RxMsg.DLC;
			pData[0] =	RxMsg.Data[0] ;
			pData[1] =	RxMsg.Data[1] ;
			pData[2] =	RxMsg.Data[2] ;
			pData[3] =	RxMsg.Data[3] ;
			pData[4] =	RxMsg.Data[4] ;
			pData[5] =	RxMsg.Data[5] ;
			pData[6] =	RxMsg.Data[6] ;
			pData[7] =	RxMsg.Data[7] ;

			return result;
}


/* Function------------------------------------------------------------------*/
uint32_t 	Can2Tx(unsigned long ID, uint8_t DLC, uint8_t *pData)
{
		uint8_t mbox;
		uint16_t i;
		TxMsg_2.ExtId = ID;
		TxMsg_2.DLC = DLC;
		TxMsg_2.Data[0] = pData[0];
		TxMsg_2.Data[1] = pData[1];
		TxMsg_2.Data[2] = pData[2];
		TxMsg_2.Data[3] = pData[3];
		TxMsg_2.Data[4] = pData[4];
		TxMsg_2.Data[5] = pData[5];
		TxMsg_2.Data[6] = pData[6];
		TxMsg_2.Data[7] = pData[7];
		TxMsg_2.IDE = CAN_ID_EXT;
		TxMsg_2.RTR = CAN_RTR_DATA;
		//hcan1.pTxMsg = &TxMsg;
		 mbox= CAN_Transmit(CAN2, &TxMsg_2);   
		 i=0;
		 while((CAN_TransmitStatus(CAN2, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
     if(i>=0XFFF){
			 return 0;
	   }
     return 1;		
}

uint32_t  	Can2Rx(unsigned long *pID, uint8_t *pDLC, uint8_t *pData)
{
			uint32_t result ;
			result = 0;
			if(CAN_MessagePending(CAN2,CAN_FIFO0))		              //查询是否有挂号的消息接收进来
			{
					CAN_Receive(CAN2,CAN_FIFO0,&RxMsg_2);
					result = 1;
			}
			
			if(RxMsg_2.IDE != CAN_ID_EXT)   return 0;
			if(RxMsg_2.RTR != CAN_RTR_DATA) return 0;

			*pID  = RxMsg_2.ExtId;
			*pDLC = RxMsg_2.DLC;
			pData[0] =	RxMsg_2.Data[0] ;
			pData[1] =	RxMsg_2.Data[1] ;
			pData[2] =	RxMsg_2.Data[2] ;
			pData[3] =	RxMsg_2.Data[3] ;
			pData[4] =	RxMsg_2.Data[4] ;
			pData[5] =	RxMsg_2.Data[5] ;
			pData[6] =	RxMsg_2.Data[6] ;
			pData[7] =	RxMsg_2.Data[7] ;

			return result;
}

