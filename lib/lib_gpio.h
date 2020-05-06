#include <stdint.h>
#include <stm32f10x.h>


#define GPIO_Pin_0 ((uint16_t)0x0001) /*!< Pin 0 selected */
#define GPIO_Pin_1 ((uint16_t)0x0002) /*!< Pin 1 selected */
#define GPIO_Pin_2 ((uint16_t)0x0004) /*!< Pin 2 selected */
#define GPIO_Pin_3 ((uint16_t)0x0008) /*!< Pin 3 selected */
#define GPIO_Pin_4 ((uint16_t)0x0010) /*!< Pin 4 selected */
#define GPIO_Pin_5 ((uint16_t)0x0020) /*!< Pin 5 selected */
#define GPIO_Pin_6 ((uint16_t)0x0040) /*!< Pin 6 selected */
#define GPIO_Pin_7 ((uint16_t)0x0080) /*!< Pin 7 selected */
#define GPIO_Pin_8 ((uint16_t)0x0100) /*!< Pin 8 selected */
#define GPIO_Pin_9 ((uint16_t)0x0200) /*!< Pin 9 selected */
#define GPIO_Pin_10 ((uint16_t)0x0400) /*!< Pin 10 selected */
#define GPIO_Pin_11 ((uint16_t)0x0800) /*!< Pin 11 selected */
#define GPIO_Pin_12 ((uint16_t)0x1000) /*!< Pin 12 selected */
#define GPIO_Pin_13 ((uint16_t)0x2000) /*!< Pin 13 selected */
#define GPIO_Pin_14 ((uint16_t)0x4000) /*!< Pin 14 selected */
#define GPIO_Pin_15 ((uint16_t)0x8000) /*!< Pin 15 selected */
#define GPIO_Pin_All ((uint16_t)0xFFFF) /*!< All pins selected */

/* A name alias to GPIO modes enum.  */
/* Contains GPIO Input and Output Modes */
/* 3rd bit is added to represent Pull resistor flag */
/* When not needed this 3rd bit has to ignored */
/* Example: */
/* Floating input is 2bits 0b01 */
/* When we add  third bit it becomes 0b011 */
typedef enum
{
    IN_ANALOG = 0x00U,   /* Analog mode */ 
    IN_FLOATING = 0x03U, /* Floating input */
    IN_PU = 0x05U,    /* Input with pull-up */
    IN_PD = 0x04U,    /* Input with pull-down */
    OUT_PP = 0x00U,      /* Output push-pull */
    OUT_OD = 0x03U,      /* Output open drain */
    OUT_AF_PP = 0x05U,   /* Output alternate function push-pull*/
    OUT_AF_OD = 0x07U    /* Output alternate function open drain*/
}GPIO_Mode_TypeDef;

/* A name alias to GPIO speed enum. */
/* Contains GPIO Output mode speed options. */
typedef enum
{
    NONE = 0x00U,       /* For input mode */
    S2M = 0x02U,        /* Max speed 2MHz */ 
    S10M = 0x01U,       /* Max speed 10MHz */
    S50M = 0x03U,       /* Max speed 50MHz */
}GPIO_Speed_TypeDef;

/* A name alise to GPIO_Pins_Config struct. */
/* Have 2 members: Mode and Speed. If Input mode is selected,  */
/* speed has to be set to None */
/* Each member is 4 bits long. */
typedef struct
{
    GPIO_Mode_TypeDef Mode : 4;
    GPIO_Speed_TypeDef Speed : 4;
}GPIO_Pins_Config_TypeDef;

void GPIO_enable_clock(GPIO_TypeDef * GPIOx);
void GPIO_SetBits(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins);
void GPIO_ResetBits(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins);
void GPIO_Config_Pins(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins, GPIO_Pins_Config_TypeDef * GPIO_Pins_Cfg);
void GPIO_ToggleBits(GPIO_TypeDef * GPIOx, uint16_t GPIO_Pins);
