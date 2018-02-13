#include "iwdg.h"
#include "stm32f4xx_iwdg.h"


void MX_IWDG_Init(void)
{
		IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//????PR?RLR
		IWDG_SetPrescaler(IWDG_Prescaler_32);  //??PR????
		IWDG_SetReload(200);  //??RLR
		IWDG_Enable();//KR??0xCCCC
}


void MX_IWDG_Reload(void)
{
		IWDG_ReloadCounter();  
}

