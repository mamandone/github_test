/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* Hardware Define------------------------------------------------------------*/
struct		GPIO_PIN
{
			GPIO_TypeDef *GPIOx;
			uint16_t			GPIO_PIN_x;
};

static	struct	GPIO_PIN		SWITCH_INs[32]=
{
			GPIOB,	GPIO_Pin_10,  // --> 1
			GPIOB,	GPIO_Pin_11,  // --> 2 
			GPIOB,	GPIO_Pin_12,  // --> 3
			GPIOB,	GPIO_Pin_13,  // --> 4
			GPIOB,	GPIO_Pin_14,  // --> 5
			GPIOB,	GPIO_Pin_15,  // --> 6
	    GPIOD,	GPIO_Pin_8,   // --> 7
	    GPIOD,	GPIO_Pin_9,   // --> 8
			GPIOD,	GPIO_Pin_10,  // --> 9
			GPIOD,	GPIO_Pin_11,  // --> 10
			GPIOD,	GPIO_Pin_12,  // --> 11
			GPIOD,  GPIO_Pin_13,  // --> 12
			GPIOD,  GPIO_Pin_14,  // --> 13
			GPIOD,  GPIO_Pin_15,  // --> 14
			GPIOC,	GPIO_Pin_6,   // --> 15
			GPIOC,	GPIO_Pin_7,   // --> 16
			GPIOC,	GPIO_Pin_9,   // --> 17
			GPIOD,	GPIO_Pin_0,   // --> 18
			GPIOD,	GPIO_Pin_1,   // --> 19			
			GPIOC,	GPIO_Pin_8,   // --> 20 
			GPIOD,	GPIO_Pin_3,   // --> 21
			GPIOD,	GPIO_Pin_2,   // --> 22
			GPIOD,	GPIO_Pin_5,   // --> 23
			GPIOD,	GPIO_Pin_4,   // --> 24
			GPIOD,	GPIO_Pin_7,   // --> 25
			GPIOD,	GPIO_Pin_6,   // --> 26
		  GPIOB,	GPIO_Pin_4,   // --> 27
			GPIOB,	GPIO_Pin_3,   // --> 28
			GPIOB,	GPIO_Pin_6,   // --> 29
			GPIOB,	GPIO_Pin_5,   // --> 30
			GPIOB,	GPIO_Pin_8,   // --> 31
			GPIOB,	GPIO_Pin_7,   // --> 32

		
};

static	struct	GPIO_PIN		POWER_OUTs[1]=
{
			GPIOC,	GPIO_Pin_12
};

static struct GPIO_PIN     ECU_Statua_out[4]=
{
			GPIOC,	GPIO_Pin_10,
			GPIOC,	GPIO_Pin_11,
			GPIOC,	GPIO_Pin_12,
			GPIOB,	GPIO_Pin_10
};

static	struct	GPIO_PIN		V24_OUTs[18]=
{

			GPIOE,	GPIO_Pin_4,   //---> 1
	    GPIOE,	GPIO_Pin_3,   //---> 2
			GPIOE,	GPIO_Pin_5,   //---> 3
			GPIOE,	GPIO_Pin_2,   //---> 4
	    GPIOE,	GPIO_Pin_15,  //---> 5
			GPIOE,	GPIO_Pin_6,   //---> 6
    	GPIOE,	GPIO_Pin_14,  //---> 7
	    GPIOE,	GPIO_Pin_1,   //---> 8
	    GPIOE,	GPIO_Pin_13,  //---> 9
			GPIOE,	GPIO_Pin_0,   //---> 10
			GPIOE,	GPIO_Pin_11,  //---> 11
			GPIOE,	GPIO_Pin_7,   //---> 12
			GPIOE,	GPIO_Pin_10,  //---> 13
			GPIOE,	GPIO_Pin_8,   //---> 14
			GPIOE,	GPIO_Pin_12,  //---> 15
			GPIOE,	GPIO_Pin_9,   //---> 16
			GPIOC,	GPIO_Pin_10,  //---> 17
			GPIOC,	GPIO_Pin_11   //---> 18
	
};


static unsigned char ECU_Status_Data[3];
static unsigned char V24_Togger_Data[16];


/* Function------------------------------------------------------------------*/
uint32_t	hw_gpio_Read(int sw)			// sw: 0-29
{
			//return	SWITCH_INs[sw].GPIOx->IDR & SWITCH_INs[sw].GPIO_PIN_x;//(0/!0)
	uint8_t data =  0;
	data = GPIO_ReadInputDataBit(  SWITCH_INs[sw].GPIOx , SWITCH_INs[sw].GPIO_PIN_x);
	
	
	/*
			uint32_t bitstatus = 0x00000000;

			if ((SWITCH_INs[sw].GPIOx->IDR & SWITCH_INs[sw].GPIO_PIN_x) != (uint32_t)Bit_RESET)
			{
				bitstatus = Bit_SET;
			}
			else
			{
				bitstatus = Bit_RESET;
			}
			return bitstatus;
	*/
	return (data&0xFFFFFFFF);
}

uint32_t	hw_ecu_On(int sw)			  // sw: 0-1
{
			ECU_Statua_out[sw].GPIOx->BSRRH = (ECU_Statua_out[sw].GPIO_PIN_x);
			ECU_Status_Data[sw] = 1;
			return  0;
}

uint32_t	hw_ecu_Off(int sw)			// sw: 0-1
{
			ECU_Statua_out[sw].GPIOx->BSRRL = ECU_Statua_out[sw].GPIO_PIN_x;
			ECU_Status_Data[sw] = 0;
			return  0;
}

uint32_t	hw_ecu_Toggle(int sw)			// sw: 0-1
{
			if(ECU_Status_Data[sw] == 1)     { hw_ecu_Off(sw);}
			else if(ECU_Status_Data[sw] == 0){ hw_ecu_On (sw);}
			return  0;
}

void 			hw_gpio_PowerOn(int pw)		// pw:0-7
{
			POWER_OUTs[pw].GPIOx->BSRRH = (POWER_OUTs[pw].GPIO_PIN_x);
}

void 			hw_gpio_PowerOff(int pw)	// pw:0-7
{
			POWER_OUTs[pw].GPIOx->BSRRL = POWER_OUTs[pw].GPIO_PIN_x;
}

void 			hw_gpio_V24OutOff(int ch)	// ch:0-23
{
			V24_OUTs[ch].GPIOx->BSRRH = V24_OUTs[ch].GPIO_PIN_x;
			V24_Togger_Data[ch] = 0;
}

void 			hw_gpio_V24OutOn(int ch)	// ch:0-23
{
			V24_OUTs[ch].GPIOx->BSRRL = V24_OUTs[ch].GPIO_PIN_x;
			V24_Togger_Data[ch] = 1;
}

void      hw_gpio_V24OutToggle(int ch)	// ch:0-23
{
			//V24_OUTs[ch].GPIOx->ODR ^= V24_OUTs[ch].GPIO_PIN_x;
	
			if(V24_Togger_Data[ch] == 1)     { hw_gpio_V24OutOff(ch);}
			else if(V24_Togger_Data[ch] == 0){ hw_gpio_V24OutOn (ch);}
}


