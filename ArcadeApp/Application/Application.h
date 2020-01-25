#pragma once
#include <memory>

#include "States/State.h"

#include "../Engine/Graphics/Screen.h"

#include "../Engine/Input/InputController.h"

struct SDL_Window;

class Application
{
public:
	static Application& Singleton();
	bool Init(uint32_t width, uint32_t height, uint32_t magnification);
	void Run();

	inline uint32_t GetWidth() const { return m_screen.GetWidth(); }
	inline uint32_t GetHeight() const { return m_screen.GetHeight(); }

	void PushState(std::unique_ptr<State> state);
	void PopState();

	State* TopState();

private:
	Screen m_screen;
	SDL_Window* m_pWindow;

	std::vector<std::unique_ptr<State>> m_stack;

	InputController m_inputController;
};