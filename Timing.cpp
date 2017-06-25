#include "BaseTypes.h"
#include "Timing.h"

#include <cstring>
#include "SDL.h"
#include <algorithm>

namespace Engine
{
	void FpsLimiter::Init(uint targetFps)
	{
		m_currentFrame = 0;
		memset(m_frameTimes, 0, sizeof(m_frameTimes));
		SetMaxFps(targetFps);
	}

	void FpsLimiter::SetMaxFps(uint targetFps)
	{
		m_maxFps = targetFps;
		m_maxFrameTime = 1000.f / m_maxFps;
	}

	void FpsLimiter::Begin()
	{
		m_startTicks = SDL_GetTicks();
	}

	float FpsLimiter::End(bool bLimit /*= true*/)
{
		uint currentTicks = SDL_GetTicks();
		uint frameTime = currentTicks - m_startTicks;
		if (bLimit && frameTime < m_maxFrameTime)
		{
			uint msToWait = (uint)m_maxFrameTime - frameTime;
			SDL_Delay(msToWait);
			// calculate new frame time, as we slept some time (this should be ~maxFrameTime)
			currentTicks = SDL_GetTicks();
			frameTime = currentTicks - m_startTicks;
		}

		m_frameTimes[m_currentFrame++ % kNumSamples] = frameTime;

		return calculateFps();
	}

	float FpsLimiter::calculateFps()
	{
		float frameTimeAverage = 0;
		for (int frameTime : m_frameTimes)
			frameTimeAverage += (float)frameTime;
		frameTimeAverage /= std::min(m_currentFrame, kNumSamples);

		return 1000.0f / frameTimeAverage;
	}
}