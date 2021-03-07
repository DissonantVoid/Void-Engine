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

			bool addFont(const std::string& name, sf::Font* font);
			bool addFont(const std::string& name, const std::string& path);
			bool duplicateFont(const std::string& originalName, const std::string& newName);
			bool isFont(const std::string& name)const;
			const sf::Font* getFont(const std::string& name)const;
			bool removeFont(const std::string& name);

		private:

			std::unordered_map<std::string, sf::Font*> fonts;

			FontHandler();
			~FontHandler();
		};
	}
}