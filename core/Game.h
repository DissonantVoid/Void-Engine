#pragma once

#include "Engine/Config.h"
#include "Engine/event/Event.h"

namespace VEngine
{
	class Game
	{
	public:
		Game(const sf::String& title, sf::VideoMode mode, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

		virtual ~Game() {}

		virtual void start() = 0;
		virtual void update() = 0;
		virtual void handleEvent(Event event) = 0;

	protected:


	};

}