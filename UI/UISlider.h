#pragma once

#include "Engine/UI/UI.h"
#include "SFML/Graphics.hpp"

#include "Engine/debug/Logger.h"

namespace VEngine
{
	class UISlider : public UI
	{
	public:

		enum class Direction
		{UpToDown, DownToUp, LeftToRight, RightToLeft};

		UISlider(Direction direction);
		~UISlider();

		void update() override;

		void setPercentage(float percentage);
		void setValue(float value);
		void setRange(float min, float max);
		void setOffset(float offset);

		float getPercentage() const;
		float getValue() const;

		void setFrameTexture(const sf::Texture* texture);
		void setDotTexture(const sf::Texture* texture);

		const sf::Sprite& getFrameSprite() const;
		const sf::Sprite& getDotSprite() const;

		sf::FloatRect getLocalBounds() const override;
		sf::FloatRect getGlobalBounds() const override;

		void draw(sf::RenderTarget &target,sf::RenderStates states) const override;

	private:
		sf::Sprite frame;
		sf::Sprite dot;
		bool isHold;
		sf::Vector2f positionRange = sf::Vector2f(0,100); //x = begining. y = end
		float offset;
		Direction direction;

		sf::Vector2f convertRange = sf::Vector2f(0,100);

		float percentageToPosition(float percentage); //only return position of one axis since the other won't change
		float valueToPosition(float value);

	};

}