#include "Timing.h"

#include <cstring>
#include "SDl/SDL.h"
#include <algorithm>

namespace Engine
{
	FpsLimiter::FpsLimiter()
	{

	}

	void FpsLimiter::Init(uint targetFps)
	{
		currentFrame = 0;
		memset(frameTimes, 0, sizeof(frameTimes));
		SetMaxFps(targetFps);
	}

	void FpsLimiter::SetMaxFps(uint targetFps)
	{
		maxFps = targetFps;
		maxFrameTime = 1000.f / maxFps;
	}

	void FpsLimiter::Begin()
	{
		startTicks = SDL_GetTicks();
	}

	float FpsLimiter::End()
	{
		uint currentTicks = SDL_GetTicks();
		uint frameTime = currentTicks - startTicks;
		if (frameTime < maxFrameTime)
		{
			uint msToWait = (uint)maxFrameTime - frameTime;
			SDL_Delay(msToWait);
			// calculate new frame time, as we slept some time (this should be ~maxFrameTime)
			currentTicks = SDL_GetTicks();
			frameTime = currentTicks - startTicks;
		}

		frameTimes[currentFrame++ % kNumSamples] = frameTime;

		return calculateFps();
	}

	float FpsLimiter::calculateFps()
	{
		float frameTimeAverage = 0;
		for (int frameTime : frameTimes)
			frameTimeAverage += (float)frameTime;
		frameTimeAverage /= std::min(currentFrame, kNumSamples);

		return 1000.0f / frameTimeAverage;
	}
}