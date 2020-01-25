#include <iostream>

#include "Application.h"

#include "States/ArcadeState.h"
#include "States/GameState.h"

#include "Games/Breakout/Breakout.h"

Application& Application::Singleton()
{
	static Application app;
	return app;
}

bool Application::Init(uint32_t width, uint32_t height, uint32_t magnification)
{
	m_pWindow = m_screen.Init(width, height, magnification);

	std::unique_ptr<AracadeState> arcadeState = std::make_unique<AracadeState>();
	PushState(std::move(arcadeState));

	/*----------------------------------------------------------------------------------------------
		Testing code
	----------------------------------------------------------------------------------------------*/

	std::unique_ptr<Breakout> breakout = std::make_unique<Breakout>();
	std::unique_ptr<GameState> breakoutState = std::make_unique<GameState>(std::move(breakout));

	PushState(std::move(breakoutState));
	/*--------------------------------------------------------------------------------------------*/

	return m_pWindow;
}

void Application::Run()
{
	if (m_pWindow)
	{
		bool bRunning = true;

		uint32_t lastTick = SDL_GetTicks(); //number of ticks since SDL initialise.
		uint32_t currentTick = lastTick;

		uint32_t deltaTime = 10; //stable delta time
		uint32_t accumulator = 0;

		m_inputController.Init([&bRunning](uint32_t deltaTime, InputState state)
		{
			bRunning = false;
		});

		while (bRunning)
		{

			/*-------------------
			stable frame rate
			--------------------*/

			currentTick = SDL_GetTicks();
			uint32_t frameTime = currentTick - lastTick; //how many ticks have happened since last frame

			if (frameTime > 300)
				frameTime = 300;

			lastTick = currentTick;
			accumulator += frameTime; //accumulator = total ticks

			m_inputController.Update(deltaTime);

			State* topState = Application::TopState();

			if (topState)
			{
				//Update current scene by delta time
				while (accumulator >= deltaTime)
				{
					topState->Update(deltaTime);
					accumulator -= deltaTime;
				}

				//Render
				topState->Draw(m_screen);
			}

			m_screen.SwapBuffers();
		}
	}

}

void Application::PushState(std::unique_ptr<State> state)
{
	if (state)
	{
		state->Init();

		m_inputController.SetGameController(state->GetGameController());

		m_stack.emplace_back(std::move(state));

		SDL_SetWindowTitle(m_pWindow, TopState()->GetStateName().c_str()); //SDL doesn't deal with strings
	}
}

void Application::PopState()
{
	if (m_stack.size() > 1)
		m_stack.pop_back();

	if (TopState())
	{
		m_inputController.SetGameController(TopState()->GetGameController());
		SDL_SetWindowTitle(m_pWindow, TopState()->GetStateName().c_str());
	}
}

State* Application::TopState()
{
	if (m_stack.empty())
		return nullptr;

	return m_stack.back().get();
}
