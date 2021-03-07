#include "UIValuePicker.h"

#include "Engine/core/InputHandler.h"

namespace VEngine
{
	UIValuePicker::UIValuePicker()
	{

	}

	UIValuePicker::~UIValuePicker()
	{

	}

	void UIValuePicker::update()
	{
		sf::Vector2i Mpos = InputHandler::init().getMouseWindowPos();
	}

	sf::FloatRect UIValuePicker::getLocalBounds() const
	{
		return sf::FloatRect();
	}

	sf::FloatRect UIValuePicker::getGlobalBounds() const
	{
		return sf::FloatRect();
	}

	void UIValuePicker::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{

	}
}

