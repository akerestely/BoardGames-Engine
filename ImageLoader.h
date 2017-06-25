#pragma once

#include "Texture.h"

namespace Engine
{
	class ImageLoader
	{
	public:
		static Texture LoadPNG(const char* filepPath);
	};
}

