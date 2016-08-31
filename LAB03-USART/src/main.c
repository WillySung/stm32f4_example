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

    while(1) {}
}

/*--------------Initial USART--------------*/

void init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = TX | RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //connect PA2 and PA3 with the USART2 AF
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);

    //Enable USART2 receive interrupt and make NVIC to USART2_IRQHandler()
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART2, ENABLE);

}
/*--------------Initial USART--------------*/

void USART_puts(USART_TypeDef *USARTx, char *str)
{
    while(*str){
        USART_SendData(USARTx, *str++);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    }
}

//Interrupt
void USART2_IRQHandler(void)
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE)){
        
        Receive_data = USART_ReceiveData(USART2);
        if(Receive_data == '1'){
            GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
            USART_puts(USART2, Receive_data);
        }
        else{
            USART_puts(USART2, "hello\r\n");
        }

        /*static uint8_t count = 0;

        if(count < MAX_STRLEN){
            received_string[count] = Receive_data;
            if(received_string[count] != NULL){
                Receive_String_Ready = 1;
                count =0;
            }
            else{
                count++;
            }
        }
        else{
            Receive_String_Ready = 1;
            count = 0;
        }
        if(Receive_String_Ready){
            USART_puts(USART2, received_string);
            USART_puts(USART2, "\r\n");

            Receive_String_Ready = 0;
            for(int i = 0; i<MAX_STRLEN; i++){
                received_string[i] = 0;
            }
        }*/
    }
}