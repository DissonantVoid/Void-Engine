#pragma once

#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace VEngine
{
	class UI : public sf::Transformable,public sf::Drawable
	{
	public:
		UI();
		virtual ~UI();

		virtual void update() = 0;

		virtual sf::FloatRect getLocalBounds() const;
		virtual sf::FloatRect getGlobalBounds() const;

	private:
		sf::RenderWindow& window;
	};

}