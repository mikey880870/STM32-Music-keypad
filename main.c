#include "stm32f407xx.h"
#include "keypad.h"
#include "helper_functions.h"
#include "timer.h"

#define COL_gpio GPIOB
#define COL_pin 11   //PB14 -> 1
#define ROW_gpio GPIOC 
#define Row_pin 6
#define COUNTER_timer TIM2
#define BEEP_gpio GPIOA
#define BEEP_pin 0

int main(void){
	FPU_init();
	
	if(init_keypad(ROW_gpio,COL_gpio,Row_pin,COL_pin)!= 0){
		return -1;
	}
		
	if(GPIO_init_AF(BEEP_gpio,BEEP_pin) != 0){
		return -1;
	}
		
	int keypad[3][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,9}
	};
	
	timer_enable(COUNTER_timer);
	timer_init(COUNTER_timer,548,100);
	PWM_channel_init(COUNTER_timer);

	while(1){
		int input = 0;
		for(int i = 0;i < 3;i++){   	//row
			for(int j = 0;j < 3;j++){ 	//column
				if(check_keypad_input_one(ROW_gpio,COL_gpio,Row_pin,COL_pin,i,j)){
					input = 1;
					music_psc(COUNTER_timer,keypad[i][j]);
					timer_start(COUNTER_timer);
				}
			}
		}
		if(input == 0){
			timer_stop(COUNTER_timer);
		}
	}
	
	return 0;
}
