#include "helper_functions.h"
#include "stm32f407xx.h"

void set_gpio(GPIO_TypeDef* gpio,int pin){
	gpio->BSRR |= (1 << pin);
}

void reset_gpio(GPIO_TypeDef* gpio,int pin){                                                                                                                
	gpio->BSRR |= (1 << (pin + 16));
}

void delay_without_interrupt(int msec){
	int loop_cnt = 500*msec;
	while(loop_cnt){
		loop_cnt--;
	}
	return;
}

int read_gpio(GPIO_TypeDef* gpio,int pin){
	return (gpio-> IDR >> pin) & 1;       
}

void FPU_init(void){
	SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));
	__DSB();
	__ISB();
}

int GPIO_init_AF(GPIO_TypeDef* gpio,int pin){
	if(gpio == GPIOA){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	}
	else{
		return -1;
	}
	
	gpio -> MODER &= ~(0b11 << (2*pin));
	gpio -> MODER |= 0b10;        // AF
	
	gpio -> AFR[0] &= ~GPIO_AFRL_AFSEL0_Msk;     // 0xF
	gpio -> AFR[0] |= (1 << GPIO_AFRL_AFSEL0_Pos);  // AF1 PWM(TIM2)
	return 0;
}

void PWM_channel_init(TIM_TypeDef* timer){
	// pwm mode 1 
	timer->CCMR1 &= ~TIM_CCMR1_OC1M_Msk;
	timer->CCMR1 |= (6 << TIM_CCMR1_OC1M_Pos);
	//OCpreload enable
	timer->CCMR1 &= ~TIM_CCMR1_OC1PE_Msk;
	timer->CCMR1 |= (1 << TIM_CCMR1_OC1PE_Pos);
	//Active high for channel 1 polarity
	timer->CCER &= ~TIM_CCER_CC1P_Msk;
	timer->CCER |= (0 << TIM_CCER_CC1E_Pos);
	//Enable for channel 1 output
	timer->CCER &= ~TIM_CCER_CC1E_Msk;
	timer->CCER |= (1 << TIM_CCER_CC1E_Pos);
	//set compare resig
	timer->CCR1 = 50;
}

void music_psc(TIM_TypeDef* timer,int note){
	switch(note){
		case 1:
			timer->PSC = 613;
			break;
		case 2:
			timer->PSC = 548;
			break;
		case 3:
			timer->PSC = 485;
			break;
		case 4:
			timer->PSC = 458;
			break;
		case 5:
			timer->PSC = 408;
			break;
		case 6:
			timer->PSC = 364;
			break;
		case 7:
			timer->PSC = 324;
			break;
		case 8 :
			timer->PSC = 306;
			break;
	}
			
}