#include "InputManager.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"

namespace Engine
{
	uint32_t KeyToSDLKey(Key keyId)
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
		case Key::F2:					return SDLK_F2;
		case Key::F3:					return SDLK_F3;
		case Key::F4:					return SDLK_F4;
		case Key::F5:					return SDLK_F5;
		case Key::F6:					return SDLK_F6;
		case Key::F7:					return SDLK_F7;
		case Key::F8:					return SDLK_F8;
		case Key::NumpadPlus:			return SDLK_KP_PLUS;
		case Key::NumpadMinus:			return SDLK_KP_MINUS;
		case Key::LeftMouseButton:		return SDL_BUTTON_LEFT;
		case Key::MiddleMouseButton:	return SDL_BUTTON_MIDDLE;
		case Key::RightMouseButton:		return SDL_BUTTON_RIGHT;
		}

		return 0;
	}

	Key SDLKeyToKey(uint32_t keyId)
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
		case SDLK_F2:			return Key::F2;
		case SDLK_F3:			return Key::F3;
		case SDLK_F4:			return Key::F4;
		case SDLK_F5:			return Key::F5;
		case SDLK_F6:			return Key::F6;
		case SDLK_F7:			return Key::F7;
		case SDLK_F8:			return Key::F8;
		case SDLK_KP_PLUS:		return Key::NumpadPlus;
		case SDLK_KP_MINUS:		return Key::NumpadMinus;
		case SDL_BUTTON_LEFT:	return Key::LeftMouseButton;
		case SDL_BUTTON_MIDDLE:	return Key::MiddleMouseButton;
		case SDL_BUTTON_RIGHT:	return Key::RightMouseButton;
		}

		return Key::None;
	}

	InputManager::InputManager(void) : m_mouseCoords(0), m_mouseCoordsRel(0)
	{
	}

	InputManager::~InputManager(void)
	{
	}

	void InputManager::Register(EventType eventType, TCallback callback)
	{
		m_registeredCallbacks[eventType].push_back(callback);
	}

	void InputManager::PressKey(uint32_t keyID)
	{
		m_keyMap[keyID] = true;

		Key key = SDLKeyToKey(keyID);
		for (auto &callback : m_registeredCallbacks[EventType::ButtonDown])
			callback(&key);
	}

	void InputManager::ReleaseKey(uint32_t keyID)
	{
		m_keyMap[keyID] = false;

		Key key = SDLKeyToKey(keyID);
		for (auto &callback : m_registeredCallbacks[EventType::ButtonUp])
			callback(&key);
	}

	bool InputManager::IsKeyDown(Key keyID)
	{
		auto it = m_keyMap.find(KeyToSDLKey(keyID));
		if (it != m_keyMap.end())
			return it->second;
		return false;
	}

	void InputManager::SetMouseCoords(int x, int y)
	{
		m_mouseCoords.x = x;
		m_mouseCoords.y = y;

		for (auto &callback : m_registeredCallbacks[EventType::MouseMotion])
			callback(&glm::ivec2(x,y));
	}

	void InputManager::SetMouseCoordsRel(int x, int y)
	{
		m_mouseCoordsRel.x = x;
		m_mouseCoordsRel.y = y;
	}
}
