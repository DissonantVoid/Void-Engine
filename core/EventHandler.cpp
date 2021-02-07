#include "EventHandler.h"

#include "Engine/core/InputHandler.h"
#include "Engine/core/Window.h"
#include "Engine/event/EventQueue.h"

#include "Engine/debug/ProfilerSample.h"
#include "Engine/debug/Logger.h"

namespace VEngine
{
	void EventHandler::handleEvents()
	{
		VE_PROFILE_FUNC;

		while (window->pollEvent(event)) //a copy of the event is stored in a vector, when all events are prosseced we send all the copies at once to the event queue so the client can access them as well
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				{
					Event e(Event::EventType::EngineQuit);
					e.submite();
				}
				break;
			case sf::Event::KeyPressed:

				for (int i = 0; i < sf::Keyboard::KeyCount; i++)
					if (event.key.code == i)
					{
						InputHandler::init().keys.push_back(std::make_pair(static_cast<sf::Keyboard::Key>(i), InputHandler::inputType::pressed));
						break;
					}
				break;
			case sf::Event::KeyReleased:

				for (int i = 0; i < sf::Keyboard::KeyCount; i++)
					if (event.key.code == i)
					{
						InputHandler::init().keys.push_back(std::make_pair(static_cast<sf::Keyboard::Key>(i), InputHandler::inputType::released));
						break;
					}
				break;
			case sf::Event::MouseButtonPressed:

				for (int i = 0; i < sf::Mouse::ButtonCount; i++)
					if (event.mouseButton.button == i)
					{
						InputHandler::init().mouseButtons.push_back(std::make_pair(static_cast<sf::Mouse::Button>(i), InputHandler::inputType::pressed));
						break;
					}
				break;
			case sf::Event::MouseButtonReleased:

				for (int i = 0; i < sf::Mouse::ButtonCount; i++)
					if (event.mouseButton.button == i)
					{
						InputHandler::init().mouseButtons.push_back(std::make_pair(static_cast<sf::Mouse::Button>(i), InputHandler::inputType::released));
						break;
					}
				break;
			case sf::Event::MouseWheelScrolled:

				InputHandler::init().mouseWheel = event.mouseWheel.delta;
				break;
			}
			eventsForClient.push_back(event);
		}

		//here events are sent to the client to handle
		for (sf::Event& e : eventsForClient)
		{
			Event event(Event::EventType::SFML);
			event.sfmlEvent.sfEvent = e;
			event.submite();
		}
		eventsForClient.clear();
	}

	//private

	EventHandler::EventHandler()
	{
		window = &Window::init().getWindow();
	}

	EventHandler::~EventHandler()
	{

	}
}