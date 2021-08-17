#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include "Globals.h"

int main()
{


	engine->init();
	

	while (engine->getWindowHandle()->isOpen())
    {	
		engine->getGame()->Update();

		engine->getWindowHandle()->display();
    }
	
	

	system("pause");
	return 0;

}


