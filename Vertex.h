#pragma once
#include "BaseTypes.h"
#include "Position.h"

namespace Engine
{
	struct ColorRGBA8
	{
		byte r;
		byte g;
		byte b;
		byte a;
		ColorRGBA8(byte r=255, byte b=255, byte g=255, byte a=255) :r(r), g(g), b(b), a(a)
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

		void SetColor(byte r, byte g, byte b, byte a)
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