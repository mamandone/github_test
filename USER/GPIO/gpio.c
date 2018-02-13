/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/

void MX_GPIO_ECU_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
			/* GPIO Ports Clock Enable */
		RCC_AHB1PeriphClockCmd(
													 RCC_AHB1Periph_GPIOC
													|RCC_AHB1Periph_GPIOB
													, ENABLE);//使能GPIOC时钟
			
		GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_11|GPIO_Pin_12;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOC, &GPIO_InitStruct);
		
		GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void MX_GPIO_Init(void)
{
		
		GPIO_InitTypeDef GPIO_InitStruct;
	  /* GPIO Ports Clock Enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA
	                      |RCC_AHB1Periph_GPIOB
												|RCC_AHB1Periph_GPIOC
												|RCC_AHB1Periph_GPIOD
												|RCC_AHB1Periph_GPIOE
												, ENABLE);//使能GPIOG时钟
	 /* Configure GPIO pins : PB */
  GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	 /* Configure GPIO pins : PB */
  GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_12;
  GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
	

	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	
	/*Configure GPIO pin : PE */
  GPIO_InitStruct.GPIO_Pin    = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode   = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd   = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed  = GPIO_Low_Speed;
  GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType  = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

}

//void MX_GPIO_Init(void)
//{

//  GPIO_InitTypeDef GPIO_InitStruct;

//  /* GPIO Ports Clock Enable */
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA
//	                      |RCC_AHB1Periph_GPIOB
//												|RCC_AHB1Periph_GPIOC
//												|RCC_AHB1Periph_GPIOD
//												|RCC_AHB1Periph_GPIOE
//												|RCC_AHB1Periph_GPIOF
//												|RCC_AHB1Periph_GPIOG
//	                      |RCC_AHB1Periph_GPIOH, ENABLE);//使能GPIOG时钟

//	/*****************INPUT*****************/
//  
//	/*Configure GPIO pins : PA */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOA, &GPIO_InitStruct);
//	
//	
//	/*Configure GPIO pins : PB */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOB, &GPIO_InitStruct);
//	
//	/*Configure GPIO pins : PC */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOC, &GPIO_InitStruct);
//	
//	/*Configure GPIO pins : PD */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOD, &GPIO_InitStruct);
//	
//	/*Configure GPIO pins : PE */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOE, &GPIO_InitStruct);
//	
//	/*Configure GPIO pins : PG */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOG, &GPIO_InitStruct);	
//	
//	/*****************OUTPUT*****************/	

//  /*Configure GPIO pin : PC */
//  //HAL_GPIO_WritePin(GPIOC, GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9, GPIO_Pin_RESET);
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
//  GPIO_Init(GPIOC, &GPIO_InitStruct);

//  /*Configure GPIO pin : PD */
//	//HAL_GPIO_WritePin(GPIOD, GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15, GPIO_Pin_RESET);
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
//  GPIO_Init(GPIOD, &GPIO_InitStruct);

//  /*Configure GPIO pin : PE */
//	//HAL_GPIO_WritePin(GPIOE, GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_12, GPIO_Pin_RESET);
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_12;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
//  GPIO_Init(GPIOE, &GPIO_InitStruct);

//  /*Configure GPIO pin : PF */
//	//HAL_GPIO_WritePin(GPIOF, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15, GPIO_Pin_RESET);
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
//  GPIO_Init(GPIOF, &GPIO_InitStruct);

//  /*Configure GPIO pin : PG */
//	//HAL_GPIO_WritePin(GPIOG, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7, GPIO_Pin_RESET);
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
//  GPIO_Init(GPIOG, &GPIO_InitStruct);
//	

//}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
