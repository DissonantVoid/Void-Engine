#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>

namespace VEngine
{
	namespace Resources
	{
		class FontHandler
		{
		public:
			static FontHandler& init() { static FontHandler instance; return instance; }

			bool addFont(std::string name, sf::Font* font);
			bool addFont(std::string name, std::string path);
			bool duplicateFont(std::string originalName, std::string newName);
			bool isFont(std::string name);
			const sf::Font* getFont(std::string name);
			bool removeFont(std::string name);

		private:

			std::unordered_map<std::string, sf::Font*> fonts;

			FontHandler();
			~FontHandler();
		};
	}
}