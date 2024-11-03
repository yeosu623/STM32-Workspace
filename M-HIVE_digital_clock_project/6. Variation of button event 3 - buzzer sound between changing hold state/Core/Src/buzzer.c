#include "main.h"
#include "tim.h"
#include "buzzer.h"

extern Buzzer buzzer;

void beep_buzzer(int beep_milisecond, Tone tone) {
	// ready
	buzzer.beep_milisecond = beep_milisecond;
	buzzer.state = BEEP;
	buzzer.tone = tone;

	// running
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	TIM2->PSC = buzzer.tone;
}

void beep_buzzer_check() {
	// stop
	if(buzzer.running_milisecond > buzzer.beep_milisecond) {
		buzzer.running_milisecond = 0;
		buzzer.beep_milisecond = 0;
		buzzer.state = OFF;

		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	}
}
