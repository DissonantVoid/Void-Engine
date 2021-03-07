#include "UISlider.h"

#include "Engine/util/Utility.h"
#include "Engine/core/InputHandler.h"

#include "Engine/debug/ProfilerSample.h"
#include "Engine/core/Window.h"

namespace VEngine
{
	UISlider::UISlider(Direction direction)
		: direction(direction)
	{
		
	}

	UISlider::~UISlider()
	{

	}

	void UISlider::update()
	{
		VE_PROFILE_FUNC;
		sf::Vector2f Mpos = InputHandler::init().getMouseViewPos(Window::init().getWindow().getDefaultView());

		sf::FloatRect dotBounds = dot.getLocalBounds();
		sf::Vector2f dotPos = dot.getPosition() - sf::Vector2f(dotBounds.width / 2, dotBounds.height / 2);

		if ((Mpos.x > dotPos.x && Mpos.x < dotPos.x + dotBounds.width) &&
			(Mpos.y > dotPos.y && Mpos.y < dotPos.y + dotBounds.height))
		{
			if (InputHandler::init().isMousePressed(sf::Mouse::Left))
			{
				isHold = true;
			}
		}

		if (InputHandler::init().isMouseDown(sf::Mouse::Left) && isHold)
		{
			switch (direction)
			{
			case VEngine::UISlider::Direction::UpToDown:

				dot.setPosition(sf::Vector2f(getPosition().x, Mpos.y));
				if (dot.getPosition().y < positionRange.x) dot.setPosition(sf::Vector2f(getPosition().x, positionRange.x));
				if (dot.getPosition().y > positionRange.y) dot.setPosition(sf::Vector2f(getPosition().x, positionRange.y));
				break;

			case VEngine::UISlider::Direction::DownToUp:

				dot.setPosition(sf::Vector2f(getPosition().x, Mpos.y));
				if (dot.getPosition().y > positionRange.x) dot.setPosition(sf::Vector2f(getPosition().x, positionRange.x));
				if (dot.getPosition().y < positionRange.y) dot.setPosition(sf::Vector2f(getPosition().x, positionRange.y));
				break;

			case VEngine::UISlider::Direction::LeftToRight:

				dot.setPosition(sf::Vector2f(Mpos.x, getPosition().y));
				if (dot.getPosition().x < positionRange.x) dot.setPosition(sf::Vector2f(positionRange.x, getPosition().y));
				if (dot.getPosition().x > positionRange.y) dot.setPosition(sf::Vector2f(positionRange.y, getPosition().y));
				break;

			case VEngine::UISlider::Direction::RightToLeft:

				dot.setPosition(sf::Vector2f(Mpos.x, getPosition().y));
				if (dot.getPosition().x > positionRange.x) dot.setPosition(sf::Vector2f(positionRange.x, getPosition().y));
				if (dot.getPosition().x < positionRange.y) dot.setPosition(sf::Vector2f(positionRange.y, getPosition().y));
				break;
			}
		}

		if (InputHandler::init().isMouseRelease(sf::Mouse::Left))
		{
			isHold = false;
		}
	}

