/*
External Interrupt (EXTI) Example
    - Modified blinky with pushbutton code
        to use EXTI instead of Polling
*/
#include "main.h"

/*-----------------Delay----------------------*/
volatile uint32_t msTicks;

void SysTick_Handler(void) {
    if(msTicks != 0) msTicks++;
}

void Delay(uint32_t delaytime){
    msTicks = delaytime;
    while (msTicks != 0);
}

void setSysTick(){
    // ---------- SysTick timer (1ms) -------- //
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }
}
/*-----------------Delay----------------------*/

void init_Leds() {

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = LEDS;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void init_Button(){

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Pin = USER_BTN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void init_Exti(){

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;                    //connect PA0 to EXTI0
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;        //trigger on rising edge(as button pressed)
                                                                  //trigger on falling edge is also feasible
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                     //enable the interrupt
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;        //Function name of EXTI_Line0 IRQHandler
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

void EXTI0_IRQHandler(void) {
    // Make sure the interrupt flag is set for EXTI0
    if(EXTI_GetITStatus(EXTI_Line0) != RESET){
        GPIO_ToggleBits(GPIOD , LEDS);

        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

int main(void) {
    setSysTick();
    init_Leds();
    init_Button();
    init_Exti();

    // Turn on LED
    GPIO_SetBits(GPIOD, LEDS);

    while(1);                         //do nothing because we have interrupt
    return 0;
}