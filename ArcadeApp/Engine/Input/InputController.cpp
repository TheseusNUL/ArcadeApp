#include <SDL.h>

#include "InputController.h"
#include "GameController.h"

void InputController::Init(InputAction quitAction)
{
	m_quit = quitAction;
}

void InputController::Update(uint32_t deltaTime)
{
	SDL_Event event;

	//Input
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{

		case SDL_QUIT:	m_quit(deltaTime, SDL_PRESSED);
			break;

		case SDL_MOUSEMOTION:
			if (m_pActiveController)
			{
				MouseMovedAction mouseMoved;
				if (mouseMoved = m_pActiveController->GetMouseMovedAction())
				{
					//Get mouse position
					MousePosition position;
					position.x = event.motion.x;
					position.y = event.motion.y;
					mouseMoved(position);
				}

			}
			break;
			
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEBUTTONDOWN:
			if (m_pActiveController)
			{
				MouseInputAction action = m_pActiveController->GetActionForMouseButton(static_cast<MouseButton>(event.button.button));

				//Get mouse position when key was pressed
				MousePosition position;
				position.x = event.motion.x;
				position.y = event.motion.y;

				action(static_cast<InputState>(event.button.state), position);
			}

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			if (m_pActiveController)
			{
				InputAction action = m_pActiveController->GetActionForKey(event.key.keysym.sym); //get action
				action(deltaTime, static_cast<InputState>(event.key.state)); //call action
			}
			break;
		}
	}
}
