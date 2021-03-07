#pragma once

#include "SFML/Graphics.hpp"

namespace VEngine
{
	struct animFrame
	{
		sf::Texture *texture;
		float delay;
		sf::Vector2f offset; //in case of texture being bigger/smaller than others and need to be adjusted
	};

	struct animation
	{
		bool isLoop;
		std::vector<animFrame> frames;
	};
}

