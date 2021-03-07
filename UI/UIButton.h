#pragma once

#include "Engine/UI/UI.h"
#include "SFML/Graphics.hpp"
#include "Engine/resources/SFML Extensions/Collider.h"

namespace VEngine
{
	class UIButton : public UI
	{
	public:
		UIButton();
		~UIButton();

		void setTextures(const sf::Texture* defaultTexture, const sf::Texture* pressedTexture, const sf::Texture* holdTexture, const sf::Texture* hoveredTexture);
		void setDefaultTexture(const sf::Texture* defaultTexture);
		void setPressedTexture(const sf::Texture* pressedTexture);
		void setHoldTexture(const sf::Texture* holdTexture);
		void setHoveredTexture(const sf::Texture* hoveredTexture);

		const sf::Texture* getDefaultTexture() const;
		const sf::Texture* getPressedTexture() const;
		const sf::Texture* getHoldTexture() const;
		const sf::Texture* getHoveredTexture() const;
		const sf::Sprite& getSprite() const;

		void update() override;

		sf::FloatRect getLocalBounds() const override;
		sf::FloatRect getGlobalBounds() const override;

		bool isPressed() const;
		bool isHold() const;
		bool isHovered() const;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		enum State
		{
			pressed, hold, hovered, nothing
		};

		sf::Sprite sprite;

		const sf::Texture* defaultTX;
		const sf::Texture* pressedTX;
		const sf::Texture* holdTX;
		const sf::Texture* hoveredTX;

		bool isHoldVar;
		State state;
		
	};
}