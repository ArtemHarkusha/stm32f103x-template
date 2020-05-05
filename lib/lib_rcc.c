#include "lib_rcc.h"

/**
 * @brief  Enable MCO (Microcontroller Clock Output).
 * @param mco_config: CFGR register MCO configuration 3 bits.
 * @retval None
 */
void RCC_MCOEnable(uint8_t mco_config)
{
    /* Set 24-26 bits in CFGR regestry */
    uint32_t mask = ~(((0x01U << 3) - 0x01U) << 24);
    RCC->CFGR = (RCC->CFGR & mask) | (uint32_t)(mco_config << 24);
}

/**
* @brief Set SYSCLK prescaler.
* @param prescaler: CFGR register HPRE 4 bits.
* @note SYSCLK can not exeed 72 MHz.
* @retval None:
*/
void RCC_SetSyclkPrescaler(uint8_t prescaler)
{
    uint32_t mask = ~(((0x01U << 4) - 0x01U) << 4);
    RCC->CFGR = (RCC->CFGR & mask) | (uint32_t)(prescaler << 4);
}

/**
* @brief Set APB1 (Advanced Peripheral Bus) prescaler.
* @param prescaler: CFGR register PPRE1 3 bits.
* @note APB1 can not exeed 36 MHz.
* @retval None
*/
void RCC_SetAPB1Prescaler(uint8_t prescaler)
{
    uint32_t mask = ~(((0x01U << 3) - 0x01U) << 8);
    RCC->CFGR = (RCC->CFGR & mask) | (uint32_t)(prescaler << 8);
}

/**
* @brief Set APB2(Advanced Peripheral Bus) prescaler.
* @param prescaler: CFGR register PPRE2 3 bits.
* @retval None
*/
void RCC_SetAPB2Prescaler(uint8_t prescaler)
{
    uint32_t mask = ~(((0x01U << 3) - 0x01U) << 11);
    RCC->CFGR = (RCC->CFGR & mask) | (uint32_t)(prescaler << 11);
}

/**
* @brief Configure 3 prescalers: SYSCLK, AHB1, AHB2.
* @param clock_config: a pointer to RCC_HSCLKConfig_TypeDef struct containing needed 
* prescalers.
* @note SYSCLK can not exeed 72 Mhz.
* @note AHB1 can not exeed 36 MHz.
* @retval None
*/
void RCC_SetPrescalers(RCC_HSCLKConfig_TypeDef * clock_config)
{
    RCC_SetSyclkPrescaler(clock_config->RCC_SYSCLK_Prescaler);
    RCC_SetAPB1Prescaler(clock_config->RCC_APB1CLK_Prescaler);
    RCC_SetAPB2Prescaler(clock_config->RCC_APB2CLK_Prescaler);
}

/**
* @brief Set or reset FLASH_ACR prefetched buffer bit.
* @param state: new state of the prefetched buffer bit.
* @note Prefetched buffer state can be changed only when SYSCLK is lower than 24 MHz.
* and no prescaler is applied on AHB (SYSCLK)
* @retval None
*/
void RCC_SetFlashPrefetchedBuffer(FunctionalState state)
{
    
    uint32_t mask = ~(0x01U << 4);
    FLASH->ACR = (FLASH->ACR & mask) | (uint32_t)(state << 4);
}

/**
* @brief Set FLASH memory latency.
* @param latency: new FLASH access latency.
* @note 0x00U, if 0  MHz < SYSCLK ≤ 24 MHz
*       0x01U, if 24 MHz < SYSCLK ≤ 48 MHz
*       0x02U, if 48 MHz < SYSCLK ≤ 72 MHz 
* @retval None
*/
void RCC_SetFlashLatency(uint8_t latency)
{
    uint32_t mask = ~(0x07U);
    FLASH->ACR = (FLASH->ACR & mask) | (uint32_t)(latency);
}

