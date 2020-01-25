#pragma once

#include <memory>

#include "State.h"

class Screen;

enum E_APP_GAMES
{
	E_BREAKOUT,
	E_MAX_NUM_GAMES
};

class AracadeState : public State
{
public:
	AracadeState();


	virtual void Init() override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& screen) override;

	virtual const std::string& GetStateName() const override;

private:
	std::unique_ptr<State> GetState(E_APP_GAMES game);
};