	void UISlider::setPercentage(float percentage)
	{
		VE_PROFILE_FUNC;
		if (percentage > 100 || percentage < 0)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "slider set percentage is wrong: " + std::to_string(percentage), true);
			return;
		}

		switch (direction)
		{
		case VEngine::UISlider::Direction::UpToDown:
		case VEngine::UISlider::Direction::DownToUp:
			
			dot.setPosition(sf::Vector2f(getPosition().x, percentageToPosition(percentage)));
			break;

		case VEngine::UISlider::Direction::LeftToRight:
		case VEngine::UISlider::Direction::RightToLeft:
		
			dot.setPosition(sf::Vector2f(percentageToPosition(percentage), getPosition().y));
			break;
		}
	}
	
	void UISlider::setValue(float value)
	{
		VE_PROFILE_FUNC;
		if (value < convertRange.x || value > convertRange.y)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "slider set value is wrong: " + std::to_string(value), true);
			return;
		}

		switch (direction)
		{
		case VEngine::UISlider::Direction::UpToDown:
		case VEngine::UISlider::Direction::DownToUp:

			dot.setPosition(sf::Vector2f(getPosition().x, valueToPosition(value)));
			break;

		case VEngine::UISlider::Direction::LeftToRight:
		case VEngine::UISlider::Direction::RightToLeft:

			dot.setPosition(sf::Vector2f(valueToPosition(value), getPosition().y));
			break;
		}
	}

	void UISlider::setRange(float min, float max)
	{
		if (min >= max)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "slider set range is wrong, min= " + std::to_string(min) + ", max= " + std::to_string(max), true);
			return;
		}

		convertRange.x = min;
		convertRange.y = max;

	}

	void UISlider::setOffset(float offset)
	{
		switch (direction)
		{
		case VEngine::UISlider::Direction::UpToDown:
		case VEngine::UISlider::Direction::LeftToRight:

			positionRange.x += this->offset;//remove the current offset first
			positionRange.x -= offset;

			positionRange.y -= this->offset;
			positionRange.y += offset;
			break;

		case VEngine::UISlider::Direction::DownToUp:
		case VEngine::UISlider::Direction::RightToLeft:

			positionRange.x -= this->offset;
			positionRange.x += offset;

			positionRange.y += this->offset;
			positionRange.y -= offset;
			break;
		}

		this->offset = offset;
	}

	float UISlider::getPercentage() const
	{
		VE_PROFILE_FUNC;
		switch (direction)
		{
		case Direction::UpToDown:
		case Direction::DownToUp:

			return Util::mapValue<float>(dot.getPosition().y, positionRange.x, positionRange.y, 0, 100);
			break;

		case Direction::LeftToRight:
		case Direction::RightToLeft:

			return Util::mapValue<float>(dot.getPosition().x, positionRange.x, positionRange.y, 0, 100);
			break;
		}
	}

	float UISlider::getValue() const
	{
		VE_PROFILE_FUNC;
		switch (direction)
		{
		case Direction::UpToDown:
		case Direction::DownToUp:

			return Util::mapValue<float>(dot.getPosition().y, positionRange.x, positionRange.y, convertRange.x, convertRange.y);
			break;

		case Direction::LeftToRight:
		case Direction::RightToLeft:

			return Util::mapValue<float>(dot.getPosition().x, positionRange.x, positionRange.y, convertRange.x, convertRange.y);
			break;
		}
	}

	void UISlider::setFrameTexture(const sf::Texture* texture)
	{
		VE_PROFILE_FUNC;
		if (texture == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "slider's frame texture is nullptr", true);
			return;
		}

		//update texture and origin
		frame.setTexture(*texture,true);
		sf::Vector2u frameSize = texture->getSize();
		frame.setOrigin(frameSize.x / 2, frameSize.y / 2);

		float oldPercentage = getPercentage(); //before posRange change

		switch (direction) //don't reset, set position according to percentage before this was called
		{
		case VEngine::UISlider::Direction::UpToDown:

			positionRange.x = (getPosition().y - frameSize.y / 2) - offset; //we get the position of the frame as this->getPos(), because frame pos is always 0
			positionRange.y = (getPosition().y + frameSize.y / 2) + offset;

			dot.setPosition(sf::Vector2f(getPosition().x, percentageToPosition(oldPercentage)));

			break;
		case VEngine::UISlider::Direction::DownToUp:

			positionRange.x = (getPosition().y + frameSize.y / 2) + offset;
			positionRange.y = (getPosition().y - frameSize.y / 2) - offset;

			dot.setPosition(sf::Vector2f(getPosition().x, percentageToPosition(oldPercentage)));

			break;
		case VEngine::UISlider::Direction::LeftToRight:

			positionRange.x = (getPosition().x - frameSize.x / 2) - offset;
			positionRange.y = (getPosition().x + frameSize.x / 2) + offset;

			dot.setPosition(sf::Vector2f(percentageToPosition(oldPercentage), getPosition().y));

			break;
		case VEngine::UISlider::Direction::RightToLeft:

			positionRange.x = (getPosition().x + frameSize.x / 2) + offset;
			positionRange.y = (getPosition().x - frameSize.x / 2) - offset;

			dot.setPosition(sf::Vector2f(percentageToPosition(oldPercentage), getPosition().y));

			break;
		}

	}

	void UISlider::setDotTexture(const sf::Texture* texture)
	{
		VE_PROFILE_FUNC;
		if (texture == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "slider's dot texture is nullptr", true);
			return;
		}

		dot.setTexture(*texture, true);
		sf::Vector2u size = texture->getSize();
		dot.setOrigin(size.x / 2, size.y / 2);
	}

	const sf::Sprite& UISlider::getFrameSprite() const
	{
		return frame;
	}

	const sf::Sprite& UISlider::getDotSprite() const 
	{
		return dot;
	}

	sf::FloatRect UISlider::getLocalBounds() const
	{
		return frame.getLocalBounds();
	}

	sf::FloatRect UISlider::getGlobalBounds() const
	{
		return frame.getGlobalBounds();
	}

	void UISlider::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(frame,states);
		target.draw(dot);
	}

	//private

	float UISlider::percentageToPosition(float percentage)
	{
		return Util::mapValue<float>(percentage,0,100,positionRange.x,positionRange.y);
	}

	float UISlider::valueToPosition(float value)
	{
		return Util::mapValue<float>(value, convertRange.x, convertRange.y, positionRange.x, positionRange.y);
	}
}