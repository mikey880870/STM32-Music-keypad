#ifndef _HELPER_FUNCTIONS_H_
#define _HELPER_FUNCTIONS_H_

#include "stm32f407xx.h"

void set_gpio(GPIO_TypeDef* gpio,int pin);
void reset_gpio(GPIO_TypeDef* gpio,int pin);
void delay_without_interrupt(int msec);
int read_gpio(GPIO_TypeDef* gpio,int pin);

void FPU_init(void);
int GPIO_init_AF(GPIO_TypeDef* gpio,int pin);
void PWM_channel_init(TIM_TypeDef* timer);
void music_psc(TIM_TypeDef* timer,int note);

#endif
