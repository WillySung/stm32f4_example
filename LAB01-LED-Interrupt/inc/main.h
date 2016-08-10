#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include <stdio.h>


void initialize();
void EXTI0_IRQHandler();

void Delay();
void setSystick();
void SysTick_Handler();