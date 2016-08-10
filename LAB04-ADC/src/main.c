#include "main.h"

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
    init_GPIO();
    init_ADC();
    init_USART();
    setSysTick();

    while(1) {
    }
}


/*--------------Initial GPIO--------------*/

void init_GPIO()
{
    /*
        Fill the code here!!!
    */
   
}

void init_ADC()
{
    /*
        Fill the code here!!!
    */
}

void init_USART()
{
    /*
        Fill the code here!!!
    */
}


void ADC_IRQHandler(void)
{
    ADCConvertedValue=ADC_GetConversionValue(ADC1);
    ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
}


int fputc(int ch,FILE *f)
{
    USART_SendData(USART1, (u8)ch);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);

    return ch;

}

