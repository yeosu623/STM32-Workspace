#include "main.h"
#include "clock.h"
#include "clock_config.h"
#include "buzzer.h"
#include "7SEG.h"
#include "CLCD.h"
#include "7SEG_control.h"

extern System system;
extern Clock clock;
extern Clock_Config clock_config;
extern Button button3;
extern Button button4;
extern Buzzer buzzer;
extern CLCD clcd;

void init_clock_config()
{
	system.wait_milisecond = 0;
	clock_config.choose = SECOND;
}

void show_clock_config()
{
	// display on CLCD
	sprintf(clcd.str1, "CLOCK %4d.%2d.%2d",
			clock.time.year,
			clock.time.month,
			clock.time.day);
	sprintf(clcd.str2, "SET     %2d:%2d:%2d",
			clock.time.hour,
			clock.time.minute,
			clock.time.second);

	blink_choose_element();
	CLCD_Puts(0, 0, clcd.str1);
	CLCD_Puts(0, 1, clcd.str2);

	// display on 7-seg
	show_7seg();

	// if idle time over 30 seconds, return to clock mode
	if(system.wait_milisecond > 30000) system.mode = CLOCK;
}

void blink_choose_element()
{
	if(system.wait_milisecond > 250 && !clock.point)
	{
		switch(clock_config.choose)
		{
		case YEAR:
			clcd.str1[6] = ' ';
			clcd.str1[7] = ' ';
			clcd.str1[8] = ' ';
			clcd.str1[9] = ' ';
			break;
		case MONTH:
			clcd.str1[11] = ' ';
			clcd.str1[12] = ' ';
			break;
		case DAY:
			clcd.str1[14] = ' ';
			clcd.str1[15] = ' ';
			break;
		case HOUR:
			clcd.str2[8] = ' ';
			clcd.str2[9] = ' ';
			break;
		case MINUTE:
			clcd.str2[11] = ' ';
			clcd.str2[12] = ' ';
			break;
		case SECOND:
			clcd.str2[14] = ' ';
			clcd.str2[15] = ' ';
			break;
		}
	}
}

void next_item()
{
	switch(clock_config.choose)
	{
	case SECOND: clock_config.choose = MINUTE; break;
	case MINUTE: clock_config.choose = HOUR;   break;
	case HOUR:   clock_config.choose = DAY;    break;
	case DAY:    clock_config.choose = MONTH;  break;
	case MONTH:  clock_config.choose = YEAR;   break;
	case YEAR:   clock_config.choose = SECOND; break;
	}
}

void increase_once()
{
	switch(clock_config.choose)
	{
	case SECOND:
		clock.time.milisecond = 0;
		clock.time.second = 0;
		break;

	case MINUTE:
		clock.time.minute++;
		if(clock.time.minute >= 60) clock.time.minute = 0;
		break;

	case HOUR:
		clock.time.hour++;
		if(clock.time.hour >= 24) clock.time.hour = 0;
		break;

	case DAY:
		clock.time.day++;
		if(check_day_reach_end()) clock.time.day = 1;
		break;

	case MONTH:
		clock.time.month++;
		if(clock.time.month >= 13) clock.time.month = 1;

		adjust_to_max_day();
		break;

	case YEAR:
		clock.time.year++;
		if(clock.time.year > 9999) clock.time.year = 9999;

		adjust_to_max_day();
		break;
	}
}

void decrease_once()
{
	switch(clock_config.choose)
	{
	case SECOND:
		clock.time.milisecond = 0;
		clock.time.second = 0;
		break;

	case MINUTE:
		clock.time.minute--;
		if(clock.time.minute < 0) clock.time.minute = 59;
		break;

	case HOUR:
		clock.time.hour--;
		if(clock.time.hour < 0) clock.time.hour = 23;
		break;

	case DAY:
		clock.time.day--;
		if(clock.time.day < 1) set_max_day();
		break;

	case MONTH:
		clock.time.month--;
		if(clock.time.month < 1) clock.time.month = 12;

		adjust_to_max_day();
		break;

	case YEAR:
		clock.time.year--;
		if(clock.time.year < 1900) clock.time.year = 1900;

		adjust_to_max_day();
		break;
	}
}

void increase_continuous_150ms()
{
	if(button3.repeating_milisecond >= 150)
	{
		button3.repeating_milisecond = 0;
		increase_once();
	}
}

void increase_continuous_20ms()
{
	if(button3.repeating_milisecond >= 20)
	{
		button3.repeating_milisecond = 0;
		increase_once();
	}
}

void decrease_continuous_150ms()
{
	if(button4.repeating_milisecond >= 150)
	{
		button4.repeating_milisecond = 0;
		decrease_once();
	}
}

void decrease_continuous_20ms()
{
	if(button4.repeating_milisecond >= 20)
	{
		button4.repeating_milisecond = 0;
		decrease_once();
	}
}

void adjust_to_max_day()
{
	int max_day[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // index 1 = month 1

	check_leap_year();
	if(clock.leap_year) max_day[2] = 29;

	if(clock.time.day > max_day[clock.time.month])
	   clock.time.day = max_day[clock.time.month];
}

