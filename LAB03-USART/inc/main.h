#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "misc.h"
#include <stdio.h>

const uint16_t TX = GPIO_Pin_2;
const uint16_t RX = GPIO_Pin_3;

#define MAX_STRLEN 50
char received_string[MAX_STRLEN]; // this will hold the recieved string


/*the usart acept the command from RX when RX interrupt is trigger*/
unsigned char Receive_data;
uint8_t Receive_String_Ready = 0;


void Delay();
void setSystick();
void SysTick_Handler();
void init();
void USART_puts();
void USART2_IRQHandler();