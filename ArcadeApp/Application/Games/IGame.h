#pragma once

#include <string>
#include <stdint.h>

class GameController;
class Screen;

class IGame
{
public:
	~IGame();

	virtual void Init(GameController& controller) = 0;
	virtual void Update(uint32_t deltaTime) = 0;
	virtual void Draw(Screen& screen) = 0;

	virtual std::string GetName() const = 0;
};
