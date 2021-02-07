#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>

namespace VEngine
{
	namespace Resources
	{
		class TextureHandler
		{
		public:
			static TextureHandler& init() { static TextureHandler instance; return instance;}

			bool addTexture(std::string name,sf::Texture* texture);//should be heap "new" allocated
			bool addTexture(std::string name,std::string path,sf::IntRect rect = sf::IntRect());
			bool duplicateTexture(std::string originalName, std::string newName);
			bool isTexture(std::string name);
			const sf::Texture* getTexture(std::string name);
			sf::Texture* getTextureMd(std::string name);
			bool removeTexture(std::string name);

		private:

			std::unordered_map<std::string, sf::Texture*> textures;

			TextureHandler();
			~TextureHandler();
		};
	}
}