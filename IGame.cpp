#include "IGame.h"

#include "Engine.h"
#include "SDL_events.h"
#include "SDL_timer.h"
#include "glew.h"

namespace Engine
{
	void IGame::Run()
	{
		initSystems();
		m_gameState = State::Running;
		gameLoop();
		onDestroy();
	}

	void IGame::setMaxFps(uint32_t maxFps)
	{
		m_maxFps = maxFps;
		m_fpsLimiter.SetMaxFps(maxFps);
	}

	uint32_t IGame::getTime() const
	{
		return SDL_GetTicks();
	}

	void IGame::initSystems()
	{
		Engine::Init();
		m_window.Create(m_windowTitle.c_str(), m_screenSize.width, m_screenSize.height, 0);
		m_fpsLimiter.Init(m_maxFps);

		onInit();
	}

	void IGame::processInput()
	{
		SDL_Event evnt;
		const float CAMERA_SPEED = 5.0f;
		const float SCALE_SPEED = 0.1f;
		while (SDL_PollEvent(&evnt))
		{
			switch (evnt.type)
			{
			case SDL_QUIT:
				m_gameState = State::Exiting;
				break;
			case SDL_KEYDOWN:
				m_inputManager.PressKey(evnt.key.keysym.sym);
				switch (evnt.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					m_gameState = State::Exiting;
					break;
				case SDLK_F1:
					m_bSkipRendering = !m_bSkipRendering;
					m_bLimitFps = !m_bLimitFps;
					break;
				case SDLK_F4:
					m_window.Fullscreen(!m_window.IsFullscreen());
					break;
				case SDLK_F5:
					m_bSkipRendering = !m_bSkipRendering;
					break;
				case SDLK_F6:
					m_bLimitFps = !m_bLimitFps;
					break; 
				}
				break;
			case SDL_KEYUP:
				m_inputManager.ReleaseKey(evnt.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_inputManager.PressKey(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_inputManager.ReleaseKey(evnt.button.button);
				break;
			case SDL_MOUSEMOTION:
				if (SDL_GetRelativeMouseMode() == SDL_TRUE)
					m_inputManager.SetMouseCoordsRel(evnt.motion.xrel, evnt.motion.yrel);
				else
					m_inputManager.SetMouseCoords(evnt.motion.x, evnt.motion.y);
				break;
			}
		}
	}

	void IGame::render()
	{
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		onRender();
		m_window.SwappBuffer();
	}

	void IGame::gameLoop()
	{
		while (m_gameState != State::Exiting)
		{
			m_fpsLimiter.Begin();

			processInput();
			onUpdate();
			if (!m_bSkipRendering)
				render();

			m_fps = m_fpsLimiter.End(m_bLimitFps);
		}
	}
}