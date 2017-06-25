#pragma once
#include <map>

#include "Texture.h"

namespace Engine
{
	class TextureCache
	{
	public:
		Texture GetTexture(const char* texturePath);

	private:
		std::map<const char*, Texture> m_textureMap;
	};
}

