#pragma once

namespace Engine
{
	template<class Type>
	struct Position
	{
		Type x;
		Type y;
	};
}

using posi = Engine::Position<int>;
using posf = Engine::Position<float>;