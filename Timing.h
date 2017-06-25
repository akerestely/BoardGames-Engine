#pragma once

namespace Engine
{
	class FpsLimiter
	{
	public:
		void Init(uint targetFps);

		void SetMaxFps(uint targetFps);

		void Begin();

		//will return current fps
		float End(bool bLimit = true);

	private:
		// returns fps
		float calculateFps();

	private:
		static const uint kNumSamples = 10;

		uint m_frameTimes[kNumSamples];

		uint m_maxFps;
		float m_maxFrameTime;

		uint m_startTicks;
		uint m_currentFrame;
	};
}