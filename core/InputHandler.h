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

		bool isKeyPressed(sf::Keyboard::Key key)const;
		bool isKeysDown(sf::Keyboard::Key key)const;
		bool isKeysRelease(sf::Keyboard::Key key)const;

		bool isMousePressed(sf::Mouse::Button button)const;
		bool isMouseDown(sf::Mouse::Button button)const;
		bool isMouseRelease(sf::Mouse::Button button)const;

		int getMouseWheel()const;
		const sf::Vector2i getMouseWindowPos()const;
		const sf::Vector2f getMouseViewPos()const;
		const sf::Vector2f getMouseViewPos(const sf::View& view)const;

	private:
		enum inputType
		{
			pressed = 0, released
		};

		std::list<std::pair<sf::Keyboard::Key, inputType>> keys;
		std::list<std::pair<sf::Mouse::Button, inputType>> mouseButtons;

		int mouseWheel;
		sf::RenderWindow* window;

		InputHandler();
		~InputHandler();
	};
}