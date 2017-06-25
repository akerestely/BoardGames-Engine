#pragma once
#include "Size.h"

struct SDL_Window;

namespace Engine
{
	enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4};

	class Window
	{
	public:
		Window();
		~Window();

		void Create(const char* windowTitle, uint screenWidth, uint screenHeight, uint currentFlags);

		void SwappBuffer();

		bool IsFullscreen();
		void Fullscreen(bool visibility);

	private:
		SDL_Window *m_pSdlWindow;
		sizei m_size;
	};
}

