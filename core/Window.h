#pragma once

#include "SFML/Graphics.hpp"

namespace VEngine
{
	class Window
	{
	public:
		static Window& init() { static Window instance; return instance; }

		sf::RenderWindow& getWindow();
		void setFullScreen(bool fullScreen);

	private:
		sf::RenderWindow window;

		Window();
		~Window();

	};
}

