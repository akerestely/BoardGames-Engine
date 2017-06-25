#pragma once
#include "BaseTypes.h"
#include "Window.h"
#include "InputManager.h"
#include "Timing.h"
#include "Size.h"

namespace Engine
{
	class IGame
	{
	public:
		void Run();
		virtual ~IGame() = default;

	protected:
		virtual void onInit() {};
		virtual void onUpdate() {};
		virtual void onRender() {};
		virtual void onDestroy() {};

		void setMaxFps(uint maxFps);
		float getFps() const { return m_fps; }
		uint getTime() const;

	protected:
		sizei m_screenSize = { 800, 600 };
		std::string m_windowTitle = "Game";

		InputManager m_inputManager;

	private:
		enum class State
		{
			Running,
			Exiting
		};

	private:
		void initSystems();
		void processInput();
		void render();
		void gameLoop();

	private:
		Window m_window;
		State m_gameState;

		FpsLimiter m_fpsLimiter;
		uint m_maxFps = 60;
		float m_fps = 0;

		bool m_bLimitFps = true;
		bool m_bSkipRendering = false;
	};
}