#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include <stdio.h>

const uint16_t LEDS = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
const uint16_t USER_BTN = GPIO_Pin_0;

void init_Leds();
void init_Button();
void init_Exti();
void EXTI0_IRQHandler();

void Delay();
void setSystick();
void SysTick_Handler();