#include "main.h"
#include "stopwatch.h"
#include "CLCD.h"
#include "7SEG.h"

extern Lap lap;
extern Stopwatch stopwatch;
extern CLCD clcd;

void stopwatch_show_time()
{
  	// 0.5초마다 스탑워치 시간의 점을 토글
	if(stopwatch.time.milisecond < 500) stopwatch.point = ON;
	else stopwatch.point = OFF;

	// 7-Seg에 시간을 출력
	_7SEG_SetNumber(DGT1, stopwatch.time.second % 10, stopwatch.point);
	_7SEG_SetNumber(DGT2, stopwatch.time.milisecond / 100, OFF);

	// CLCD에 시간을 출력
	sprintf(clcd.str1, "STW %02d:%02d:%02d%c%03d",
			stopwatch.time.hour,
			stopwatch.time.minute,
			stopwatch.time.second,
			stopwatch.point ? '.' : ' ',
			stopwatch.time.milisecond);
	CLCD_Puts(0, 0, clcd.str1);
}

void stopwatch_clear_time()
{
	stopwatch.time.hour = 0;
	stopwatch.time.minute = 0;
	stopwatch.time.second = 0;
	stopwatch.time.milisecond = 0;
}

void stopwatch_run_and_pause()
{
	if(stopwatch.state == RUNNING) stopwatch.state = PAUSED;
	else stopwatch.state = RUNNING;
}

void stopwatch_measure_lap_or_stop()
{
	if(stopwatch.state == RUNNING) lap.state = MEASURE; // stopwatch가 실행중일때는 lap 측정
	else // stopwatch가 일시정지 되어 있거나 멈춰 있을 떄는
	{
		stopwatch.state = STOPPED; // stopwatch를 초기화하고
		stopwatch_clear_time();

		lap.state = CLEAR; // lap도 초기화
	}
}

void stopwatch_dlsplay_record()
{
	lap.state = DISPLAY_RECORD;
}

void stopwatch_convert_time_format()
{
	if(stopwatch.time.milisecond == 1000)
	{
		stopwatch.time.milisecond = 0;
		stopwatch.time.second++;
	}
	if(stopwatch.time.second == 60)
	{
		stopwatch.time.second = 0;
		stopwatch.time.minute++;
	}
	if(stopwatch.time.minute == 60)
	{
		stopwatch.time.minute = 0;
		stopwatch.time.hour++;
	}
}

