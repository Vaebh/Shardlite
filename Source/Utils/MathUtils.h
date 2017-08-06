#ifndef MATH_UTILS_SHARDLITE
#define MATH_UTILS_SHARDLITE

float LinearMap(float currentValue, float currentMin, float currentMax, float newMin, float newMax)
{
	float oldRange = currentMax - currentMin;
	float newRange = newMax - newMin;

	return (currentValue - currentMin) * newRange / oldRange + newMin;
}

#endif