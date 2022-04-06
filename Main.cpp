#include "Display.hpp"

int main()
{
	Display display;

	{
		while (display.window->isOpen())
		{
			display.graphics();
		}
	}

	return 0;
}
