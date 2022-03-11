#include <stdint.h>
#include <stm32l4xx.h>
// semih barmaksiz
int mux = 0;

void delay(unsigned int n){
    volatile unsigned int delay = n;
    while (delay--);
}

void clear(){
	delay(5000);
	GPIOA->ODR &= ~(GPIO_ODR_OD7 | GPIO_ODR_OD5);
	GPIOB->ODR &= ~(GPIO_ODR_OD0 | GPIO_ODR_OD12 | GPIO_ODR_OD15 | GPIO_ODR_OD1 | GPIO_ODR_OD2);
}

void seg7(int n){
	switch (n){
		case 0:
			GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
			GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD12 | GPIO_ODR_OD15 | GPIO_ODR_OD1);
			break;
		case 1:
			GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
			break;
		case 2:
			GPIOA->ODR |= (GPIO_ODR_OD7);
			GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD2 | GPIO_ODR_OD15 | GPIO_ODR_OD12);
			break;
		case 3:
			GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
			GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD2 | GPIO_ODR_OD12);
			break;
		case 4:
			GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
			GPIOB->ODR |= (GPIO_ODR_OD1 | GPIO_ODR_OD2);
			break;
		case 5:
			GPIOA->ODR |= (GPIO_ODR_OD5);
			GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD1 | GPIO_ODR_OD2 | GPIO_ODR_OD12);
			break;
		case 6:
			GPIOA->ODR |= (GPIO_ODR_OD5);
			GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD1 | GPIO_ODR_OD15 | GPIO_ODR_OD12 | GPIO_ODR_OD2);
			break;
		case 7:
			GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
			GPIOB->ODR |= (GPIO_ODR_OD0);
			break;
		case 8:
			GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
			GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD12 | GPIO_ODR_OD15 | GPIO_ODR_OD1 | GPIO_ODR_OD2);
			break;
		case 9:
			GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
			GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD12 | GPIO_ODR_OD1 | GPIO_ODR_OD2);
			break;
	}
}

void multiplexer(int uren, int minuten){
	while (mux == 0){
		if (uren / 10 < 1){
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR &= ~(GPIO_ODR_OD15);		// 00
			seg7(0);
			clear();


			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR &= ~(GPIO_ODR_OD15);		// 10
			seg7(uren);
			clear();
			mux++;
		}
		else if (uren / 10 < 2){
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR &= ~(GPIO_ODR_OD15);		// 00
			seg7(1);
			clear();

			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR &= ~(GPIO_ODR_OD15);		// 10
			seg7(uren % 10);
			clear();
			mux++;
		}
		else{
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR &= ~(GPIO_ODR_OD15);		// 00
			seg7(2);
			clear();

			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR &= ~(GPIO_ODR_OD15);		// 10
			seg7(uren % 10);
			clear();
			mux++;
		}
	}

	while (mux == 1){
		if (minuten / 10 < 1){
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 01
			seg7(0);
			clear();

			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 11
			seg7(minuten);
			clear();
			mux--;
		}
		else if (minuten / 10 < 2){
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 01
			seg7(1);
			clear();

			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 11
			seg7(minuten % 10);
			clear();
			mux--;
		}
		else if (minuten / 10 < 3){
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 01
			seg7(2);
			clear();

			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 11
			seg7(minuten % 10);
			clear();
			mux--;//semih barmaksiz
		}
		else if (minuten / 10 < 4){
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 01
			seg7(3);
			clear();

			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 11
			seg7(minuten % 10);
			clear();
			mux--;
		}
		else if (minuten / 10 < 5){
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 01
			seg7(4);
			clear();

			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 11
			seg7(minuten % 10);
			clear();
			mux--;
		}
		else if (minuten / 10 < 6){
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 01
			seg7(5);
			clear();

			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 11
			seg7(minuten % 10);
			clear();
			mux--;
		}
		else{
			GPIOA->ODR &= ~(GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 01
			seg7(6);
			clear();//semih barmaksiz

			GPIOA->ODR |= (GPIO_ODR_OD8);
			GPIOA->ODR |= (GPIO_ODR_OD15);		// 11
			seg7(0);
			clear();
			mux--;
		}
	}
}

int main(void) {
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

    //7seg leds
	GPIOA->MODER &= ~GPIO_MODER_MODE7_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE7_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT7;

	GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;

	GPIOB->MODER &= ~GPIO_MODER_MODE0_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE0_0;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT0;

	GPIOB->MODER &= ~GPIO_MODER_MODE12_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE12_0;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT12;

	GPIOB->MODER &= ~GPIO_MODER_MODE15_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE15_0;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT15;

	GPIOB->MODER &= ~GPIO_MODER_MODE1_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE1_0;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT1;

	GPIOB->MODER &= ~GPIO_MODER_MODE2_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE2_0;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT2;

	//mux
	GPIOA->MODER &= ~GPIO_MODER_MODE8_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE8_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT8;

	GPIOA->MODER &= ~GPIO_MODER_MODE15_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE15_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT15;

	GPIOA->MODER &= ~GPIO_MODER_MODE6_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE6_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT6;

    while (1) {
    	int uren = 15;
    	int minuten = 34;

    	multiplexer(uren,minuten);
    }
}
