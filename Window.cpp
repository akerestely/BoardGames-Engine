#include "BaseTypes.h"
#include "Window.h"

#include "Errors.h"
#include <stdio.h>
#include "SDL_video.h"
#include "glew.h"

namespace Engine
{

	Window::Window()
		: m_pSdlWindow(nullptr)
	{
		// empty
	}

	Window::~Window()
	{
		if(m_pSdlWindow)
			SDL_DestroyWindow(m_pSdlWindow);
	}

	void Window::Create(const char* windowTitle, uint screenWidth, uint screenHeight, uint currentFlags)
	{
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE)
			flags |= SDL_WINDOW_HIDDEN;
		if (currentFlags & FULLSCREEN)
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		if (currentFlags & BORDERLESS)
			flags |= SDL_WINDOW_BORDERLESS;

		m_pSdlWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		m_size.width = screenWidth;
		m_size.height = screenHeight;

		if(m_pSdlWindow==nullptr)
			fatalError("SDL window could not be loaded");

		SDL_GLContext glContex = SDL_GL_CreateContext(m_pSdlWindow);
		if(glContex == nullptr)
			fatalError("SQL_GL context could not be created");

		GLenum glewError=glewInit();
		if(glewError != GLEW_OK)
			fatalError("Could not initialize glew!");

		printf("***   OpenGl Version: %s   ***\n", glGetString(GL_VERSION));

		glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );

		//set v-sync
		SDL_GL_SetSwapInterval(0);

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::SwappBuffer()
	{
		SDL_GL_SwapWindow(m_pSdlWindow);
	}

	bool Window::IsFullscreen()
	{
		return SDL_GetWindowFlags(m_pSdlWindow) & SDL_WINDOW_FULLSCREEN;
	}

	void Window::Fullscreen(bool visibility)
	{
		if (visibility)
			SDL_SetWindowFullscreen(m_pSdlWindow, SDL_WINDOW_FULLSCREEN);
		else
			SDL_SetWindowFullscreen(m_pSdlWindow, 0);
	}
}
