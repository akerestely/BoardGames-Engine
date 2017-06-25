#pragma once

#include "Texture.h"
#include "ResourceMngr.h"
#include "Rectangle.h"

namespace Engine
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();

		void Init(float x, float y, float width, float height, const char* texturePath);
		void Draw();

	private:
		uint m_vboId;
		rectf m_bounds;
		Texture m_texture;
	};
}

