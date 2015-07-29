#include "main.h"

/* leds in the board will fade */
 int count=0,i=1;
 int on=300,off=0,ms=200;
 int main(void) {
   init();
     do {
   
        loop();
     
    } while (1);
}

void init() {
    initButton(); //初始按鈕
    initLeds();   
    initTimer();
    initPWM();
    
}

void loop() {
 
  //switch(brightLed1) {           //brightLed1 = 0;   brigthLed2 = 5;
                                                            //const uint16_t LEDS = GPIO_Pin_13 | GPIO_Pin_15;;
                                                            //const uint16_t USER_BUTTON = GPIO_Pin_0;
                                                            //int lastButtonStatus = RESET;
  //      case 299: delta=-1; break;
  //      case 1: delta=1; break;

  //  }

 //   brightLed1 += delta;
 
   switch(count){
   case 0:
   i=1;
   TIM_SetCompare1(TIM4, on);
   TIM_SetCompare2(TIM4, off);
   TIM_SetCompare3(TIM4, off);
   TIM_SetCompare4(TIM4, off);
   delay(ms);  
   count=count+i;  
   break;

   case 1:
   TIM_SetCompare1(TIM4, off);
   TIM_SetCompare2(TIM4, on);
   TIM_SetCompare3(TIM4, off);
   TIM_SetCompare4(TIM4, off);
   delay(ms);
   count=count+i;
   break;

   case 2:
   TIM_SetCompare1(TIM4, off);
   TIM_SetCompare2(TIM4, off);
   TIM_SetCompare3(TIM4, on);
   TIM_SetCompare4(TIM4, off);
   delay(ms);
   count=count+i;
   break;

    case 3:
   TIM_SetCompare1(TIM4, off);
   TIM_SetCompare2(TIM4, off);
   TIM_SetCompare3(TIM4, off);
   TIM_SetCompare4(TIM4, on);
   TIM_SetCompare1(TIM5, off);
   delay(ms);
   count=count+i;
   break;

   case 4:
   TIM_SetCompare4(TIM4, off);
   TIM_SetCompare1(TIM5, on);
   TIM_SetCompare2(TIM5, off);
   TIM_SetCompare3(TIM5, off);
   TIM_SetCompare4(TIM5, off);
   delay(ms);
   count=count+i;
   break;
 
   case 5:
   TIM_SetCompare1(TIM5, off);
   TIM_SetCompare2(TIM5, on);
   TIM_SetCompare3(TIM5, off);
   TIM_SetCompare4(TIM5, off);
   delay(ms);
   count=count+i;
   break;

   case 6 :
   TIM_SetCompare1(TIM5, off);
   TIM_SetCompare2(TIM5, off);
   TIM_SetCompare3(TIM5, on);
   TIM_SetCompare4(TIM5, off);
   delay(ms);
   count=count+i;
   break;

   case 7: 
   TIM_SetCompare1(TIM5, off);
   TIM_SetCompare2(TIM5, off);
   TIM_SetCompare3(TIM5, off);
   TIM_SetCompare4(TIM5, on);
   delay(ms);
   count=count+i;
   break;

   case 8:
   {
   int k;
   for(k=0;k<3;k++){
   LedToggle();
   delay(ms);
   }
   i=-1;
   count=count+i;
   break;
   }
    }






  //  TIM_SetCompare4(TIM4, 300 - brightLed1 % 300); // set brightness  in channel4
   // TIM_SetCompare3(TIM4, 300 - brightLed1 % 300); // set brightness  in channel3
   // TIM_SetCompare2(TIM4, 300 - brightLed1 % 300); // set brightness  in channel2
   // TIM_SetCompare1(TIM4, 300 - brightLed1 % 300); // set brightness  in channel1




    uint8_t currentButtonStatus = GPIO_ReadInputDataBit(GPIOA, USER_BUTTON);
    if (lastButtonStatus != currentButtonStatus && currentButtonStatus != RESET) {
        brigthLed2 *= 2;
        if (brigthLed2 >= 500 ) {
            brigthLed2 = 5;
        }
        TIM_SetCompare2(TIM4, brigthLed2);
    }
    lastButtonStatus = currentButtonStatus;

    delay(4);
}

void delay(uint32_t ms) {
    ms *= 3360;
    while(ms--) {
        __NOP();
    }
}

void initButton() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef gpio;
    GPIO_StructInit(&gpio);
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_Pin = USER_BUTTON;
    GPIO_Init(GPIOA, &gpio);
}

void initLeds() {
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //portD enable
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // portA enable
     

    GPIO_InitStructure.GPIO_Pin = LEDS;  // PD12,13,14,15
    //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  //alternate function
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //push/pull configuration
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //  pull up resistor
   
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOA, &GPIO_InitStructure);   

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);

     GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
     GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
     GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5);
     GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM5);

}

void initTimer() {
    /* TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    /* Compute the prescaler value */
    u32 PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 21000000) - 1;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 1000;
    TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
}

void initPWM() {
    TIM_OCInitTypeDef TIM_OCInitStructure;

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

//---------set pwm channel in timer4-------------
    /* PWM1 Mode configuration: Channel2 (GPIOD Pin 13)*/
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //channel 2
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel4 (GPIOD Pin 15)*/
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //channel 4
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

    
    /* PWM1 Mode configuration: Channel3 (GPIOD Pin 12)*/
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //channel 1
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

    
    /* PWM1 Mode configuration: Channel1 (GPIOD Pin 14)*/
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //channel 3
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
//---------------------------

    TIM_Cmd(TIM4, ENABLE);


//---------set pwm channel in timer5-------------
    /* PWM1 Mode configuration: Channel (GPIOD Pin 13)*/
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //channel 1
    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel4 (GPIOD Pin 15)*/
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //channel 2
    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

    
    /* PWM1 Mode configuration: Channel3 (GPIOD Pin 12)*/
    TIM_OC3Init(TIM5, &TIM_OCInitStructure);  //channel 3
    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

    
    /* PWM1 Mode configuration: Channel1 (GPIOD Pin 14)*/
    TIM_OC4Init(TIM5, &TIM_OCInitStructure);  //channel 4
    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
//---------------------------

    TIM_Cmd(TIM5, ENABLE);



}
 void LedToggle(){
   TIM_SetCompare1(TIM4, on);
   TIM_SetCompare2(TIM4, on);
   TIM_SetCompare3(TIM4, on);
   TIM_SetCompare4(TIM4, on);
   TIM_SetCompare1(TIM5, on);
   TIM_SetCompare2(TIM5, on);
   TIM_SetCompare3(TIM5, on);
   TIM_SetCompare4(TIM5, on);
   delay(ms);
   TIM_SetCompare1(TIM4, off);
   TIM_SetCompare2(TIM4, off);
   TIM_SetCompare3(TIM4, off);
   TIM_SetCompare4(TIM4, off);
   TIM_SetCompare1(TIM5, off);
   TIM_SetCompare2(TIM5, off);
   TIM_SetCompare3(TIM5, off);
   TIM_SetCompare4(TIM5, off);
  
}





