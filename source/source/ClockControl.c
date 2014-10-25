#include "stm32f4xx.h"
#include "ClockControl.h"

ClockControlType ClockControl;

void ClockControl_Initialize()
{
  //enable HSE
  RCC->CR |= RCC_CR_HSEON;
  while(~RCC->CR & RCC_CR_HSERDY);
  
  //enable MSI
  //RCC->CR |= RCC_CR_MSION;
  //while(~RCC->CR & RCC_CR_MSIRDY);
  
  //run MSI as SYSCLK
  RCC->CFGR &= ~(RCC_CFGR_SW);
  while(RCC->CFGR & RCC_CFGR_SWS);
  
  //disable PLL to configure it
  RCC->CR &= ~RCC_CR_PLLON;
  while(RCC->CR & RCC_CR_PLLRDY);
  
  //configure PLL
  RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
  RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
  RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3 | RCC_PLLCFGR_PLLM_4;
  RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
	RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_7;
  
  //enable PLL
  RCC->CR |= RCC_CR_PLLON;
  while(~RCC->CR & RCC_CR_PLLRDY);
  
  //run PLL as SYSCLK
  RCC->CFGR &= ~(RCC_CFGR_SW);
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while(~RCC->CFGR & RCC_CFGR_SWS_PLL);
  
  
  RCC->CFGR &= ~RCC_CFGR_HPRE;
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
  
  RCC->CFGR &= ~RCC_CFGR_PPRE1;
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
  
  RCC->CFGR &= ~RCC_CFGR_PPRE2;
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV4;
  
  ClockControl.APB1_Frequency = 8000000; // if changes, clock tuning in I2C should be changed 
  ClockControl.APB2_Frequency = 8000000;
  ClockControl.AHB_Frequency = 32000000;
  ClockControl.SYSCLK_Frequency = 32000000;
}
