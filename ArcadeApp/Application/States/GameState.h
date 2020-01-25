#pragma once

#include <memory>

#include "State.h"

#include "../Games/IGame.h"

class GameState : public State
{
public:
	GameState(std::unique_ptr<IGame> pGame) : m_game(std::move(pGame)) {}
	virtual ~GameState() {}

	virtual void Init() override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& screen) override;

	virtual const std::string& GetStateName() const override;

private:
	std::unique_ptr<IGame> m_game;
};
