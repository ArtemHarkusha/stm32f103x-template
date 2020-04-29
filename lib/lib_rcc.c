#include "lib_rcc.h"
/* 
 *It can be HSE and HSI clocks*
 *
 *
 */

uint32_t RCC_EnableHSE(void)
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
            RCC->CFGR |= 0x01U;
            
            //while((RCC->CFGR & (0x03U << 2)) != (0x01U << 2))
            // {
            // }
            //
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x04)
    {
    }
            return (uint32_t)0x00U;
        }
   }

   /* normally we should not be here. */
   /* Let's reset HSEON */
   RCC->CR &= ~(0x01U << 16);
   /* End return error. */
   return (uint32_t)0x01U;
}

uint32_t RCC_ConfigHighSpeedClock(RCC_SysClockConfig_TypeDef * clock_config)
{
    if (clock_config->SysClockSource == RCC_SysClockSource_HSE)
    {
      return  RCC_EnableHSE();
    }
    return 0x00U;
}
