#include <stdint.h>
#include <stm32f10x.h>

typedef enum
{
    RCC_SysClockSource_HSI = 0x00U, /* High-speed internal */
    RCC_SysClockSource_HSE = 0x01U, /* High-speed external */
    RCC_SysClockSource_PLL = 0x02U /* Phase-Lock-Loop     */
}RCC_SysClockSource_TypeDef;

typedef enum
{
    RCC_PLLClockSorce_HSI = 0x00U, /* High-speed internal */
    RCC_PLLClockSorce_HSE = 0x01U, /* High-speed external */
    RCC_PLLClockSorce_HSE2 = 0x02U /* High-speed external prescaled by 2 */
}RCC_PLLClockSorce_TypeDef;

/* AHB (Advanced High-Performance Bus) prescaler */
/* Generate SYSCLK signal */
typedef enum
{
    RCC_SysClockPrescaler_NONE = 0x00U, /* 0b0000 SYSCLK not divided */
    RCC_SysClockPrescaler_DIV2 = 0x08U, /* 0b1000 SYSCLK divided by x2 */
    RCC_SysClockPrescaler_DIV4 = 0x09U, /* 0b1001 SYSCLK divided by x4 */
    RCC_SysClockPrescaler_DIV8 = 0x0AU, /* 0b1010 SYSCLK divided by x8 */
    RCC_SysClockPrescaler_DIV16 = 0x0BU, /* 0b1011 SYSCLK divided by x16 */
    RCC_SysClockPrescaler_DIV64 = 0x0CU, /* 0b1100 SYSCLK divided by x64 */
    RCC_SysClockPrescaler_DIV128 = 0x0DU, /* 0b1101 SYSCLK divided by x128 */
    RCC_SysClockPrescaler_DIV256 = 0x0EU, /* 0b1110 SYSCLK divided by x256 */
    RCC_SysClockPrescaler_DIV512 = 0x0FU  /* 0b1111 SYSCLK divided by x512 */
}RCC_SysClockPrescaler_TypeDef;

/* APB2 (Advanced Peripheral Bus) high-speed prescaler */
/* APB1 (Advanded Peripharal Bus) low-speed prescaler */
/* Generate PCLK2 and PCLK1 signal */
typedef enum
{
    RCC_PeriphClockPrescaler_NONE = 0x00U, /* HCLK not divided */
    RCC_PeriphClockPrescaler_DIV2 = 0x04U, /* HCLK divided by x2 */
    RCC_PeriphClockPrescaler_DIV4 = 0x05U, /* HCLK divided by x4 */
    RCC_PeriphClockPrescaler_DIV8 = 0x06U, /* HCLK divided by x8 */
    RCC_PeriphClockPrescaler_DIV16 = 0x07U /* HCLK divided by x16 */
}RCC_PeriphClockPrescaler_TypeDef;

/* PLL (Phase-Lock-Loop) multiplication factor */
typedef enum
{
   PLLMulCoef_MUL2 = 0x00U, /* 0b0000 PLL input clock x2 */
   PLLMulCoef_MUL3 = 0x01U, /* 0b0001 PLL input clock x3 */ 
   PLLMulCoef_MUL4 = 0x02U, /* 0b0010 PLL input clock x4 */
   PLLMulCoef_MUL5 = 0x03U, /* 0b0011 PLL input clock x5 */
   PLLMulCoef_MUL6 = 0x04U, /* 0b0100 PLL input clock x6 */
   PLLMulCoef_MUL7 = 0x05U, /* 0b0101 PLL input clock x7 */
   PLLMulCoef_MUL8 = 0x06U, /* 0b0110 PLL input clock x8 */
   PLLMulCoef_MUL9 = 0x07U, /* 0b0111 PLL input clock x9 */
   PLLMulCoef_MUL10 = 0x08U, /* 0b1000 PLL input clock x10 */
   PLLMulCoef_MUL11 = 0x09U, /* 0b1001 PLL input clock x11 */
   PLLMulCoef_MUL12 = 0x0AU, /* 0b1010 PLL input clock x12 */
   PLLMulCoef_MUL13 = 0x0BU, /* 0b1011 PLL input clock x13 */
   PLLMulCoef_MUL14 = 0x0CU, /* 0b1100 PLL input clock x14 */
   PLLMulCoef_MUL15 = 0x0DU, /* 0b1101 PLL input clock x15 */
   PLLMulCoef_MUL16 = 0x0EU  /* 0b1110 PLL input clock x16 */
}RCC_PLLMulCoef_TypeDef;

typedef struct
{
    RCC_PLLClockSorce_TypeDef PLLClockSource : 2;
    RCC_PLLMulCoef_TypeDef PLLMulCoef : 4; 
}RCC_PLLClockConfig_TypeDef;

typedef struct
{
    RCC_SysClockSource_TypeDef SysClockSource : 2;
    RCC_SysClockPrescaler_TypeDef SysClockPrescaler : 4;
    RCC_PeriphClockPrescaler_TypeDef APB1ClockPrescaler : 3;
    RCC_PeriphClockPrescaler_TypeDef APB2ClockPrescaler : 3;
    RCC_PLLClockConfig_TypeDef * PLLClockConfig; 
}RCC_SysClockConfig_TypeDef;

uint32_t RCC_EnableHSE(void);
uint32_t RCC_ConfigHighSpeedClock(RCC_SysClockConfig_TypeDef * clock_config);
