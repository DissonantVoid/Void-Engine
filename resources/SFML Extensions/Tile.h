#pragma once

#include "SFML/Graphics.hpp"

namespace VEngine
{
	class Tile : public sf::Drawable, public sf::Transformable //NOTE: a costum tile can be made by inheriting from this class, otherwise this class is usable as a tile
	{
	public:
		Tile(){}
		virtual ~Tile(){}
	
		virtual void update() = 0;

	private:

	};
}