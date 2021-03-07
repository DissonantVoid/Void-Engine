#pragma once

#include "Engine/UI/UI.h"
#include  "SFML/Graphics.hpp"

namespace VEngine
{
	class UITextBox : public UI
	{
	public:
		UITextBox();
		~UITextBox();

		void update() override;

		sf::FloatRect getLocalBounds() const override;
		sf::FloatRect getGlobalBounds() const override;

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	private:
		sf::Sprite frame;
		sf::Text text;

		const sf::Texture* frameDefault;
		const sf::Texture* frameSelected;

	};
}

