#pragma once

#include <vector>

#include "Input.h"

class GameController
{
public:
	GameController() : m_mouseMovedAction(nullptr) {}

	InputAction GetActionForKey(InputKey key);

	void AddInputActionForKey(const ButtonAction& buttonAction);
	void ClearAll();

	/*-----------------------------------------------
	Helper Functions -  wrapper around SDL functions
	------------------------------------------------*/

	static bool isPressed(InputState state);
	static bool isReleased(InputState state);

	static InputKey ActionKey();
	static InputKey CancelKey();
	static InputKey UpKey();
	static InputKey DownKey();
	static InputKey LeftKey();
	static InputKey RightKey();

	/*--------------------
		Mouse Input 
	---------------------*/

	inline const MouseMovedAction& GetMouseMovedAction() { return m_mouseMovedAction; }
	inline void SetMouseMovedAction(const MouseMovedAction& action) { m_mouseMovedAction = action; }

	MouseInputAction GetActionForMouseButton(const MouseButton button);
	void AddMouseButtonAction(const MouseButtonAction& action);

	static MouseButton LeftMouseButton();
	static MouseButton RightMouseButton();

private:
	std::vector<ButtonAction> m_buttonActions;
	std::vector<MouseButtonAction> m_mouseButtonActions;

	MouseMovedAction m_mouseMovedAction;
};