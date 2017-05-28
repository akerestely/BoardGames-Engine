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
		case Key::R:					return SDLK_r;
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

		return 0;
	}

	Key SDLKeyToKey(uint keyId)
	{
		switch (keyId)
		{
		case SDLK_a:			return Key::A;
		case SDLK_d:			return Key::D;
		case SDLK_e:			return Key::E;
		case SDLK_q:			return Key::Q;
		case SDLK_s:			return Key::S;
		case SDLK_w:			return Key::W;
		case SDLK_r:			return Key::R;
		case SDLK_SPACE:		return Key::Space;
		case SDLK_ESCAPE:		return Key::Esc;
		case SDLK_F1:			return Key::F1;
		case SDLK_F4:			return Key::F4;
		case SDLK_KP_PLUS:		return Key::NumpadPlus;
		case SDLK_KP_MINUS:		return Key::NumpadMinus;
		case SDL_BUTTON_LEFT:	return Key::LeftMouseButton;
		case SDL_BUTTON_MIDDLE:	return Key::MiddleMouseButton;
		case SDL_BUTTON_RIGHT:	return Key::RightMouseButton;
		}

		return Key::None;
	}

	InputManager::InputManager(void) : mouseCoords(0), mouseCoordsRel(0)
	{
	}

	InputManager::~InputManager(void)
	{
	}

	void InputManager::Register(EventType eventType, TCallback callback)
	{
		registeredCallbacks[eventType].push_back(callback);
	}

	void InputManager::PressKey(uint keyID)
	{
		keyMap[keyID] = true;

		Key key = SDLKeyToKey(keyID);
		for (auto &callback : registeredCallbacks[EventType::ButtonDown])
			callback(&key);
	}

	void InputManager::ReleaseKey(uint keyID)
	{
		keyMap[keyID] = false;

		Key key = SDLKeyToKey(keyID);
		for (auto &callback : registeredCallbacks[EventType::ButtonUp])
			callback(&key);
	}

	bool InputManager::IsKeyDown(Key keyID)
	{
		auto it = keyMap.find(KeyToSDLKey(keyID));
		if (it != keyMap.end())
			return it->second;
		return false;
	}

	void InputManager::SetMouseCoords(int x, int y)
	{
		mouseCoords.x = x;
		mouseCoords.y = y;

		for (auto &callback : registeredCallbacks[EventType::MouseMotion])
			callback(&glm::ivec2(x,y));
	}

	void InputManager::SetMouseCoordsRel(int x, int y)
	{
		mouseCoordsRel.x = x;
		mouseCoordsRel.y = y;
	}
}
