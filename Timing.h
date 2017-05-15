#pragma once
#include "BaseTypes.h"

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
		float End();
	private:
		// returns fps
		float calculateFps();

		static const int kNumSamples = 10;
		uint frameTimes[kNumSamples];

		uint maxFps;
		float maxFrameTime;

		uint startTicks;
		int currentFrame;
	};
}