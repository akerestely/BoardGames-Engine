#include "BaseTypes.h"
#include "TextureCache.h"

#include <iostream>

#include "ImageLoader.h"

namespace Engine
{
	Engine::Texture TextureCache::GetTexture(const char* texturePath)
	{
		//lookup for texture and see if its there
		auto mit = m_textureMap.find(texturePath);

		//check if its not in the map
		if(mit == m_textureMap.end())
		{
			//load the texture
			Texture newTexture = ImageLoader::LoadPNG(texturePath);

			//insert it into the map
			mit = m_textureMap.insert(std::make_pair(texturePath, newTexture)).first;
		}

		return mit->second;
	}
}
