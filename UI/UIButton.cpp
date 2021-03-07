#include "UIButton.h"

#include "Engine/core/InputHandler.h"

#include "Engine/debug/ProfilerSample.h"
#include "Engine/debug/Logger.h"
#include "Engine/core/Window.h"

namespace VEngine
{
	UIButton::UIButton()
	{
		
	}

	UIButton::~UIButton()
	{

	}

	void UIButton::setTextures(const sf::Texture* defaultTexture, const sf::Texture* pressedTexture, const sf::Texture* holdTexture, const sf::Texture* hoveredTexture)
	{
		VE_PROFILE_FUNC;
		setDefaultTexture(defaultTexture);
		setPressedTexture(pressedTexture);
		setHoldTexture(holdTexture);
		setHoveredTexture(hoveredTexture);
	}
	
	void UIButton::setDefaultTexture(const sf::Texture* defaultTexture)
	{
		if (defaultTexture == nullptr) Debug::Logger::init().Log(Debug::Logger::Type::error,"button's default texture is nullptr",true);
		defaultTX = defaultTexture;
	}

	void UIButton::setPressedTexture(const sf::Texture* pressedTexture)
	{
		if (pressedTexture == nullptr) Debug::Logger::init().Log(Debug::Logger::Type::error, "button's pressed texture is nullptr", true);
		pressedTX = pressedTexture;
	}
	
	void UIButton::setHoldTexture(const sf::Texture* holdTexture)
	{
		if (holdTexture == nullptr) Debug::Logger::init().Log(Debug::Logger::Type::error, "button's hold texture is nullptr", true);
		holdTX = holdTexture;
	}
	
	void UIButton::setHoveredTexture(const sf::Texture* hoveredTexture)
	{
		if (hoveredTexture == nullptr) Debug::Logger::init().Log(Debug::Logger::Type::error, "button's hovered texture is nullptr", true);
		hoveredTX = hoveredTexture;
	}

	const sf::Texture* UIButton::getDefaultTexture() const
	{
		return defaultTX;
	}

	const sf::Texture* UIButton::getPressedTexture() const
	{
		return pressedTX;
	}

	const sf::Texture* UIButton::getHoldTexture() const
	{
		return holdTX;
	}

	const sf::Texture* UIButton::getHoveredTexture() const
	{
		return hoveredTX;
	}

	const sf::Sprite& UIButton::getSprite() const
	{
		return sprite;
	}

	void UIButton::update()
	{
		VE_PROFILE_FUNC;
		sf::Vector2f Mpos = InputHandler::init().getMouseViewPos(Window::init().getWindow().getDefaultView());

		sf::FloatRect bounds = getLocalBounds();
		sf::Vector2f pos = getPosition();
			
		if ((Mpos.x > pos.x && Mpos.x < pos.x + bounds.width) &&
			(Mpos.y > pos.y && Mpos.y < pos.y + bounds.height))
		{
			if (InputHandler::init().isMousePressed(sf::Mouse::Button::Left) ||
			   (InputHandler::init().isMouseDown(sf::Mouse::Button::Left) && isHoldVar))
			{
				if (state != State::hold)
				{
					if (holdTX != nullptr)
						sprite.setTexture(*holdTX, true);
					isHoldVar = true;
					state = State::hold;
					//hold
				}
			}
			else if (InputHandler::init().isMouseRelease(sf::Mouse::Button::Left) && isHoldVar )
			{
				if (state != State::pressed)
				{
					if (pressedTX != nullptr)
						sprite.setTexture(*pressedTX, true);
					isHoldVar = false;
					state = State::pressed;
					//pressed
				}
			}
			else
			{
				if (state != State::hovered)
				{
					if (hoveredTX != nullptr)
						sprite.setTexture(*hoveredTX, true);
					isHoldVar = false;
					state = State::hovered;
					//hovered
				}
			}
		}
		else
		{
			if (InputHandler::init().isMouseRelease(sf::Mouse::Button::Left) &&
				isHoldVar )
			{
				if (state != State::nothing)
				{
					if (defaultTX != nullptr)
						sprite.setTexture(*defaultTX, true);
					isHoldVar = false;
					state = State::nothing;
				}
			}
			else if (isHoldVar == false)
			{
				if (state != State::nothing)
				{
					if (defaultTX != nullptr)
						sprite.setTexture(*defaultTX, true);
					state = State::nothing;
				}
			}
		}
	}

	sf::FloatRect UIButton::getLocalBounds() const
	{
		return sprite.getLocalBounds();
	}

	sf::FloatRect UIButton::getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}

	bool UIButton::isPressed() const
	{
		return (state == State::pressed);
	}

	bool UIButton::isHold() const
	{
		return (state == State::hold);
	}

	bool UIButton::isHovered() const
	{
		return (state == State::hovered);
	}

	void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		
		target.draw(sprite,states);
	}

	//private
}