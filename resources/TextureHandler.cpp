#include "TextureHandler.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	namespace Resources
	{
		
		bool TextureHandler::addTexture(std::string name, sf::Texture* texture)
		{
			VE_PROFILE_FUNC;

			if (texture == nullptr)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add texture with name: " + name + ", it's nullptr (texture is now deleted)", true);
				delete texture;
				return false;
			}

			if (textures.find(name) != textures.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add texture with name: " + name + ", name already exist (texture is now deleted)", true);
				delete texture;
				return false;
			}
			textures.emplace(std::make_pair(name, texture));
			return true;
		}

		bool TextureHandler::addTexture(std::string name, std::string path, sf::IntRect rect)
		{
			VE_PROFILE_FUNC;
			if (textures.find(name) != textures.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add texture with name: " + name + ", name already exist", true);
				return false;
			}
			
			sf::Texture* texture = new sf::Texture;
			if (texture->loadFromFile(path, rect) == false)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add texture with name: " + name + ", file path or rect is invalid", true);
				delete texture;
				return false;
			}

			textures.emplace(std::make_pair(name,texture));
			return true;
		}

		bool TextureHandler::duplicateTexture(std::string originalName, std::string newName)
		{
			VE_PROFILE_FUNC;
			if (textures.find(originalName) != textures.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to duplicate texture with names: " + originalName + " - " + newName + ", originalName already exist", true);
				return false;
			}

			if (textures.find(newName) != textures.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to duplicate texture with names: " + originalName + " - " + newName + ", newName already exist", true);
				return false;
			}

			sf::Texture* texture = new sf::Texture(*textures.find(originalName)->second);
			textures.emplace(std::make_pair(newName,texture));
			return true;
		}

		bool TextureHandler::isTexture(std::string name)
		{
			return (textures.find(name) != textures.end());
		}

		const sf::Texture* TextureHandler::getTexture(std::string name)
		{
			return getTextureMd(name);
		}
		
		sf::Texture* TextureHandler::getTextureMd(std::string name)
		{
			VE_PROFILE_FUNC;
			std::unordered_map<std::string, sf::Texture*>::iterator result = textures.find(name);
			if (result != textures.end())
				return result->second;

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to get texture with name: " + name + ", doesn't exist", true);
			return nullptr;
		}

		bool TextureHandler::removeTexture(std::string name)
		{
			VE_PROFILE_FUNC;
			if (textures.find(name) != textures.end())
			{
				delete textures.at(name);
				textures.erase(name);
				return true;
			}

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to remove texture with name: " + name + ", doesn't exist", true);
			return false;
		}

		//private:

		TextureHandler::TextureHandler()
		{

		}

		TextureHandler::~TextureHandler()
		{
			VE_PROFILE_FUNC_ONCE;
			for (auto& texture : textures)
				delete texture.second;
		}
	}
}