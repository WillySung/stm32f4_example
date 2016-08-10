/*
External Interrupt (EXTI) Example
    - Modified blinky with pushbutton code
        to use EXTI instead of Polling
*/
#include "main.h"

/* counts 1ms timeTicks       */
volatile uint32_t msTicks;
void SysTick_Handler(void) {
    msTicks++;
}

//  Delays number of Systicks (happens every 1 ms)
void Delay(__IO uint32_t dlyTicks){
    uint32_t curTicks = msTicks;
    while ((msTicks - curTicks) < dlyTicks);
}

void setSysTick(){
    // ---------- SysTick timer (1ms) -------- //
    if (SysTick_Config(SystemCoreClock / 1000)) {
        // Capture error
        while (1){};
    }
}

void initialize() {
    /*
        Fill the code here!!!
    */
}

void EXTI0_IRQHandler(void) {
    // Make sure the interrupt flag is set for EXTI0
    /*
        Fill the code here!!!
    */
}

int main(void) {
    setSysTick();
    initialize();
    
    // Turn on LED
    GPIO_SetBits(GPIOD, GPIO_Pin_13);
    
    while(1){
        // Do nothing here, using interrupts
    }

    return 0;
}