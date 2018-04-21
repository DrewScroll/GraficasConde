#include "IDVUtils\IDVTimer.h"
#include <stdio.h>

IDVTimer::IDVTimer() {

}
IDVTimer::~IDVTimer() {

}

void IDVTimer::Init() {
#ifdef OS_WINDOWS
	LARGE_INTEGER y;
	QueryPerformanceFrequency(&y);
	Frequency = double(y.QuadPart) / 1000000.0;
	StartTime.QuadPart = 0;
	Dt = 0.0;
	QueryPerformanceCounter(&StartTime);
#elif defined(OS_LINUX)
	gettimeofday(&StartTime, 0);
#endif
}

void IDVTimer::Update() {
#ifdef OS_WINDOWS
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);
	Dt = double(end.QuadPart - StartTime.QuadPart) / Frequency;
	QueryPerformanceCounter(&StartTime);
	DtSecs = (Dt / 1000000.0);
#elif defined(OS_LINUX)
	timeval actual;
	gettimeofday(&actual, 0);
	DtSecs = double((actual.tv_sec - StartTime.tv_sec) + (actual.tv_usec - StartTime.tv_usec) / 1000000.0);
	gettimeofday(&StartTime, 0);
	// printf("FPS %f \n",1.0/DtSecs);
#endif
}

float	IDVTimer::GetDTSecs() {
	return static_cast<float>(DtSecs);
}