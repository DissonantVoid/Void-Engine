#pragma once

#include "Engine/UI/UI.h"
#include "SFML/Graphics.hpp"

namespace VEngine
{
	class UIValuePicker : public UI
	{
	public:
		UIValuePicker();
		~UIValuePicker();

		void update() override;

		sf::FloatRect getLocalBounds() const override;
		sf::FloatRect getGlobalBounds() const override;

		void draw(sf::RenderTarget &target, sf::RenderStates states)const override;

	private:


	};
}
