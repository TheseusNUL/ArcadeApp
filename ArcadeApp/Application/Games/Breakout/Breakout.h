#pragma once

#include "../IGame.h"

class Breakout : public IGame
{
public:
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t deltaTime) override;
	virtual void Draw(Screen& screen) override;

	virtual std::string GetName() const override;
};
