#include <stdint.h>
#include <stm32f10x.h>

/* lib configuration defines */
#define LOOPS_TO_STABILIZE ((uint16_t)0x3E8U) /* whait for clock sources to stabilize */
/* from stm32f10x.h */ 
/*typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState; */

/* System clock sources */
#define RCC_SYSCLKSource_HSI ((uint8_t)0x00U) /* High-speed internal */
#define RCC_SYSCLKSource_HSE ((uint8_t)0x01U) /* High-speed external */
#define RCC_SYSCLKSource_PLL ((uint8_t)0x02U) /* Phase-Lock-Loop     */

/* PLL (Phase-Lock-Loop) clock sources */
#define RCC_PLLCLKSource_HSI ((uint8_t)0x00U) /* High-speed internal */
#define RCC_PLLCLKSource_HSE_Div1 ((uint8_t)0x01U) /* High-speed external */
#define RCC_PLLCLKSource_HSE_Div2 ((uint8_t)0x02U) /* High-speed external prescaled by 2 */

/* AHB (Advanced High-Performance Bus) prescaler */
/* System clock prescaler */
/* Generate SYSCLK signal */
#define RCC_SYSCLK_Div1 ((uint8_t)0x00U) /* 0b0000 SYSCLK not divided */
#define RCC_SYSCLK_Div2 ((uint8_t)0x08U) /* 0b1000 SYSCLK divided by x2 */
#define RCC_SYSCLK_Div4 ((uint8_t)0x09U) /* 0b1001 SYSCLK divided by x4 */
#define RCC_SYSCLK_Div8 ((uint8_t)0x0AU) /* 0b1010 SYSCLK divided by x8 */
#define RCC_SYSCLK_Div16 ((uint8_t)0x0BU) /* 0b1011 SYSCLK divided by x16 */
#define RCC_SYSCLK_Div64 ((uint8_t)0x0CU) /* 0b1100 SYSCLK divided by x64 */
#define RCC_SYSCLK_Div128 ((uint8_t)0x0DU) /* 0b1101 SYSCLK divided by x128 */
#define RCC_SYSCLK_Div256 ((uint8_t)0x0EU) /* 0b1110 SYSCLK divided by x256 */
#define RCC_SYSCLK_Div512 ((uint8_t)0x0FU)  /* 0b1111 SYSCLK divided by x512 */

/* APB2 (Advanced Peripheral Bus) high-speed prescaler */
/* APB1 (Advanded Peripharal Bus) low-speed prescaler */
/* Generate PCLK2 and PCLK1 signal */
#define RCC_HCLK_Div1 ((uint8_t)0x00U) /* HCLK not divided */
#define RCC_HCLK_Div2 ((uint8_t)0x04U) /* HCLK divided by x2 */
#define RCC_HCLK_Div4 ((uint8_t)0x05U) /* HCLK divided by x4 */
#define RCC_HCLK_Div8 ((uint8_t)0x06U) /* HCLK divided by x8 */
#define RCC_HCLK_Div16 ((uint8_t)0x07U) /* HCLK divided by x16 */

/* PLL (Phase-Lock-Loop) multiplication factor */
#define RCC_PLLMul_2 ((uint8_t)0x00U) /* 0b0000 PLL input clock x2 */
#define RCC_PLLMul_3 ((uint8_t)0x01U) /* 0b0001 PLL input clock x3 */ 
#define RCC_PLLMul_4 ((uint8_t)0x02U) /* 0b0010 PLL input clock x4 */
#define RCC_PLLMul_5 ((uint8_t)0x03U) /* 0b0011 PLL input clock x5 */
#define RCC_PLLMul_6 ((uint8_t)0x04U) /* 0b0100 PLL input clock x6 */
#define RCC_PLLMul_7 ((uint8_t)0x05U) /* 0b0101 PLL input clock x7 */
#define RCC_PLLMul_8 ((uint8_t)0x06U) /* 0b0110 PLL input clock x8 */
#define RCC_PLLMul_9 ((uint8_t)0x07U) /* 0b0111 PLL input clock x9 */
#define RCC_PLLMul_10 ((uint8_t)0x08U) /* 0b1000 PLL input clock x10 */
#define RCC_PLLMul_11 ((uint8_t)0x09U) /* 0b1001 PLL input clock x11 */
#define RCC_PLLMul_12 ((uint8_t)0x0AU) /* 0b1010 PLL input clock x12 */
#define RCC_PLLMul_13 ((uint8_t)0x0BU) /* 0b1011 PLL input clock x13 */
#define RCC_PLLMul_14 ((uint8_t)0x0CU) /* 0b1100 PLL input clock x14 */
#define RCC_PLLMul_15 ((uint8_t)0x0DU) /* 0b1101 PLL input clock x15 */
#define RCC_PLLMul_16 ((uint8_t)0x0EU)  /* 0b1110 PLL input clock x16 */

