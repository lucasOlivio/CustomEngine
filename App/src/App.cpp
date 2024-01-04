#include "Core/AppEngine.h"

int main()
{
	using namespace MyEngine;

	Application app = Application();

	app.Init();

	app.Run();
}