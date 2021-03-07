#include "Window.h"

namespace VEngine
{
	sf::RenderWindow& Window::getWindow()
	{
		return window;
	}

	void Window::setFullScreen(bool fullScreen) //TODO: sfml doesn't provide a way to check if window is fullScreen so we can add a "fullscreen" variable which require a costum create() function
	{
		
	}

	//private

	Window::Window()
	{

	}

	Window::~Window()
	{

	}
}