/*  Clock source to output on MCO Pin. Usually PA8 */
#define RCC_MCO_NoClock ((uint8_t)0x00U) /* 0b000 No clock */
#define RCC_MCO_SYSCLK ((uint8_t)0x04U) /* 0b100 SYSCLK clock selected */
#define RCC_MCO_HSI ((uint8_t)0x05U) /* 0b101 HSI clock selected */
#define RCC_MCO_HSE ((uint8_t)0x06U) /* 0b110 HSE clock selected */
#define RCC_MCO_PLLCLK_Div2 ((uint8_t)0x07U) /* 0b111 PLL clock divided by 2 selected */

/* From stm32f10x.h FLASH latency */
//#define  FLASH_ACR_LATENCY ((uint8_t)0x03) /*!< LATENCY[2:0] bits (Latency) */
//#define  FLASH_ACR_LATENCY_0 ((uint8_t)0x00) /*!< Bit 0 */
//#define  FLASH_ACR_LATENCY_1 ((uint8_t)0x01) /*!< Bit 0 */
//#define  FLASH_ACR_LATENCY_2 ((uint8_t)0x02) /*!< Bit 1 */

//#define  FLASH_ACR_HLFCYA ((uint8_t)0x08) /*!< Flash Half Cycle Access Enable */
//#define  FLASH_ACR_PRFTBE ((uint8_t)0x10) /*!< Prefetch Buffer Enable */
//#define  FLASH_ACR_PRFTBS ((uint8_t)0x20) /*!< Prefetch Buffer Status */

/* PLL configuration structure. */
typedef struct
{
    uint8_t RCC_PLLCLK_Source; /* PLL clock source */
    uint8_t RCC_PLLMul_Coef; /* PLL multiplication factor */
}RCC_PLLCLKConfig_TypeDef;

/* High speed clock config structure */
/* Be careful with RCC_SYSCLK_Frequency. FLASH latency will be set based on it */
typedef struct
{
    uint8_t RCC_SYSCLK_Source; /* System clock source */ 
    uint8_t RCC_SYSCLK_Prescaler; /* System clock prescaler */
    uint8_t RCC_APB1CLK_Prescaler; /* APB1 low-speed prescaler */
    uint8_t RCC_APB2CLK_Prescaler; /* APB2 high-speed prescaler */
    uint8_t RCC_SYSCLK_Frequency; /* System clock frequency in MHz. User must set corrently. */
    RCC_PLLCLKConfig_TypeDef * PLLClockConfig; /* A pointer to PLL configuration struct. Nullable */
}RCC_HSCLKConfig_TypeDef;

uint32_t RCC_ConfigHSE(FunctionalState state);
void RCC_ConfigPLL(RCC_PLLCLKConfig_TypeDef * config);
void RCC_ConfigHSI(FunctionalState state);
void RCC_SetFlashLatency(uint8_t latency);
void RCC_SetFlashPrefetchedBuffer(FunctionalState state);
void RCC_SetPrescalers(RCC_HSCLKConfig_TypeDef * clock_config);
void RCC_SetAPB2Prescaler(uint8_t prescaler);
void RCC_SetAPB1Prescaler(uint8_t prescaler);
void RCC_SetSyclkPrescaler(uint8_t prescaler);
void RCC_MCOEnable(uint8_t mco_config);
uint32_t RCC_SelectSysCLKSource(uint8_t source);
uint32_t RCC_ConfigHSCLK(RCC_HSCLKConfig_TypeDef * clock_config);
