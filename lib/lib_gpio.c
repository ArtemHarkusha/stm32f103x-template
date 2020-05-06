#include <lib_gpio.h>

/* * THIS FILE IS MADE ON THE TOP OF CMIS LIBRARY. ALL CONSTANSES ARE DEFINED THERE.  * /

*GPIO_TypeDef * is pointer to a struct. Depending on the selected port, 
 * the struct beginning address changes. This is possible because all GPIO 
 * registers are (of a specific port) are going one by one in the address space.
 * Each structure element is 32 bits
 * GPIO_TypeDef is defined in stm32f103xx.h
*/


/**
 * @brief Configure GPIO ports mode and speed.
 * @param GPIOx: where x can be (A..G) to select GPIO peripheral.
 * @param GPIO_Pins: specifies port pins to be configured.
 * @param GPIO_Pins_Cfg: a combination of CNF and MODE bits represented in a struct.
 * @retval None
*/
void GPIO_ConfigPins(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins, GPIO_PinsConfig_TypeDef * GPIO_PinsCfg)
{
    /* Let's get the Pull resistor flag for input mode. */
    /* It's the lowest bit in GPIOx->Mode */
    uint8_t pu_pd_flag = GPIO_PinsCfg->Mode & 0x01U;
    /* make a 4bit configuration word out of the struct */
    /* First clear up Pull resistor flag and OR with  Speed to get what we need */
    uint32_t cfg = ((GPIO_PinsCfg->Mode << 1) & ~(0x01U << 1)) | GPIO_PinsCfg->Speed; 
    uint32_t regtemp, pinpos, mask, index;
    /* this is a lenth of a specific pin configuration bits inside the register */
    uint32_t cfg_field_lenth = 0x04U;

    /* Check if any of lower port bits are set */
    /* 0xFFU is a mask of 8th 1s */ 
    if ((((uint32_t)GPIO_Pins) & ((uint32_t)0xFFU)) != 0x00U) 
    {
        /* CONFIGURE LOW PORT BITS */
        /* the value from CRL before configuration */
        regtemp = GPIOx->CRL;
        for (pinpos = 0x00U; pinpos < 0x08U; pinpos++)
        {
            if ((uint32_t)GPIO_Pins & ((uint32_t)(0x01U << pinpos)))
            {
                index = pinpos << 0x02U;
                mask = ~(((0x01U << cfg_field_lenth) - 0x01U) << index);
                regtemp = (regtemp & mask) | (uint32_t)(cfg << index);      
            }
        }
        /* Write CRL register confgiuration */ 
        GPIOx->CRL = regtemp; 
    }
    
    /* Shif higher part of port bits to the right and repeat the exercise */
    if ((((uint32_t)GPIO_Pins >> 0x08U) & 0xFFU) != 0x00U)
    {
        /* Congigure higher port pins */
        /* the value of CRH before configuration */
       regtemp = GPIOx->CRH;
       /* Let's loop through all 8 higher port pins and see if 
        * any need to be configured */
       for (pinpos = 0x00U; pinpos < 0x08U; pinpos++ )
       {
            /* If current pin has to be configured */
            /* Shift 1 to the position we are checking and perform AND operation */
            /* We are adding 0x08 as it's a higher part of the port */
            if ((uint32_t)GPIO_Pins & ((uint32_t)0x01U << (pinpos + 0x08U)))
            {
                /* index inside CRH. We have to multiply current position by 4 */
                /* basically when we shift left 1 position it is the same 
                 * as multiply by 2 */ 
                index = pinpos << 0x02U;
                /* This is mask for setting any number of bit's in the world.  */
                /* 1) We shif 1 to the number of bits iwe want to set */
                /* 2) Substract 1 from the result */ 
                /* 3) Shif to the index in the word we want to change */
                /* 4) Finally we invert the result */
                /* Example. Let's say we want to set 6th, 5th and 4th bits in 8 bits word */
                /*  00000001 << 3 */
                /*  00001000 -1   */
                /*  00000111 << 4 */
                /*  01110000 ~    */
                /*  10001111      */
                mask = ~(((0x01U << cfg_field_lenth) - 0x01U) << index);
                /* Finally we can cofigure the pin by setting specific bit in CRH reg
                 * to cfg word. */
                /* 1) Reset specific position using AND. */
                /* 2) Set bits with OR (Config word is shifted to therequired position). */
                /* Example: Let's say we want to set 6th, 5th and 4th bits i 8 bits
                 * in 8 bits word to 101. We will use the mask from step above. */
                /* 01101101 AND   */
                /* 10001111       */
                /*     ____       */
                /* 00001101 OR    */ 
                /* 01010000       */
                /*     ____       */
                /* 01011101       */ 
                regtemp  = (regtemp & mask) | (uint32_t)(cfg << index);
                /* more details about reading/setting arbitrary bits: 
                 * https://stackoverflow.com/questions/11815894/how-to-read-write-arbitrary-bits-in-c-c */
            }
       }
        
       /* Write configuration regestry */
       GPIOx->CRH = regtemp; 
    }

    /* In case it's input mode with Pull-down resistor */
    /* Reset ODR bits */
    if ((GPIO_PinsCfg->Speed == 0x00U) & (pu_pd_flag == 0x00U))
    {
        GPIOx->BRR |= GPIO_Pins;
    }
    
    /* In case it's input mode with pull-up resistore */
    /* Set ODR bits */
    if ((GPIO_PinsCfg->Speed == 0x00U) & (pu_pd_flag != 0x00U))
    {
        GPIOx->BSRR |= GPIO_Pins; 
    }
}

