Generally RCC setup should look like the following:

1. When MC starts it's always running from HSI clock source on 8 MHz 
2. We need to configure FLASH access register 
    2.1. Confgure prefetched buffer. Is enabled after reset. Prefetched buffer can turn on/off only when SYSCLK 
         is lower than 24 MHz and no prescaler is applied on AHB (HCLK must be equel SYSCLK). The prefetch buffer must be 
         on when AHB prescaler is different from 1.
    2.2. Configre flash latency (number of wait states for a read operation programmed on-the-fly)
        - 0 wait states, if 0 < SYSCLK ≤ 24 MHz
        - 1 wait state, if 24 MHz < SYSCLK ≤ 48 MHz
        - 2 wait states, if 48 MHz < SYSCLK ≤ 72 MHz
    2.3 Optionally configure Half cycle: for power optimization. Half cycle configuration is not available in combination with a prescaler on the AHB. The
system clock (SYSCLK) should be equal to the HCLK clock. This feature can therefore be used only with a low-frequency clock of 8 MHz or less. It can be generated from the HSI or
the HSE but not from the PLL.

3. Configure prescalers 

4. Choose the clock source and configure it 

5. Switch to the new clock source

6. Optionally disable HSI clock
