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
    setSysTick();
    init();

    while(1) {
        loop();
    }
}

void init()
{
    init_Leds();
    init_Timer();
    init_PWM();
}


void init_Leds()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = LEDS;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;   
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
}
void init_Timer()
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;     //Create TIM base init structure

    TIM_TimeBaseStructure.TIM_Period = 1680-1;         //Let PWM frequency = 100Hz ( 84MHz/[(1680-1+1)*(500-1+1)] )
    TIM_TimeBaseStructure.TIM_Prescaler = 500-1;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
}

void init_PWM()
{
    TIM_OCInitTypeDef TIM_OCInitStructure;             //Create TIM output compare init sructure

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM4 , &TIM_OCInitStructure);
    TIM_OC2Init(TIM4 , &TIM_OCInitStructure);
    TIM_OC3Init(TIM4 , &TIM_OCInitStructure);
    TIM_OC4Init(TIM4 , &TIM_OCInitStructure);

    TIM_Cmd(TIM4,ENABLE);
}

void loop()
{
    switch(brightLed){
        case 1000: delta=-1;
                   break;
        case 1:    delta=1;
                   break;
    }

    brightLed += delta;

    TIM_SetCompare1(TIM4, brightLed);
    TIM_SetCompare2(TIM4, brightLed);
    TIM_SetCompare3(TIM4, brightLed);
    TIM_SetCompare4(TIM4, brightLed);
    Delay(1);
}
