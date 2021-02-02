#include "Game.h"

#include "Engine/core/Window.h"
#include "Engine.h"


namespace VEngine
{
	Game::Game(const sf::String& title, sf::VideoMode mode, sf::Uint32 style, const sf::ContextSettings& settings)
	{
		Window::init().getWindow().create(mode, title, style, settings);
	}

	//private
}