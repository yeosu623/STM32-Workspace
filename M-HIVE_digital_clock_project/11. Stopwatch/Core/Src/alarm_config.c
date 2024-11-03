#include "main.h"
#include "clock.h"
#include "clock_config.h"
#include "alarm.h"
#include "alarm_config.h"
#include "buzzer.h"
#include "7SEG.h"
#include "CLCD.h"
#include "7SEG_control.h"

extern System system;
extern Clock clock;
extern Clock_Config clock_config;
extern Alarm alarm;
extern Alarm_Config alarm_config;
extern Button button3;
extern Button button4;
extern Buzzer buzzer;
extern CLCD clcd;

void init_alarm_config()
{
	system.wait_milisecond = 0;
	alarm.select = 0;
	alarm_config.choose = SELECT;
}

void show_alarm_config()
{
	// display on CLCD
	sprintf(clcd.str1, "ALARM #%d %s %s",
			alarm.select + 1,
			alarm.activate[alarm.select] ? "ON " : "OFF",
			alarm.repeat[alarm.select] ? "RPT" : "ONC");
	sprintf(clcd.str2, "SET     %s %02d:%02d",
			alarm.hour[alarm.select] <  12 ? "AM" : "PM",
			alarm.hour[alarm.select] == 12 ?  12  : alarm.hour[alarm.select] % 12,
			alarm.minute[alarm.select]);

	blink_choose_alarm_config_element();
	CLCD_Puts(0, 0, clcd.str1);
	CLCD_Puts(0, 1, clcd.str2);

	// display on 7-seg
	show_7seg();

	// if idle time over 30 seconds, return to alarm mode
	if(system.wait_milisecond > 30000) {
		system.wait_milisecond = 0;
		system.mode = ALARM;
	}
}

void blink_choose_alarm_config_element()
{
	if(system.wait_milisecond > 250 && !clock.point)
	{
		switch(alarm_config.choose)
		{
		case SELECT:
			clcd.str1[7] = ' ';
			break;
		case ALARM_MINUTE:
			clcd.str2[14] = ' ';
			clcd.str2[15] = ' ';
			break;
		case ALARM_HOUR:
			clcd.str2[11] = ' ';
			clcd.str2[12] = ' ';
			break;
		case REPEAT:
			clcd.str1[13] = ' ';
			clcd.str1[14] = ' ';
			clcd.str1[15] = ' ';
			break;
		case ACTIVATE:
			clcd.str1[9] = ' ';
			clcd.str1[10] = ' ';
			clcd.str1[11] = ' ';
			break;
		}
	}
}

void alarm_config_next_item()
{
	switch(alarm_config.choose)
	{
	case SELECT:       alarm_config.choose = ALARM_MINUTE; break;
	case ALARM_MINUTE: alarm_config.choose = ALARM_HOUR;   break;
	case ALARM_HOUR:   alarm_config.choose = REPEAT;       break;
	case REPEAT:       alarm_config.choose = ACTIVATE;     break;
	case ACTIVATE:     alarm_config.choose = SELECT;       break;
	}
}

void alarm_config_increase_once()
{
	switch(alarm_config.choose)
	{
	case SELECT:
		alarm.select++;
		if(alarm.select >= 5) alarm.select = 0;
		break;

	case ALARM_MINUTE:
		alarm.minute[alarm.select]++;
		if(alarm.minute[alarm.select] >= 60) alarm.minute[alarm.select] = 0;
		break;

	case ALARM_HOUR:
		alarm.hour[alarm.select]++;
		if(alarm.hour[alarm.select] >= 24) alarm.hour[alarm.select] = 0;
		break;

	case REPEAT:
		alarm.repeat[alarm.select] = !alarm.repeat[alarm.select];
		break;

	case ACTIVATE:
		alarm.activate[alarm.select] = !alarm.activate[alarm.select];
		break;
	}
}

void alarm_config_decrease_once()
{
	switch(alarm_config.choose)
	{
	case SELECT:
		alarm.select--;
		if(alarm.select < 0) alarm.select = 4;
		break;

	case ALARM_MINUTE:
		alarm.minute[alarm.select]--;
		if(alarm.minute[alarm.select] < 0) alarm.minute[alarm.select] = 59;
		break;

	case ALARM_HOUR:
		alarm.hour[alarm.select]--;
		if(alarm.hour[alarm.select] < 0) alarm.hour[alarm.select] = 23;
		break;

	case REPEAT:
		alarm.repeat[alarm.select] = !alarm.repeat[alarm.select];
		break;

	case ACTIVATE:
		alarm.activate[alarm.select] = !alarm.activate[alarm.select];
		break;
	}
}

void alarm_config_increase_continuous_150ms()
{
	if(button3.repeating_milisecond >= 150)
	{
		button3.repeating_milisecond = 0;
		alarm_config_increase_once();
	}
}

void alarm_config_increase_continuous_20ms()
{
	if(button3.repeating_milisecond >= 20)
	{
		button3.repeating_milisecond = 0;
		alarm_config_increase_once();
	}
}

void alarm_config_decrease_continuous_150ms()
{
	if(button4.repeating_milisecond >= 150)
	{
		button4.repeating_milisecond = 0;
		alarm_config_decrease_once();
	}
}

void alarm_config_decrease_continuous_20ms()
{
	if(button4.repeating_milisecond >= 20)
	{
		button4.repeating_milisecond = 0;
		alarm_config_decrease_once();
	}
}
