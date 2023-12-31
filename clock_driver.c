#include "stm32f401xc.h"
#include "clock_driver.h"

void setRCC_84MHz(void)
{
	RCC->CR |= RCC_CR_HSEON; 
	while(!(RCC->CR & RCC_CR_HSERDY))
	
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS_1;
	PWR->CR &=~ PWR_CR_VOS_0;
	
	FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
	
	RCC->PLLCFGR = (20<<0) | (420<<6)| (1<<16) | RCC_PLLCFGR_PLLSRC_HSI; 
	
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
