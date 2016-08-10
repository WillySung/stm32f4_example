#include "main.h"

int main()
{
    init_Leds();
    init_Button();
    setSysTick();

    while(1) {
        loop();
    }
}
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

/*--------------Initial LEDs--------------*/

void init_Leds()
{
    /*
        Fill the code here!!!
    */
}
/*--------------Initial LEDs--------------*/

/*--------------Initial Button--------------*/

void init_Button()
{
    /*
        Fill the code here!!!
    */
}
/*--------------Initial Button--------------*/

void loop()
{
    /*
        Goal : Change the led state by pressing the user button.
        The pins of Leds have been declared in LAB02/inc/main.h
        Fill the code here!
    */
}
