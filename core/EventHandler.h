#pragma once

#include "SFML/Graphics.hpp"

namespace VEngine
{
	class EventHandler
	{
	public:
		static EventHandler& init() { static EventHandler instance; return instance; }

		void handleEvents();

	private:
		sf::RenderWindow* window;
		sf::Event event;
		std::vector<sf::Event> eventsForClient;

		EventHandler();
		~EventHandler();
	};

}


