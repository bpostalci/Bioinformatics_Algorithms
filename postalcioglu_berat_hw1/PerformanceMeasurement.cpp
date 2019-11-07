#include "PerformanceMeasurement.h"
#include <stdio.h>

void display_performance(clock_t start, clock_t end)
{
	double ellapsed_time = ((double)(end - start) * 1000);
	printf("ellapsed time in microseconds = %.5f\n", ellapsed_time);
}