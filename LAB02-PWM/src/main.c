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
    init();
    setSysTick();

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

/*--------------Initial LEDs--------------*/

void init_Leds()
{
    /*
        Fill the code here!!!
    */
}
void init_Timer()
{
    /*
        Fill the code here!!!
    */
}

void init_PWM()
{
    /*
        Fill the code here!!!
    */
}

void loop()
{
    /*
        Fill the code here!!!
    */
}
