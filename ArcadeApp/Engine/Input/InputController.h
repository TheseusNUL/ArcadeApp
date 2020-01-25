#pragma once

#include "Input.h"

class GameController;

class InputController
{
public:
	InputController() : m_quit(nullptr), m_pActiveController(nullptr) {}

	void Init(InputAction quitAction);
	void Update(uint32_t deltaTime);
	
	inline void SetGameController(GameController* controller) { m_pActiveController = controller; }

private:
	InputAction m_quit;

	GameController* m_pActiveController;
};