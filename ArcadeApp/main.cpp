#include <iostream>

#include "Application/Application.h"

const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int MAGNIFICATION = 3; //allows for window size increase with same pixel resolution

int main(int argc, char *argv[])
{
	if (Application::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION))
		Application::Singleton().Run();

	return 0;
}