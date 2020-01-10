#include "Gazzali.h"

#define __IO
typedef struct
{
  __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint16_t BSRRL;    /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */
  __IO uint16_t BSRRH;    /*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
  __IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIO_TypeDef;

typedef struct
{
  __IO uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
  __IO uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  __IO uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
  __IO uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  __IO uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  __IO uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  __IO uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  __IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  __IO uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  __IO uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  __IO uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  __IO uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  __IO uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  __IO uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  __IO uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  __IO uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  __IO uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  __IO uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  __IO uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
} RCC_TypeDef;

#define PERIPH_BASE           	((uint32_t)0x40000000) /*!< Peripheral base address in the alias region                                */
/*!< Peripheral memory map */
#define APB1PERIPH_BASE       	PERIPH_BASE
#define APB2PERIPH_BASE       	(PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE       	(PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE       	(PERIPH_BASE + 0x10000000)

#define RCC_BASE              	(AHB1PERIPH_BASE + 0x3800)
#define RCC                   	((RCC_TypeDef *) RCC_BASE)
/*!< AHB1 peripherals */
#define GPIOA_BASE            	(AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE            	(AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE            	(AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE            	(AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASE            	(AHB1PERIPH_BASE + 0x1000)
#define GPIOF_BASE            	(AHB1PERIPH_BASE + 0x1400)
#define GPIOG_BASE            	(AHB1PERIPH_BASE + 0x1800)
#define GPIOH_BASE            	(AHB1PERIPH_BASE + 0x1C00)
#define GPIOI_BASE            	(AHB1PERIPH_BASE + 0x2000)

#define GPIOA               	((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               	((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               	((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               	((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE               	((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF               	((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG               	((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH               	((GPIO_TypeDef *) GPIOH_BASE)
#define GPIOI               	((GPIO_TypeDef *) GPIOI_BASE)


static void blinky_discovery()
{
	RCC->AHB1ENR|=0x00000008;          // GPIOD donanımının clock sinyalini uygulayalım
	GPIOD->MODER=0x55000000;           // GPIOD nin 15, 14, 13, 12 pinleri cikis tanimlandi (Ledler bu pinlerde)
	GPIOD->OSPEEDR= 0xFFFFFFFF;        // GPIOD nin tum cikislari en yuksek hizda kullanacagiz
	while(1) {
		GPIOD->ODR= 0x0000F000;     // Ledler yansin
		GPIOD->ODR= 0x00000000;     // Ledler sonsun
    }
}



static void init()
{
	
}

static void exit()
{

}

