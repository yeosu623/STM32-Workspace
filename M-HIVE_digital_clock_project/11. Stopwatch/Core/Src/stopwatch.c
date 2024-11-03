#include "main.h"
#include "stopwatch.h"
#include "CLCD.h"
#include "7SEG.h"

extern System system;
extern Lap lap;
extern Stopwatch stopwatch;
extern CLCD clcd;

void init_stopwatch()
{
	system.wait_milisecond = 0;
}

void show_stopwatch()
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

	// 스탑워치가 STOPPED 일떄, 가만히 30초 경과시 시계 모드로 복귀
	if(system.wait_milisecond > 30000 && stopwatch.state == STOPPED) {
		system.wait_milisecond = 0;
		system.mode = CLOCK;
	}
}

void clear_stopwatch()
{
	stopwatch.time.hour = 0;
	stopwatch.time.minute = 0;
	stopwatch.time.second = 0;
	stopwatch.time.milisecond = 0;
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

