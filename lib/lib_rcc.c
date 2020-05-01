#include "lib_rcc.h"
/* 
 *It can be HSE and HSI clocks*
 *
 *
 */
/* Configure HSE. Does not switch SYSCLOCK to HSE */
uint32_t RCC_HSEConfig(void)
{
   uint32_t counter;
   /* Set HSEON (Hight Speed External) bit to clock from external generator */
   RCC->CR |= 0x01U << 16;

   /* Wait for HSE to stabilize */
   for (counter = 0; counter < 0x3E8U; counter++)
   {
        /* As soon as HSE is ready it sets 17th bit in RCC_RC regestry. */
        if (RCC->CR & (0x01U << 17))
        {
            //RCC->CR &= ~(0x01U);
            //RCC->CFGR |= 0x01U;
            
            //while((RCC->CFGR & (0x03U << 2)) != (0x01U << 2))
            // {
            // }
            //
   // while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x04)
   // {
   // }
            return (uint32_t)0x00U;
        }
   }

   /* normally we should not be here. */
   /* Let's reset HSEON */
   RCC->CR &= ~(0x01U << 16);
   /* End return error. */
   return (uint32_t)0x01U;
}

void RCC_PLLConfig(RCC_PLLCLKConfig_TypeDef * config)
{
    if ((config->RCC_PLLCLK_Source & 0x10U) != 0x00U)
    {
        RCC->CFGR |= config->RCC_PLLCLK_Source << 16;
    }
    else
    {
        RCC->CFGR |= 0x01U << 16;
        RCC->CFGR |= 0x01U << 17;
    }

    RCC->CFGR |= config->RCC_PLLMul_Coef << 18;

    // Turn on PLL 
    RCC->CR |= (0x01U << 24);

    // Wait for PLL to init
    for(; ;)
    {
        // check PLLRDY flag in RCC_RC 
        if(RCC->CR & (0x01U << 25))
            break;
    }    
    RCC->CFGR |= (0x02U << 0U);

    while((RCC->CFGR & (0x03U << 2)) != (0x02U << 2))
    {
    }
}


uint32_t RCC_HSCLKConfig(RCC_HSCLKConfig_TypeDef * clock_config)
{

    /* Let's take care of Prescalers first */
    if (clock_config->RCC_SYSCLK_Source == RCC_SYSCLKSource_HSE)
    {
        RCC_EnableHSE();
    }

    if (clock_config->RCC_SYSCLK_Source == RCC_SYSCLKSource_HSI)
    {
        //RCC_EnableHSI();
    
    }
    if (clock_config->RCC_SYSCLK_Source == RCC_SYSCLKSource_PLL)
    {
        RCC_EnableHSE();
        RCC_PLLConfig(clock_config->PLLClockConfig);
    }

    RCC->CR &= ~(0x01U);

    //enable MCO output 
    RCC->CFGR |= 0x07U << 24;
    return 0x00U;
}
