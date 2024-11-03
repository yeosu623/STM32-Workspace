#include "main.h"
#include "lap.h"
#include "CLCD.h"

extern Lap lap;
extern Stopwatch stopwatch;
extern CLCD clcd;

/* lap을 저장하는 함수 */
void lap_measure()
{
	// lap이 9개면 꽉 차 있다고 표시한다.
	if(lap.count == 9) sprintf(clcd.str2, "LAP FULL(9/9)   ");

	// lap이 9개가 아니면 lap을 저장한다.
	else
	{
		// lap의 정보에 현재 stopwatch의 시간을 담는다.
		lap.record[lap.count].hour = stopwatch.time.hour;
		lap.record[lap.count].minute = stopwatch.time.minute;
		lap.record[lap.count].second = stopwatch.time.second;
		lap.record[lap.count].milisecond = stopwatch.time.milisecond;

		// lap의 정보를 string에 넣어둔다.
		sprintf(clcd.str2, "LP%1d %02d:%02d:%02d.%03d",
				lap.count + 1,
				lap.record[lap.count].hour,
				lap.record[lap.count].minute,
				lap.record[lap.count].second,
				lap.record[lap.count].milisecond);

		// lap 개수를 1 증가시킨다.
		lap.count++;
	}

	// CLCD에 lap의 정보를 표시한다.
	CLCD_Puts(0, 1, clcd.str2);

	// 만약 이전의 lap 정보를 보여주고 있었다면, 처음부터 보여주도록 순서를 초기화 한다.
	lap.show_num = 0;

	// 그 후 다음 lap 조작이 준비되었다고 상태를 바꾸어 준다.
	lap.state = READY;
}


/* 저장된 lap을 표시해주는 함수 */
void lap_display_record()
{
	// 만약 lap이 없다면, 없다고 표시해준다.
	if(lap.count == 0) sprintf(clcd.str2, "NO LAP          ");

	// 만약 lap이 있다면, 첫 번째 lap부터 순차적으로 표시해준다.
	else
	{
		// 마지막 lap에 도달할 경우는, 첫 번쨰 lap으로 돌아간다.
		if(lap.show_num == lap.count) lap.show_num = 0;

		// 해당 lap의 정보를 string 변수에 담는다.
		sprintf(clcd.str2, "%d/%d %02d:%02d:%02d.%03d",
				lap.show_num + 1,
				lap.count,
				lap.record[lap.show_num].hour,
				lap.record[lap.show_num].minute,
				lap.record[lap.show_num].second,
				lap.record[lap.show_num].milisecond);

		// 그 후 다음 lap을 출력할 준비를 하기 위해, 순서를 1 증가시킨다.
		lap.show_num++;
	}

	// 해당 lap의 정보를 CLCD에 출력해 준 다음,
	CLCD_Puts(0, 1, clcd.str2);

	// 다음 lap 조작이 준비 되었다고 상태를 바꾸어 준다.
	lap.state = READY;
}


/* lap을 초기화 하는 함수 */
void lap_clear()
{
	// 모든 lap 관련 정보를 초기화 해준다.
	lap.count = 0;
	lap.show_num = 0;
	sprintf(clcd.str2, "                ");
	CLCD_Puts(0, 1, clcd.str2);

	// 그 후 다음 lap 조작이 준비 되었다고 상태를 바꾸어 준다.
	lap.state = READY;
}
