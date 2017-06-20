#pragma once

namespace Engine
{
	class FpsLimiter
	{
	public:
		FpsLimiter();
		void Init(uint targetFps);

		void SetMaxFps(uint targetFps);

		void Begin();

		//will return current fps
		float End(bool bLimit = true);
	private:
		// returns fps
		float calculateFps();

		static const uint kNumSamples = 10;
		uint frameTimes[kNumSamples];

		uint maxFps;
		float maxFrameTime;

		uint startTicks;
		uint currentFrame;
	};
}