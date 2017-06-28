#pragma once
#include <map>
#include <unordered_map>
#include <functional>

#include "glm.hpp"

namespace Engine
{
	enum class Key
	{
		None,
		A,
		D,
		E,
		Q,
		S,
		W,
		R,

		Space,
		Esc,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,

		NumpadPlus,
		NumpadMinus,

		LeftMouseButton,
		MiddleMouseButton,
		RightMouseButton,
	};

	enum class EventType
	{
		ButtonDown,
		ButtonUp,
		MouseMotion
	};

	class InputManager
	{
	public:
		using TCallback = std::function<void(void*)>;

	public:
		InputManager(void);
		~InputManager(void);

		void Register(EventType eventType, TCallback callback);

		void PressKey(uint keyID);
		void ReleaseKey(uint keyID);

		bool IsKeyDown(Key keyID);

		void SetMouseCoords(int x, int y);
		void SetMouseCoordsRel(int x, int y);

		glm::ivec2 GetMouseCoords() const { return m_mouseCoords; }
		glm::ivec2 GetMouseCoordsRel() const { return m_mouseCoordsRel; }

	private:
		std::unordered_map<uint, bool> m_keyMap;
		glm::ivec2 m_mouseCoords;
		glm::ivec2 m_mouseCoordsRel;

		std::map<EventType, std::vector<TCallback>> m_registeredCallbacks;
	};
}