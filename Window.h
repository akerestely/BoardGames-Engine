#pragma once

struct SDL_Window;

namespace Engine
{
	enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4};

	class Window
	{
	public:
		Window(void);
		~Window(void);

		void Create(const char* windowTitle, uint screenWidth, uint screenHeight, uint currentFlags);

		void SwappBuffer();

		bool IsFullscreen();
		void Fullscreen(bool visibility);

		uint GetScreenWidth() { return screenWidth; }
		uint GetScreenHeight() { return screenHeight; }

	private:
		SDL_Window *sdlWindow;
		uint screenWidth, screenHeight;
	};
}

