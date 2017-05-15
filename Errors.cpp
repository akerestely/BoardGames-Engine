#include "Errors.h"
#include <sdl/SDL.h>

#ifdef _WIN32
#include <windows.h>
#include <debugapi.h>
#endif

namespace Engine
{
	void logi(const char* szFormat, ...)
	{
#ifdef _WIN32
		char szBuff[1024];
		va_list arg;
		va_start(arg, szFormat);
		_vsnprintf(szBuff, sizeof(szBuff), szFormat, arg);
		va_end(arg);
		auto size = strlen(szBuff);
		szBuff[size] = '\n';
		szBuff[size + 1] = '\0';

		OutputDebugStringA(szBuff);
#endif		
	}

	extern void fatalError(const std::string &msg)
	{
		printf("%s\n", msg.c_str());
		logi("%s\n", msg.c_str());
		system("pause");
		SDL_Quit();
		exit(1);
	}
}
