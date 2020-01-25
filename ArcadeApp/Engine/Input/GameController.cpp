#include <SDL.h>

#include "GameController.h"

InputAction GameController::GetActionForKey(InputKey key)
{
	for (const auto& buttonAction : m_buttonActions)
	{
		if (key == buttonAction.key)
			return buttonAction.action;
	}

	return [](uint32_t, InputState) {}; //return empty action
}

void GameController::AddInputActionForKey(const ButtonAction& buttonAction)
{
	m_buttonActions.push_back(buttonAction);
}

void GameController::ClearAll()
{
	m_buttonActions.clear();
}

bool GameController::isPressed(InputState state)
{
	return state == SDL_PRESSED;
}

bool GameController::isReleased(InputState state)
{
	return state == SDL_RELEASED;
}

InputKey GameController::ActionKey()
{
	return static_cast<InputKey>(SDLK_SPACE);
}

InputKey GameController::CancelKey()
{
	return static_cast<InputKey>(SDLK_ESCAPE);
}

InputKey GameController::UpKey()
{
	return static_cast<InputKey>(SDLK_w);
}

InputKey GameController::DownKey()
{
	return static_cast<InputKey>(SDLK_s);
}

InputKey GameController::LeftKey()
{
	return static_cast<InputKey>(SDLK_a);
}

InputKey GameController::RightKey()
{
	return static_cast<InputKey>(SDLK_d);
}

MouseInputAction GameController::GetActionForMouseButton(const MouseButton button)
{
	for (const auto& buttonAction : m_mouseButtonActions)
	{
		if (button == buttonAction.mouseButton)
		{
			return buttonAction.mouseInputAction;
		}
	}

	return [](InputState state, const MousePosition& position) {};
}

void GameController::AddMouseButtonAction(const MouseButtonAction& action)
{
	m_mouseButtonActions.push_back(action);
}

MouseButton GameController::LeftMouseButton()
{
	return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}

MouseButton GameController::RightMouseButton()
{
	return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}
