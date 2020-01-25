#include "ArcadeState.h"

#include "../../Engine/Graphics/Screen.h"

#include "../../Engine/Input/GameController.h"

#include "../../Engine/Shapes/Line.h"
#include "../../Engine/Shapes/Triangle.h"
#include "../../Engine/Shapes/AARect.h"
#include "../../Engine/Shapes/Circle.h"

AracadeState::AracadeState()
{

}

void AracadeState::Init()
{
	//Test code for input

	ButtonAction action;
	action.key = GameController::ActionKey();
	action.action = [](uint32_t deltaTime, InputState state)
	{
		if(GameController::isPressed(state))
		std::cout << "Action Button Pressed" << std::endl;
	};

	m_gameController.AddInputActionForKey(action);

	MouseButtonAction mouseAction;
	mouseAction.mouseButton = GameController::LeftMouseButton();
	mouseAction.mouseInputAction = [](InputState state, const MousePosition& position)
	{
		if (GameController::isPressed(state))
		{
			std::cout << "Left Mouse button pressed!" << std::endl;
		}
	};

	m_gameController.AddMouseButtonAction(mouseAction);

	m_gameController.SetMouseMovedAction([](const MousePosition& mousePosition)
	{
		std::cout << "Mouse position x: " << mousePosition.x << ", y: " << mousePosition.y << std::endl;
	});
}

void AracadeState::Update(uint32_t deltaTime)
{

}

void AracadeState::Draw(Screen& screen)
{
	Line line = { Vector2(0,0), Vector2(screen.GetWidth(), screen.GetHeight()) };
	Triangle tri(Vector2(60, 10), Vector2(10, 110), Vector2(110, 110));
	AARect rect(Vector2(screen.GetWidth() / 2 + -25, screen.GetWidth() / 2 - 26), 50, 50);
	Circle circle(Vector2(screen.GetWidth() / 2 + 50, screen.GetHeight() / 2 + 50), 50);

	screen.Draw(tri, Colour(40, 100, 180, 255), true, Colour::White());
	screen.Draw(rect, Colour(0, 255, 0, 255), true, Colour(0, 255, 0, 128));
	screen.Draw(circle, Colour(0, 0, 255, 128), true, Colour(0, 0, 255, 128));
}

const std::string& AracadeState::GetStateName() const
{
	static std::string stateName = "Arcade";
	return stateName;
}

std::unique_ptr<State> AracadeState::GetState(E_APP_GAMES game)
{
	switch (game)
	{
	case E_BREAKOUT:
		break;
	default:
		break;
	}

	return nullptr;
}
