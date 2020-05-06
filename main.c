#include "main.h"
//#include "lib/lib_gpio.h"

void delay(int millis) {
    while (millis-- > 0) {
        volatile int x = 5971;
        while (x-- > 0) {
            __asm("nop");
        }
    }
}

void time_init()
{
    //enable takting on TIM1
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    TIM1->SMCR &= ~TIM_SMCR_SMS;
    TIM1->CR1 = TIM_CR1_CEN;

    TIM1->PSC = 719;
    TIM1->ARR = 24999;

    TIM1->DIER |= TIM_DIER_UIE;

    NVIC_EnableIRQ (TIM1_UP_IRQn);

}

void TIM1_UP_IRQHandler(void) {

    TIM1->SR &= ~ TIM_SR_UIF;
      
    GPIO_ToggleBits(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
         
}

int main(void) {

RCC_PLLCLKConfig_TypeDef PLL;
PLL.RCC_PLLMul_Coef = RCC_PLLMul_9;
PLL.RCC_PLLCLK_Source = RCC_PLLCLKSource_HSE_Div1;

RCC_HSCLKConfig_TypeDef CLK;
CLK.RCC_SYSCLK_Source = RCC_SYSCLKSource_PLL;
CLK.RCC_SYSCLK_Prescaler = RCC_SYSCLK_Div1;
CLK.RCC_APB1CLK_Prescaler = RCC_HCLK_Div1;
CLK.RCC_APB2CLK_Prescaler = RCC_HCLK_Div1;
CLK.RCC_SYSCLK_Frequency = 72;
CLK.PLLClockConfig = &PLL;

RCC_ConfigHSCLK(&CLK);
GPIO_enable_clock(GPIOC);
GPIO_enable_clock(GPIOB);
GPIO_enable_clock(GPIOA);

time_init();


   GPIO_Pins_Config_TypeDef var; 
   var.Mode = OUT_OD;
   var.Speed = S50M;

   // GPIOC_Pin_13_Init()
   GPIO_Config_Pins(GPIOC, GPIO_Pin_13, &var);
   GPIO_Config_Pins(GPIOC, GPIO_Pin_15, &var);
   GPIO_Config_Pins(GPIOB, GPIO_Pin_12, &var);

   var.Mode = OUT_AF_PP;
   var.Speed = S50M;

   GPIO_Config_Pins(GPIOA, GPIO_Pin_8, &var);
    // main loop
    while(1) {
 //       GPIO_TogglePins(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
//        delay(DELAY);
//        GPIO_TogglePins(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
//        delay(DELAY);
       // if (GPIOB->IDR & GPIO_Pin_12)
        //{
         //   GPIO_SetBits(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
        //}
        //else
       // {
        //    GPIO_ResetBits(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
        //}
        //Set bit
       // GPIO_SetBits(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
       // GPIO_SetBits(GPIOB, GPIO_Pin_12);
       // delay(DELAY);
        
        //Reset bit
        //GPIO_ResetBits(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
       // GPIO_ResetBits(GPIOB, GPIO_Pin_12);
       // delay(DELAY);
    }

}
