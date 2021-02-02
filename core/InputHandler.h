#pragma once

#include <list>
#include "Engine/core/EventHandler.h"

namespace VEngine
{
	class InputHandler
	{
		friend class EventHandler;
	public:
		static InputHandler& init() { static InputHandler instance; return instance;};

		void reset();

		bool isKeyPressed(sf::Keyboard::Key key);
		bool isKeysDown(sf::Keyboard::Key key);
		bool isKeysRelease(sf::Keyboard::Key key);

		bool isMousePressed(sf::Mouse::Button button);
		bool isMouseDown(sf::Mouse::Button button);
		bool isMouseRelease(sf::Mouse::Button button);

		int8_t getMouseWheel();
		sf::Vector2i getMouseWindowPos();
		sf::Vector2f getMouseViewPos(sf::View& view);

	private:
		enum inputType
		{
			pressed = 0, released
		};

		std::list<std::pair<sf::Keyboard::Key, inputType>> keys;
		std::list<std::pair<sf::Mouse::Button, inputType>> mouseButtons;

		int8_t mouseWheel = 0;
		sf::RenderWindow* window;

		InputHandler();
		~InputHandler();
	};
}