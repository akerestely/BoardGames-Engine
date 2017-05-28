#include "Logger.h"
#include "stdio.h"

#ifdef _WIN32
#include <windows.h>
#include <debugapi.h>
#endif

namespace Engine
{
	void log(const char * szFormat, ...)
	{
#ifdef _WIN32
		char szBuff[1024];
		va_list arg;
		va_start(arg, szFormat);
		_vsnprintf_s(szBuff, sizeof(szBuff), szFormat, arg);
		va_end(arg);
		auto size = strlen(szBuff);
		szBuff[size] = '\n';
		szBuff[size + 1] = '\0';

		OutputDebugStringA(szBuff);
#endif		
	}
}