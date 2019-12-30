#pragma once
#include "Position.h"

#include <cstdint>

namespace Engine
{
	struct ColorRGBA8
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
		ColorRGBA8(uint8_t r=255, uint8_t g=255, uint8_t b=255, uint8_t a=255) :r(r), g(g), b(b), a(a)
		{
		}
	};

	struct UV
	{
		float u;
		float v;
	};

	struct Vertex
	{
		posf position;
		ColorRGBA8 color;
		UV uv;

		void SetPosition(float x, float y)
		{
			position.x=x;
			position.y=y;
		}

		void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void SetUV(float u, float v)
		{
			uv.u=u;
			uv.v=v;
		}
	};
}