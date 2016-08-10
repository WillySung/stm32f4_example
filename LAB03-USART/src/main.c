#include "main.h"
/*
Wiring connections:
    STM32F4             CP2102
    PA2 (USART2 Tx) ->  Rx
    PA3 (USART2 Rx) ->  Tx
*/

/*--------------Delay--------------*/

volatile uint32_t msTicks;

void SysTick_Handler(void)
{
    if(msTicks != 0)msTicks--;
}

void Delay(uint32_t delaytime)
{
    msTicks = delaytime;
    while(msTicks != 0);
}

void setSysTick()
{
    //Interrupt 1000 times per second
    if(SysTick_Config(SystemCoreClock / 1000)) {
        while(1) {};
    }
}
/*--------------Delay--------------*/

int main()
{
    init();
    setSysTick();

    while(1) {

    }
}

/*--------------Initial USART--------------*/

void init()
{
    /*
        Fill the code here!!!
    */
}
/*--------------Initial USART--------------*/

void USART_puts(USART_TypeDef *USARTx, volatile char *str)
{
    /*
        Fill the code here!!!
    */
}

//Interrupt
void USART2_IRQHandler(void)
{
    /*
        Fill the code here!!!
    */
}