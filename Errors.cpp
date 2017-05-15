#include "Errors.h"
#include <sdl/SDL.h>

namespace Engine
{
	extern void fatalError(const std::string &msg)
	{
		printf("%s\n", msg.c_str());
		system("pause");
		SDL_Quit();
		exit(1);
	}
}
