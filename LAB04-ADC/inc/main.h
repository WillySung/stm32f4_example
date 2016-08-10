#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_adc.h"
#include "misc.h"
#include <stdio.h>

const uint16_t TX = GPIO_Pin_2;
const uint16_t RX = GPIO_Pin_3;

#define MAX_STRLEN 50
volatile unsigned char received_string[MAX_STRLEN]; // this will hold the recieved string


/*the usart acept the command from RX when RX interrupt is trigger*/
unsigned char Receive_data;
uint8_t Receive_String_Ready = 0;


//Some used functions
void init_GPIO();
void init_USART();
void init_ADC();
void ADC_IRQHandler()
int fputc()

void Delay();
void setSystick();
void SysTick_Handler();