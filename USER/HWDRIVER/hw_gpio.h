/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* Function------------------------------------------------------------------*/
uint32_t	hw_gpio_Read(int sw);				// sw: 0-29
void 			hw_gpio_PowerOn(int pw);		// pw:0-7
void 			hw_gpio_PowerOff(int pw);		// pw:0-7
void 			hw_gpio_V24OutOn(int ch);		// ch:0-15
void 			hw_gpio_V24OutOff(int ch);	// ch:0-15
void      hw_gpio_V24OutToggle(int ch);// ch:0-15
uint32_t	hw_ecu_On(int sw);
uint32_t	hw_ecu_Off(int sw);
uint32_t	hw_ecu_Toggle(int sw);			// sw: 0-1

