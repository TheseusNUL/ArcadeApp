#pragma once

#include <functional>
#include <stdint.h>

/* Create typedefs for input types*/

using InputKey = uint8_t;
using InputState = uint8_t;

using InputAction = std::function<void(uint32_t deltaTime, InputState state)>;

struct ButtonAction
{
	InputKey key;
	InputAction action;
};

/*--------------------------------
	Mouse Input
---------------------------------*/

using MouseButton = uint8_t;

struct MousePosition
{
	int32_t x, y;
};

using MouseInputAction = std::function<void(InputState state, const MousePosition& position)>;
using MouseMovedAction = std::function<void(const MousePosition& mousePosition)>;

struct MouseButtonAction
{
	MouseButton mouseButton;
	MouseInputAction mouseInputAction;
};
