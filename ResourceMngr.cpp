#include "BaseTypes.h"
#include "ResourceMngr.h"

namespace Engine
{
	TextureCache ResourceMngr::m_textureCache;

	Engine::Texture ResourceMngr::GetTexture(const char* texturePath)
	{
		return m_textureCache.GetTexture(texturePath);
	}
}