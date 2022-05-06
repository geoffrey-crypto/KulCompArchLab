#include <stdint.h>
#include <stm32l4xx.h>
#include <math.h>
int mux = 0;
int uren = 0;
int minuten = 0;
int i = 0;
int ms = 0;
float waarde;
float V;
float R;
int temperatuur;
float t;
int input_pot;
int __io_putchar(int ch){
			    while(!(USART1->ISR & USART_ISR_TXE));
			    USART1->TDR = ch;
			}
void delay(unsigned int n) {
	volatile unsigned int delay = n;
	while (delay--) {
		;
	}
}

void clear() {
	GPIOA->ODR &= ~(GPIO_ODR_OD7 | GPIO_ODR_OD5);
	GPIOB->ODR &= ~(GPIO_ODR_OD0 | GPIO_ODR_OD12 | GPIO_ODR_OD15 | GPIO_ODR_OD1
			| GPIO_ODR_OD2);
}

void seg7(int n) {
	switch (n) {
	case 0:
		GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
		GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD12 | GPIO_ODR_OD15
				| GPIO_ODR_OD1);
		break;
	case 1:
		GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
		break;
	case 2:
		GPIOA->ODR |= (GPIO_ODR_OD7);
		GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD2 | GPIO_ODR_OD15
				| GPIO_ODR_OD12);
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
		GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD1 | GPIO_ODR_OD2
				| GPIO_ODR_OD12);
		break;
	case 6:
		GPIOA->ODR |= (GPIO_ODR_OD5);
		GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD1 | GPIO_ODR_OD15
				| GPIO_ODR_OD12 | GPIO_ODR_OD2);
		break;
	case 7:
		GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
		GPIOB->ODR |= (GPIO_ODR_OD0);
		break;
	case 8:
		GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
		GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD12 | GPIO_ODR_OD15
				| GPIO_ODR_OD1 | GPIO_ODR_OD2);
		break;
	case 9:
		GPIOA->ODR |= (GPIO_ODR_OD7 | GPIO_ODR_OD5);
		GPIOB->ODR |= (GPIO_ODR_OD0 | GPIO_ODR_OD12 | GPIO_ODR_OD1
				| GPIO_ODR_OD2);
		break;
	}
}