/**
* @brief Configure HSI clock state.
* @param state: new state of HLI clock source.
* @note it will not switch SYSCLK to HLI.
* @todo: rename later when below functions are refactored.
* @retval None
*/
void RCC_ConfigHSI(FunctionalState state)
{
    /* if new state is DISABLE, disable HSI and exit */
    if (state == DISABLE)
    {
        RCC->CR &= ~(0x01U);
        return;
    }

    /* Set HSION (High Speed Internal) bit to enable internal generator */
    RCC->CR |= 0x01U;

   /* Wait for HSI to stabilize */
   /* It should be always fine since it's crystal's guts */
   for(; ;)
   {
        /* As soon as HSE is ready it sets 17th bit in RCC_RC regestry. */
        if (RCC->CR & (0x01U << 1))
        {
            break;
        }
   }
}

/**
* @brief Configure HSE clock state.
* @param state: new state of HSE clock source.
* @note it will not switch SYSCLK to HSE.
* @todo  split into several independent functions to actually config and enable/disable
* @retval None
*/
uint32_t RCC_ConfigHSE(FunctionalState state)
{
   uint32_t counter;
   /* if new state is DISABLE, disable and exit */
   if (state == DISABLE)
   {
        RCC->CR &= ~(0x01U << 16);
        return 0x00U;
   }
   /* Set HSEON (Hight Speed External) bit to enable external generator */
   RCC->CR |= 0x01U << 16;

   /* Wait for HSE to stabilize */
   for (counter = 0; counter < LOOPS_TO_STABILIZE; counter++)
   {
        /* As soon as HSE is ready it sets 17th bit in RCC_RC regestry. */
        if (RCC->CR & (0x01U << 17))
        {
            return (uint32_t)0x00U;
        }
   }

   /* normally we should not be here. */
   /* Let's reset HSEON */
   RCC->CR &= ~(0x01U << 16);
   /* End return error. */
   return (uint32_t)0x01U;
}

/**
* @brief Config PLL source clock.
* @param config: a pointer to RCC_PLLCLKConfig_TypeDef structure.
* @note  it will not switch SYSCLK to PLL
* @todo  split into several independent functions to actually config and enable/disable
* @retval None
*/
void RCC_ConfigPLL(RCC_PLLCLKConfig_TypeDef * config)
{
    uint32_t mask;
    switch(config->RCC_PLLCLK_Source)
    {
        /* if PLL source is HSI. HSI is always divided by 2 */
        case RCC_PLLCLKSource_HSI:
            /* Reset 16th bit to use HSI PLL source */
            RCC->CFGR &= ~(0x01U << 16);
            /* Reset HSE PLL prescaler bit */
            RCC->CFGR &= ~(0x01U << 17);
            break;
        /* if PLL source is HSE */
        case RCC_PLLCLKSource_HSE_Div1:
            /* Reset HSE PLL prescaler bit */
            RCC->CFGR &= ~(0x01U << 17);
            /* Set 16th bit to use HSE PLL source */
            RCC->CFGR |= 0x01U << 16;
            break;
        /* if PLL source is HSE divided by 2 */
        case RCC_PLLCLKSource_HSE_Div2:
            /* Set 17th bit to prescale HSE PLL source */
            RCC->CFGR |= 0x01U << 17;
            /* set 16th bit to use HSE PLL source  */
            RCC->CFGR |= 0x01U << 16;
            break;

        default:
            /* We should not get here */
            return;
    }
    
    /* configure PLL multiplication */
    mask = ~(((0x01U << 4) - 0x01U) << 18);
    RCC->CFGR = (RCC->CFGR & mask) | (uint32_t)(config->RCC_PLLMul_Coef << 18);

    // Turn on PLL 
    RCC->CR |= (0x01U << 24);
    /**
    * @todo get rid of infinite loop
    */
    /* Wait for PLL to init */
    for(; ;)
    {
        /* check PLLRDY flag in RCC_RC */
        if(RCC->CR & (0x01U << 25))
        {
            break;
        }
    }
}

