#pragma once

#include <vector>

namespace Engine
{
	class IOManager
	{
	public:
		static bool ReadFileToBuffer(const char* filepath, std::vector<byte>& buffer);
	};
}

