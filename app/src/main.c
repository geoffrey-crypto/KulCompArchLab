/**
 * @file main.c
 * @version 0.1
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */



#include <stdint.h>
#include <stm32l4xx.h>

int main(void) {
	// Selecteren van HSI16
	RCC->CCIPR &= ~RCC_CCIPR_USART2SEL_0;
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_1;
	// Activeren klok
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN_Msk;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN_Msk;


	GPIOB->MODER &= ~GPIO_MODER_MODE9_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE9_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;
	GPIOC->MODER |= GPIO_MODER_MODE13_0;

	GPIOB->OTYPER &= ~GPIO_OTYPER_OT9;
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT13;
volatile int i = 1000000;
  while (i>0) {
	  if ()//if button 1 is pushed down "setting in push"
	  {
		  //clock value is equal to a value
		  GPIOB->ODR |= GPIO_ODR_ODE9; //led0 on for certain amount
		  GPIOB->ODR &= ~GPIO_ODR_ODE9;
		  GPIOC->ODR |= GPIO_ODR_ODE13; //led1 on for certain amount
		  GPIOC->ODR &= ~GPIO_ODR_ODE13;

		  i--;
	  }
	  else
	  {
		  //clock value is equal to a value
		  GPIOB->ODR |= GPIO_ODR_ODE9; //led0 on for certain amount
		  GPIOB->ODR &= ~GPIO_ODR_ODE9;
		  GPIOC->ODR |= GPIO_ODR_ODE13; //led1 on for certain amount
		  GPIOC->ODR &= ~GPIO_ODR_ODE13;
	  }
  }
}
