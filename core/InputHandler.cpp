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

	bool InputHandler::isKeyPressed(sf::Keyboard::Key key) const
	{
		for (const std::pair<sf::Keyboard::Key, inputType>& pair : keys)
		{
			if (pair.first == key && pair.second == inputType::pressed)
				return true;
		}
		return false;
	}

	bool InputHandler::isKeysDown(sf::Keyboard::Key key) const
	{
		return sf::Keyboard::isKeyPressed(key);
	}

	bool InputHandler::isKeysRelease(sf::Keyboard::Key key) const
	{
		for (const std::pair<sf::Keyboard::Key, inputType>& pair : keys)
		{
			if (pair.first == key && pair.second == inputType::released)
				return true;
		}
		return false;
	}

	bool InputHandler::isMousePressed(sf::Mouse::Button button) const
	{
		for (const std::pair<sf::Mouse::Button, inputType>& pair : mouseButtons)
		{
			if (pair.first == button && pair.second == inputType::pressed)
				return true;
		}
		return false;
	}

	bool InputHandler::isMouseDown(sf::Mouse::Button button) const
	{
		return sf::Mouse::isButtonPressed(button);
	}

	bool InputHandler::isMouseRelease(sf::Mouse::Button button) const
	{
		for (const std::pair<sf::Mouse::Button, inputType>& pair : mouseButtons)
		{
			if (pair.first == button && pair.second == inputType::released)
				return true;
		}
		return false;
	}

	int InputHandler::getMouseWheel() const
	{
		return mouseWheel;
	}

	const sf::Vector2i InputHandler::getMouseWindowPos() const
	{
		return sf::Mouse::getPosition(*window);
	}

	const sf::Vector2f InputHandler::getMouseViewPos() const
	{
		return window->mapPixelToCoords((getMouseWindowPos()), window->getView());
	}

	const sf::Vector2f InputHandler::getMouseViewPos(const sf::View& view) const
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