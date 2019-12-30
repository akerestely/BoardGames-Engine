#pragma once
#include <cstdint>

namespace Engine
{
	class FpsLimiter
	{
	public:
		FpsLimiter() = default;

		void Init(uint32_t targetFps);

		void SetMaxFps(uint32_t targetFps);

		void Begin();

		//will return current fps
		float End(bool bLimit = true);

	private:
		// returns fps
		float calculateFps();

	private:
		static const uint32_t kNumSamples = 10;

		uint32_t m_frameTimes[kNumSamples];

		uint32_t m_maxFps;
		float m_maxFrameTime;

		uint32_t m_startTicks;
		uint32_t m_currentFrame;
	};
}