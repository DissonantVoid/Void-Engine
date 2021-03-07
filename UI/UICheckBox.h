#pragma once

#include "Engine/UI/UI.h"
#include "SFML/Graphics.hpp"

namespace VEngine
{
	class UICheckBox : public UI
	{
	public:
		UICheckBox();
		~UICheckBox();

		void update() override;

		void setState(bool state);
		bool getState() const;

		void setDefaultTexture(const sf::Texture* texture);
		void setCheckedTexture(const sf::Texture* texture);

		sf::FloatRect getLocalBounds() const override;
		sf::FloatRect getGlobalBounds() const override;

		void draw(sf::RenderTarget &target,sf::RenderStates states) const override;

	private:

		sf::Sprite sprite;
		const sf::Texture* boxDefault;
		const sf::Texture* boxChecked;
		bool state;

	};
}