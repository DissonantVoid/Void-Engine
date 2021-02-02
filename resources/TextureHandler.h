#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>

namespace VEngine
{
	namespace Resources
	{
		class TextureHandler //TODO: consider a function to create add texture from an existing texture from the map, since sometimes we'll need to modify the texture, so we do so by storing a copy of it with different name and getting it with a non const getter
		{					 //another solution would be to find a way so that modifications are only applied right before drawing and set off right after
		public:
			static TextureHandler& init() { static TextureHandler instance; return instance;}

			bool addTexture(std::string name,sf::Texture* texture);//should be heap "new" allocated
			bool addTexture(std::string name,std::string path,sf::IntRect rect = sf::IntRect());
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