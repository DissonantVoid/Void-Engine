#include "UI.h"

#include "Engine/core/Window.h"

namespace VEngine
{
	UI::UI()
		: window(Window::init().getWindow())
	{

	}

	UI::~UI()
	{

	}

	sf::FloatRect UI::getLocalBounds() const
	{
		return sf::FloatRect();
	}

	sf::FloatRect UI::getGlobalBounds() const
	{
		return sf::FloatRect();
	}

	//private
}