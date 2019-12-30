#include "Timing.h"

#include <cstring>
#include "SDL.h"
#include <algorithm>

namespace Engine
{
	void FpsLimiter::Init(uint32_t targetFps)
	{
		m_currentFrame = 0;
		memset(m_frameTimes, 0, sizeof(m_frameTimes));
		SetMaxFps(targetFps);
	}

	void FpsLimiter::SetMaxFps(uint32_t targetFps)
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
		uint32_t currentTicks = SDL_GetTicks();
		uint32_t frameTime = currentTicks - m_startTicks;
		if (bLimit && frameTime < m_maxFrameTime)
		{
			uint32_t msToWait = (uint32_t)m_maxFrameTime - frameTime;
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