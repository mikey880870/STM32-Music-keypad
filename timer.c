#include "timer.h"
#include "stm32f407xx.h"

void timer_enable(TIM_TypeDef* timer){
	if(timer == TIM2){
		RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
		//while (!(RCC->APB1ENR & RCC_APB1ENR_TIM2EN));
	} 
}

void timer_disable(TIM_TypeDef* timer){
	if(timer == TIM2){
		RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN;
	}
}

void timer_reload(TIM_TypeDef* timer){
	timer->EGR |= TIM_EGR_UG;
}

void timer_init(TIM_TypeDef* timer,int psc,int arr){
	timer->PSC = (uint32_t)(psc-1);
	timer->ARR = (uint32_t)(arr-1);
	timer->EGR |= TIM_EGR_UG;
}

void timer_start(TIM_TypeDef* timer){
	timer->CR1 |= TIM_CR1_CEN;
}

void timer_stop(TIM_TypeDef* timer){
	timer->CR1 &= ~TIM_CR1_CEN;
}
