#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include <stdio.h>

const uint16_t LEDS = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

int delta = 1;
int brightLed = 0;

void init();
void loop();

void init_Leds();
void init_Timer();
void init_PWM();

void Delay();
void setSystick();
void SysTick_Handler();