#include "BaseTypes.h"
#include "InputManager.h"
#include "SDl\SDL_keycode.h"
#include "SDl\SDL_mouse.h"

namespace Engine
{
	uint KeyToSDLKey(Key keyId)
	{
		switch (keyId)
		{
		case Key::A:					return SDLK_a;
		case Key::D:					return SDLK_d;
		case Key::E:					return SDLK_e;
		case Key::Q:					return SDLK_q;
		case Key::S:					return SDLK_s;
		case Key::W:					return SDLK_w;
		case Key::Space:				return SDLK_SPACE;
		case Key::Esc:					return SDLK_ESCAPE;
		case Key::F1:					return SDLK_F1;
		case Key::F4:					return SDLK_F4;
		case Key::NumpadPlus:			return SDLK_KP_PLUS;
		case Key::NumpadMinus:			return SDLK_KP_MINUS;
		case Key::LeftMouseButton:		return SDL_BUTTON_LEFT;
		case Key::MiddleMouseButton:	return SDL_BUTTON_MIDDLE;
		case Key::RightMouseButton:		return SDL_BUTTON_RIGHT;
		}
	}

	InputManager::InputManager(void) : mouseCoords(0), mouseCoordsRel(0)
	{
	}

	InputManager::~InputManager(void)
	{
	}

	void InputManager::PressKey(uint keyID)
	{
		keyMap[keyID].pressed = true;
	}

	void InputManager::ReleaseKey(uint keyID)
	{
		keyMap[keyID].pressed = false;
		keyMap[keyID].usedOnce = false;
	}

	bool InputManager::IsKeyDown(Key keyID)
	{
		auto it = keyMap.find(KeyToSDLKey(keyID));
		if (it != keyMap.end())
			return it->second.pressed;
		return false;
	}

	bool InputManager::IsKeyDownOnce(Key keyID)
	{
		auto it = keyMap.find(KeyToSDLKey(keyID));
		if (it != keyMap.end())
			if (it->second.pressed && !it->second.usedOnce)
			{
				it->second.usedOnce = true;
				return true;
			}
		return false;
	}

	void InputManager::SetMouseCoords(int x, int y)
	{
		mouseCoords.x = x;
		mouseCoords.y = y;
	}

	void InputManager::SetMouseCoordsRel(int x, int y)
	{
		mouseCoordsRel.x = x;
		mouseCoordsRel.y = y;
	}
}
