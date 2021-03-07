#include "UITextBox.h"

namespace VEngine
{
	UITextBox::UITextBox()
	{

	}

	UITextBox::~UITextBox()
	{

	}

	void UITextBox::update()
	{
		//sf::Vector2f Mpos = InputHandler::init().getMouseViewPos(Window::init().getWindow().getDefaultView());

	}

	sf::FloatRect UITextBox::getLocalBounds() const
	{
		return sf::FloatRect();
	}

	sf::FloatRect UITextBox::getGlobalBounds() const
	{
		return sf::FloatRect();
	}

	void UITextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{

	}
}