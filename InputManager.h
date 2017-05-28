#pragma once
#include <map>
#include <unordered_map>
#include <functional>
#include <glm\glm.hpp>

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
		F4,

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

		glm::ivec2 GetMouseCoords() const { return mouseCoords; }
		glm::ivec2 GetMouseCoordsRel() const { return mouseCoordsRel; }

	private:
		std::unordered_map<uint, bool> keyMap;
		glm::ivec2 mouseCoords;
		glm::ivec2 mouseCoordsRel;

		std::map<EventType, std::vector<TCallback>> registeredCallbacks;
	};
}