/**
 * @brief Sets Port bits individually.
 * @param GPIOx: where x can be (A..G) to select GPIO peripheral.
 * @param GPIO_Pins: specifies port pins to be reset.
 * @retval None:
*/
void GPIO_SetBits(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins)
{
    /* GPIOx-BSRR is a pointer to BSRR regestry of a specific port */
    GPIOx->BSRR |= GPIO_Pins;  
}

/**
 * @brief Resets Port bits individually.
 * @param GPIOx: where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pins: specifies port pins to be reset.
 * Is a 16 bits number.
 * @retval None
 */ 
void GPIO_ResetBits(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins)
{

    /* GPIOx-BSRR is a pointer to BSRR regestry of a specific port.
     * We have to make a 16 bit shift to get to the higher bits of BSRR
     * writing in which resets pins.
     *
     * It's also possible to use BRR just like this: 
     *  GPIOx->BRR = GPIO_Pins;
     *  */
   GPIOx->BSRR |= GPIO_Pins << 16;
}

/**
 * @brief   Enables clock of a specific GPIO port.
 * @param   GPIOx: where x can be (A..D) to select GPIO peripheral.
 * @retval  None
*/
void GPIO_EnableClock(GPIO_TypeDef * GPIOx)
{
/* RCC->APB2ENR contains a pointer to the RCC_APB2ENR register address 0x040021018U*/
    if(GPIOx == GPIOA)
    {
        /* RCC_APB2ENR_IOPAEN - Port A enable mask. 2th bit (uint32_t)0x04U*/
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    }

    if(GPIOx == GPIOB)
    {
        /* RCC_APB2ENR_IOPBEN - Port B enable mask. 3th bit (uint32_t)0x08U*/
        RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    }

    if(GPIOx == GPIOC)
    {
        /* RCC_APB2ENR_IOPCEN - Port C enable mask. 4th bit (uint32_t)0x10U*/
        RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    }

    if(GPIOx == GPIOD)
    {   
        /* RCC_APB@ENR_IOPDEN - Port D enable mask. 5th bit (uint32_t)0x20U*/
        RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
    }
}

/**
 * @brief changes the bits state of a specific GPIO port to opposit.
 * @param GPIOx: where x can be (A..D) to select GPIO peripheral.
 * @param GPIO_Pins: pins to toggle.
 * @retval None
 */
void GPIO_ToggleBits(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins)
{
    /* read port bits state */
    uint32_t pins_state = GPIOx->ODR;
    /* change bits state to opposit */
    /* (pins_state & GPIO_Pins) << 16 will cause corresponding bits to be reset, if set*/
    /* (~pins_state & GPIO_Pins) this will set corresponding bits, if reset */
    GPIOx->BSRR |= ((pins_state & GPIO_Pins) << 16 | (~pins_state & GPIO_Pins));
}
