#include "GameState.h"

void GameState::Init()
{
	m_game->Init(m_gameController);
}

void GameState::Update(uint32_t deltaTime)
{
	m_game->Update(deltaTime);
}

void GameState::Draw(Screen& screen)
{
	m_game->Draw(screen);
}

const std::string& GameState::GetStateName() const
{
	static std::string name = "";
	return name;
}
