#ifndef _TIMER_H_
#define _TIMER_H_
#include "stm32f407xx.h"

void timer_enable(TIM_TypeDef* timer);
void timer_disable(TIM_TypeDef* timer);
void timer_reload(TIM_TypeDef* timer);
void timer_init(TIM_TypeDef* timer,int psc,int arr);
void timer_start(TIM_TypeDef* timer);
void timer_stop(TIM_TypeDef* timer);

#endif
