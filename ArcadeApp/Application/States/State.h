#pragma once

#include <string>
#include <stdint.h>

#include "../../Engine/Input/GameController.h"

class Screen;

class State
{
public:
	virtual ~State() {}

	virtual void Init() = 0;
	virtual void Update(uint32_t deltaTime) = 0;
	virtual void Draw(Screen& screen) = 0;

	virtual const std::string& GetStateName() const = 0;

	inline GameController* GetGameController() { return &m_gameController; }

protected:
	GameController m_gameController;
};