/**
 * @brief Switch SYSCLK to the chosen clock source.
 * @param source: clock source to switch to.
 * @retval uint32_t: status code. failed if not 0x00U
 */
uint32_t RCC_SelectSysCLKSource(uint8_t source)
{
    uint32_t check_flag;
    switch(source)
    {
        case RCC_SYSCLKSource_HSI:
            RCC->CFGR &= ~(0x03U);
            check_flag = (uint32_t)(RCC_SYSCLKSource_HSI << 2);
            break;

        case RCC_SYSCLKSource_HSE:
            RCC->CFGR = (RCC->CFGR & ~(0x03U)) | (uint32_t)RCC_SYSCLKSource_HSE;
            check_flag = (uint32_t)(RCC_SYSCLKSource_HSE << 2);
            break;
            
        case RCC_SYSCLKSource_PLL:
            RCC->CFGR = (RCC->CFGR & ~(0x03U)) | (uint32_t)RCC_SYSCLKSource_PLL;
            check_flag = (uint32_t)(RCC_SYSCLKSource_PLL << 2);
            break;
            
        default:
            /* We should not get here */
            return 0x01U;
    }
    for (uint32_t counter = 0; counter < LOOPS_TO_STABILIZE; counter++)
    {
        if ((RCC->CFGR & (0x03U << 2)) == check_flag)
        {
            return 0x00U;
        }
    }
    /* normally we should not get here*/
    return 0x01U;
}

/**
 * @brief Configure High Speed clock sources.
 * @param clock_config: a pointer to RCC_HSCLKConfig_TypeDef struct.
 * @retval uint32_t: non zero, in case of errors.
 */
uint32_t RCC_ConfigHSCLK(RCC_HSCLKConfig_TypeDef * clock_config)
{
    /* let's set FLASH registers. Prefetch buffer and latency*/
    /* Prefetched buffer is normally  on */
    RCC_SetFlashPrefetchedBuffer(ENABLE);

    /* latency depends on a SYSCLK speed*/
    switch(clock_config->RCC_SYSCLK_Frequency)
    {
        case 0 ... 24:
            RCC_SetFlashLatency(FLASH_ACR_LATENCY_0);
            break;
        case 25 ... 48:
            RCC_SetFlashLatency(FLASH_ACR_LATENCY_1);
            break;
        case 49 ... 72:
            RCC_SetFlashLatency(FLASH_ACR_LATENCY_2);
            break;
        default:
            /* we should not get here. We can't exeed 72 MHz */
            return 0x01U;
    }

    /* Let's take care of Prescalers */
    RCC_SetPrescalers(clock_config);

    if (clock_config->RCC_SYSCLK_Source == RCC_SYSCLKSource_PLL)
    {
       switch(clock_config->PLLClockConfig->RCC_PLLCLK_Source)
       {
            case RCC_PLLCLKSource_HSI:
                RCC_ConfigHSI(ENABLE);
                break;
            case RCC_PLLCLKSource_HSE_Div1 ... RCC_PLLCLKSource_HSE_Div2:
                RCC_ConfigHSE(ENABLE);
                break;
            default:
                /* we should not get here */
                return 0x02U;
       }
        RCC_ConfigPLL(clock_config->PLLClockConfig);
        RCC_SelectSysCLKSource(RCC_SYSCLKSource_PLL);
    }

    if (clock_config->RCC_SYSCLK_Source == RCC_SYSCLKSource_HSI)
    {
        RCC_ConfigHSI(ENABLE);
        RCC_SelectSysCLKSource(RCC_SYSCLKSource_HSI);
    }

    if (clock_config->RCC_SYSCLK_Source == RCC_SYSCLKSource_HSE)
    {
        RCC_ConfigHSE(ENABLE);
        RCC_SelectSysCLKSource(RCC_SYSCLKSource_HSE);
    }

    return 0x00U;
}