void SysTick_Handler(void) {
	switch (mux) {
	case 0:
		clear();
		GPIOA->ODR &= ~(GPIO_ODR_OD8);
		GPIOA->ODR &= ~(GPIO_ODR_OD15);		// 00
		seg7(temperatuur / 1000);
		GPIOA->ODR &= ~(GPIO_ODR_OD6);
		break;

	case 1:

		clear();
		GPIOA->ODR |= (GPIO_ODR_OD8);
		GPIOA->ODR &= ~(GPIO_ODR_OD15);	// 10
		seg7((temperatuur / 100) % 10);
		GPIOA->ODR &= ~(GPIO_ODR_OD6);
		break;

	case 2:
		clear();
		GPIOA->ODR &= ~(GPIO_ODR_OD8);
		GPIOA->ODR |= (GPIO_ODR_OD15);		// 01
		seg7((temperatuur % 100) / 10);
		GPIOA->ODR |= (GPIO_ODR_OD6);
		break;

	case 3:

		clear();
		GPIOA->ODR |= (GPIO_ODR_OD8);
		GPIOA->ODR |= (GPIO_ODR_OD15);		// 11
		seg7((temperatuur % 100) % 10);
		GPIOA->ODR &= ~(GPIO_ODR_OD6);
		break;
	}
	mux++;
	ms++;


	if (ms == 1000) {
		ms = 0;
		t = temperatuur;
		printf("%.1f\n\r",t/10);
	}

	if (mux > 3) {
		mux = 0;
	}
}
int main(void) {

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	//Klok aanzetten van GPIO en UART blok
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	//GPIO configureren en alternative mode aanzetten
	GPIOA->MODER &= ~GPIO_MODER_MODE9_Msk;
	GPIOA->MODER |=  GPIO_MODER_MODE9_1;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT9;
	GPIOA->AFR[1] = (GPIOA->AFR[1] & (~GPIO_AFRH_AFSEL9_Msk)) | (0x7 << GPIO_AFRH_AFSEL9_Pos);

	GPIOA->MODER &= ~GPIO_MODER_MODE10_Msk;
	GPIOA->AFR[1] = (GPIOA->AFR[1] & (~GPIO_AFRH_AFSEL10_Msk)) | (0x7 << GPIO_AFRH_AFSEL10_Pos);

	//UART configureren
	USART1->CR1 = 0;
	USART1->CR2 = 0;
	USART1->CR3 = 0;
	USART1->BRR = 417;
	USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

	//Potmeter
	GPIOA->MODER &= ~GPIO_MODER_MODE1_Msk; //NTC configureren naar Analog
	GPIOA->MODER |= GPIO_MODER_MODE1_0;
	GPIOA->MODER |= GPIO_MODER_MODE1_1;

	//klok aanzetten
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;

	// Klok selecteren, hier gebruiken we sysclk
	RCC->CCIPR &= ~RCC_CCIPR_ADCSEL_Msk;
	RCC->CCIPR |= RCC_CCIPR_ADCSEL_0 | RCC_CCIPR_ADCSEL_1;

	// Deep powerdown modus uitzetten
	ADC1->CR &= ~ADC_CR_DEEPPWD;
	// ADC voltage regulator aanzetten
	ADC1->CR |= ADC_CR_ADVREGEN;

	// Delay a few miliseconds, see datasheet for exact timing
	delay(1500);

	ADC1->CR |= ADC_CR_ADCAL;
	while (ADC1->CR & ADC_CR_ADCAL)
		;

	// ADC aanzetten
	ADC1->CR |= ADC_CR_ADEN;

	// Kanalen instellen NTC en POT
	ADC1->SMPR1 |= (ADC_SMPR1_SMP5_0 | ADC_SMPR1_SMP5_1 | ADC_SMPR1_SMP5_2); //Hoogste frequentie 111
	ADC1->SMPR1 |= (ADC_SMPR1_SMP6_0 | ADC_SMPR1_SMP6_1 | ADC_SMPR1_SMP6_2); //Hoogste frequentie 111

	//NTC
	GPIOA->MODER &= ~GPIO_MODER_MODE0_Msk; // port mode register mask van GPIOA pin 0 laag zetten
	GPIOA->MODER |= GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1; //register poort modus van GPIOA pin 0 op 11 zetten -> analog mode

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

	// CPU Frequentie = 48 MHz
	// Systick interrupt elke 1 ms (1kHz)  --> 48000000 Hz / 1000 Hz --> Reload = 48000
	SysTick_Config(48000);

	// Interrupt aanzetten met een prioriteit van 128
	NVIC_SetPriority(SysTick_IRQn, 128);
	NVIC_EnableIRQ(SysTick_IRQn);

	// TIMER
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;

	//Configureren GPIO
	GPIOB->MODER &= ~GPIO_MODER_MODE8_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE8_1;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT8;
	GPIOB->AFR[1] = (GPIOB->AFR[1] & (~GPIO_AFRH_AFSEL8_Msk)) | (0xE << GPIO_AFRH_AFSEL8_Pos);
	//Instellen Timer, hoofdteller
	TIM16->PSC = 0;
	TIM16->ARR = 24000;
	TIM16->CCR1 = 12000;

	while (1) {
		//reset kanalen
		ADC1->SQR1 &= ~(ADC_SQR1_SQ1_0 | ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_2
				| ADC_SQR1_SQ1_3);
		// Kanalen instellen NTC
		ADC1->SQR1 |= (ADC_SQR1_SQ1_0 | ADC_SQR1_SQ1_2); 	//Kanaal 6 => 101

		// Start de ADC en wacht tot de sequentie klaar is
		ADC1->CR |= ADC_CR_ADSTART;

		while (!(ADC1->ISR & ADC_ISR_EOC))
			;

		// Lees de waarde in
		waarde = ADC1->DR;

		V = (waarde * 3.0f) / 4096.0f;
		R = (10000.0f * V) / (3.0f - V);
		temperatuur = 10 * ((1.0f / ((logf(R / 10000.0f) / 3936.0f) + (1.0f / 298.15f))) - 273.15f);
		delay(200);
		//Instellen Timer, capture & compare
		TIM16->CCMR1 &= ~TIM_CCMR1_CC1S;
		TIM16->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1FE;
		TIM16->CCER |= TIM_CCER_CC1E;
		TIM16->CCER &= ~TIM_CCER_CC1P;

		//reset kanalen
		ADC1->SQR1 &= ~(ADC_SQR1_SQ1_0 | ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_2
				| ADC_SQR1_SQ1_3);

		// Kanalen instellen POT
		ADC1->SQR1 = (ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_2);

		ADC1->CR |= ADC_CR_ADSTART;
		while (!(ADC1->ISR & ADC_ISR_EOC))
			;
		input_pot = ADC1->DR;

		while (temperatuur > input_pot / 10) {
			TIM16->BDTR |= TIM_BDTR_MOE;
			TIM16->CR1 |= TIM_CR1_CEN;
			if (i < 500) {
				TIM16->ARR = 24000;
				TIM16->CCR1 = 12000;
				delay(10);
			}
			else if (i < 1000) {
				TIM16->ARR = 48000;
				TIM16->CCR1 = 24000;
				delay(10);
			}

			else {
				i = 0;
			}

			//reset kanalen
			ADC1->SQR1 &= ~(ADC_SQR1_SQ1_0 | ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_2| ADC_SQR1_SQ1_3);
			// Kanalen instellen NTC
			ADC1->SQR1 |= (ADC_SQR1_SQ1_0 | ADC_SQR1_SQ1_2);
			// Start de ADC en wacht tot de sequentie klaar is
			ADC1->CR |= ADC_CR_ADSTART;
			while (!(ADC1->ISR & ADC_ISR_EOC))
				;
			// Lees de waarde in
			waarde = ADC1->DR;

			V = (waarde * 3.0f) / 4096.0f;
			R = (10000.0f * V) / (3.0f - V);
			temperatuur = 10 * ((1.0f / ((logf(R / 10000.0f) / 3936.0f)+ (1.0f / 298.15f))) - 273.15f);
			delay(200);


			//reset kanalen
			ADC1->SQR1 &= ~(ADC_SQR1_SQ1_0 | ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_2| ADC_SQR1_SQ1_3);
			// Kanalen instellen POT
			ADC1->SQR1 = (ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_2);
			ADC1->CR |= ADC_CR_ADSTART;
			while (!(ADC1->ISR & ADC_ISR_EOC))
			;
			input_pot = ADC1->DR;


			i++;
		}

		TIM16->BDTR &= ~TIM_BDTR_MOE;
		TIM16->CR1 &= ~TIM_CR1_CEN;

	}
}
