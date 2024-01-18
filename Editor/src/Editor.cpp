#include "Core/EditorEngine.h"

int main()
{
	using namespace MyEngine;

	Editor editor = Editor();

	// TODO: This would be better comming from command args?
	const std::string INITIAL_SCENE = "scene01.json";
	editor.Init(INITIAL_SCENE);

	editor.Run();
}