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

int ClockInit()
{
  int StartUpCounter; 
    RCC_EnableHSE();

    // set PLL Multiplire to 9 and clock PPL from HSE 
    RCC->CFGR |= (0x02U << 18)
              | (0x01U << 16);
    
    // Turn on PLL 
    RCC->CR |= (0x01U << 24);

    // Wait for PLL to init
    for(StartUpCounter=0; ; StartUpCounter++)
    {
        // check PLLRDY flag in RCC_RC 
        if(RCC->CR & (0x01U << 25))
            break;
        
        if(StartUpCounter > 0x1000)
        {
            RCC->CR &= ~(0x01U << 16);
            RCC->CR &= ~(0x01U << 24);
            return 2;
        }
    }
   
    
    FLASH->ACR |= (0x1U << 0U);

    //RCC->CFGR |= (0x04U << 8);

    // make  PLL a system clock. 
    // set SW bits to 10
    RCC->CFGR |= (0x02U << 0U);

    while((RCC->CFGR & (0x03U << 2)) != (0x02U << 2))
    {
    }

    RCC->CR &= ~(0x01U);
    return 0;
}

int main(void) {

//ClockInit();
//RCC_EnableHSE();

    // enable clock on APB2
   // pointer 'register_address' of type uint32_t points to 0x40021018 address in MC memory
   // U in the end means unsigned. (uint32_t *) is a type convension aka cast
//volatile uint32_t * register_address = (uint32_t *) 0x40021018U;
  //  *(volatile uint32_t *)register_address |= 0x10;

RCC_PLLClockConfig_TypeDef PLLCFG;
PLLCFG.PLLClockSource = RCC_PLLClockSorce_HSE;
PLLCFG.PLLMulCoef = PLLMulCoef_MUL9;

RCC_SysClockConfig_TypeDef  CLOCK;
CLOCK.SysClockSource = RCC_SysClockSource_HSE;
CLOCK.SysClockPrescaler = RCC_SysClockPrescaler_NONE;
CLOCK.APB1ClockPrescaler = RCC_PeriphClockPrescaler_NONE;
CLOCK.APB2ClockPrescaler = RCC_PeriphClockPrescaler_NONE;

RCC_ConfigHighSpeedClock(&CLOCK);

GPIO_enable_clock(GPIOC);
GPIO_enable_clock(GPIOB);

   GPIO_Pins_Config_TypeDef var; 
   var.Mode = OUT_OD;
   var.Speed = S2M;

   // GPIOC_Pin_13_Init()
   GPIO_Config_Pins(GPIOC, GPIO_Pin_13, &var);
   GPIO_Config_Pins(GPIOC, GPIO_Pin_15, &var);
   GPIO_Config_Pins(GPIOB, GPIO_Pin_12, &var);
    // main loop
    while(1) {

       // if (GPIOB->IDR & GPIO_Pin_12)
        //{
         //   GPIO_SetBits(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
        //}
        //else
       // {
        //    GPIO_ResetBits(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
        //}
        //Set bit
        GPIO_SetBits(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
        delay(DELAY);
        
        //Reset bit
        GPIO_ResetBits(GPIOC, (GPIO_Pin_13 | GPIO_Pin_15));
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
        delay(DELAY);
    }

}
