#pragma once
#include <unordered_map>
#include <glm\glm.hpp>
namespace Engine
{
	struct ButtonState
	{
		bool pressed;
		bool usedOnce;
		ButtonState() : pressed(false), usedOnce(false) {}
	};

	enum class Key
	{
		A,
		D,
		E,
		Q,
		S,
		W,

		Space,
		Esc,
		F1,
		F4,

		NumpadPlus,
		NumpadMinus,

		LeftMouseButton,
		MiddleMouseButton,
		RightMouseButton
	};

	class InputManager
	{
	public:
		InputManager(void);
		~InputManager(void);

		void PressKey(uint keyID);
		void ReleaseKey(uint keyID);

		bool IsKeyDown(Key keyID);
		bool IsKeyDownOnce(Key keyID);

		void SetMouseCoords(int x, int y);
		void SetMouseCoordsRel(int x, int y);

		glm::ivec2 GetMouseCoords() const { return mouseCoords; }
		glm::ivec2 GetMouseCoordsRel() const { return mouseCoordsRel; }

	private:
		std::unordered_map<uint, ButtonState> keyMap;
		glm::ivec2 mouseCoords;
		glm::ivec2 mouseCoordsRel;
	};
}