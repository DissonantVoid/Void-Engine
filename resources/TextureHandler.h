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

			bool addTexture(const std::string& name,sf::Texture* texture);//should be heap "new" allocated
			bool addTexture(const std::string& name, const std::string& path,sf::IntRect rect = sf::IntRect());
			bool duplicateTexture(const std::string& originalName, const std::string& newName);
			bool isTexture(const std::string& name)const;
			const sf::Texture* getTexture(const std::string& name)const;
			sf::Texture* getTextureMd(const std::string& name);
			bool removeTexture(const std::string& name);

		private:

			std::unordered_map<std::string, sf::Texture*> textures;

			TextureHandler();
			~TextureHandler();
		};
	}
}