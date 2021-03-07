#include "UICheckBox.h"

#include "Engine/core/Window.h"
#include "Engine/core/InputHandler.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	UICheckBox::UICheckBox()
	{
		
	}

	UICheckBox::~UICheckBox()
	{

	}

	void UICheckBox::update()
	{
		VE_PROFILE_FUNC;
		sf::Vector2f Mpos = InputHandler::init().getMouseViewPos(Window::init().getWindow().getDefaultView());
		sf::Vector2f pos = getPosition();
		sf::FloatRect bounds = sprite.getLocalBounds();

		if ((Mpos.x > pos.x && Mpos.x < pos.x + bounds.width) &&
			(Mpos.y > pos.y && Mpos.y < pos.y + bounds.height) &&
			InputHandler::init().isMousePressed(sf::Mouse::Left))
		{
			if (state == false)
			{
				sprite.setTexture(*boxChecked);
				state = true;
			}
			else
			{
				sprite.setTexture(*boxDefault);
				state = false;
			}
		}
	}

	void UICheckBox::setState(bool state)
	{
		if (this->state == state) return;

		if (state == false)
		{
			sprite.setTexture(*boxChecked);
			state = true;
		}
		else
		{
			sprite.setTexture(*boxDefault);
			state = false;
		}
	}

	bool UICheckBox::getState()const
	{
		return state;
	}

	void UICheckBox::setDefaultTexture(const sf::Texture* texture)
	{
		if (texture == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "checkBox defualt texture is nullptr", true);
			return;
		}

		boxDefault = texture;

		if (sprite.getTexture() == nullptr)
		{
			sprite.setTexture(*texture);
		}
	}

	void UICheckBox::setCheckedTexture(const sf::Texture* texture)
	{
		if (texture == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "checkBox checked texture is nullptr", true);
			return;
		}

		boxChecked = texture;
	}

	sf::FloatRect UICheckBox::getLocalBounds() const
	{
		return sprite.getLocalBounds();
	}

	sf::FloatRect UICheckBox::getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}

	void UICheckBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(sprite,states);
	}

}