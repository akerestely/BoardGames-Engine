#pragma once

#include <vector>
#include <cstdint>

namespace Engine
{
	class IOManager
	{
	public:
		static bool ReadFileToBuffer(const char* filepath, std::vector<uint8_t>& buffer);
	};
}

