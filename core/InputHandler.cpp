#include "InputHandler.h"

#include "Engine/core/Window.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	void InputHandler::reset()
	{
		VE_PROFILE_FUNC;
		keys.clear();
		mouseButtons.clear();
		mouseWheel = 0;
	}

	bool InputHandler::isKeyPressed(sf::Keyboard::Key key)
	{
		for (std::pair<sf::Keyboard::Key, inputType>& pair : keys)
		{
			if (pair.first == key && pair.second == inputType::pressed)
				return true;
		}
		return false;
	}

	bool InputHandler::isKeysDown(sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}

	bool InputHandler::isKeysRelease(sf::Keyboard::Key key)
	{
		for (std::pair<sf::Keyboard::Key, inputType>& pair : keys)
		{
			if (pair.first == key && pair.second == inputType::released)
				return true;
		}
		return false;
	}

	bool InputHandler::isMousePressed(sf::Mouse::Button button)
	{
		for (std::pair<sf::Mouse::Button, inputType>& pair : mouseButtons)
		{
			if (pair.first == button && pair.second == inputType::pressed)
				return true;
		}
		return false;
	}

	bool InputHandler::isMouseDown(sf::Mouse::Button button)
	{
		return sf::Mouse::isButtonPressed(button);
	}

	bool InputHandler::isMouseRelease(sf::Mouse::Button button)
	{
		for (std::pair<sf::Mouse::Button, inputType>& pair : mouseButtons)
		{
			if (pair.first == button && pair.second == inputType::released)
				return true;
		}
		return false;
	}

	int8_t InputHandler::getMouseWheel()
	{
		return mouseWheel;
	}

	sf::Vector2i InputHandler::getMouseWindowPos()
	{
		return sf::Mouse::getPosition(*window);
	}

	sf::Vector2f InputHandler::getMouseViewPos(sf::View& view)
	{
		return window->mapPixelToCoords((getMouseWindowPos()),view);
	}

	//private

	InputHandler::InputHandler()
	{
		window = &Window::init().getWindow();
	}

	InputHandler::~InputHandler()
	{

	}
}