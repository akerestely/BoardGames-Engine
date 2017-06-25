#pragma once

namespace Engine
{
	template<class Type>
	struct Size
	{
		Type width;
		Type height;
	};
}

using sizei = Engine::Size<int>;
using sizef = Engine::Size<float>;