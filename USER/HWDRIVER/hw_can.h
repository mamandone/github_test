/* Includes ------------------------------------------------------------------*/
#include "can.h"

uint32_t 	CanTx(unsigned long ID, uint8_t DLC, uint8_t *pData);
uint32_t  CanRx(unsigned long *pID, uint8_t *pDLC, uint8_t *pData);

uint32_t 	Can2Tx(unsigned long ID, uint8_t DLC, uint8_t *pData);
uint32_t  Can2Rx(unsigned long *pID, uint8_t *pDLC, uint8_t *pData);

