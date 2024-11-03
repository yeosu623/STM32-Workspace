#include "main.h"
#include "tim.h"
#include "buzzer.h"

extern Buzzer buzzer;

void beep_buzzer(int beep_milisecond, Tone tone)
{
	// ready
	buzzer.beep_milisecond = beep_milisecond;
	buzzer.state = BEEP;
	buzzer.tone = tone;

	// running
	buzzer_start(tone);
}

void beep_buzzer_check()
{
	// stop
	if(buzzer.running_milisecond > buzzer.beep_milisecond)
	{
		buzzer.running_milisecond = 0;
		buzzer.beep_milisecond = 0;
		buzzer.state = STOP;

		buzzer_stop();
	}
}

void buzzer_start(Tone tone)
{
	buzzer.tone = tone;

	if(buzzer.config == ON)
	{
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		TIM2->PSC = buzzer.tone;
	}
}

void buzzer_stop()
{
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
}
