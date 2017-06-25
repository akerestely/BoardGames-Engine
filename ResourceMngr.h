#pragma once
#include "TextureCache.h"

namespace Engine
{
	class ResourceMngr
	{
	public:
		static Texture GetTexture(const char* texturePath);

	private:
		static TextureCache m_textureCache;
	};
}

