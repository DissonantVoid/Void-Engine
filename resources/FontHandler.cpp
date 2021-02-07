#include "FontHandler.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	namespace Resources
	{
		bool FontHandler::addFont(std::string name, sf::Font* font)
		{
			VE_PROFILE_FUNC;

			if (font == nullptr)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add font with name: " + name + ", it's nullptr (texture is now deleted)", true);
				delete font;
				return false;
			}

			if (fonts.find(name) != fonts.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add font with name: " + name + ", name already exist (font is now deleted)", true);
				delete font;
				return false;
			}
			fonts.emplace(std::make_pair(name, font));
			return true;
		}

		bool FontHandler::addFont(std::string name, std::string path)
		{
			VE_PROFILE_FUNC;
			if (fonts.find(name) != fonts.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add font with name: " + name + ", name already exist", true);
				return false;
			}
			
			sf::Font* font = new sf::Font;
			if (font->loadFromFile(path) == false)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add font with name: " + name + ", file path may be invalid", true);
				delete font;
				return false;
			}

			fonts.emplace(std::make_pair(name, font));
			return true;
		}

		bool FontHandler::duplicateFont(std::string originalName, std::string newName)
		{
			VE_PROFILE_FUNC;
			if (fonts.find(originalName) != fonts.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to duplicate font with names: " + originalName + " - " + newName + ", originalName already exist", true);
				return false;
			}

			if (fonts.find(newName) != fonts.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to duplicate font with names: " + originalName + " - " + newName + ", newName already exist", true);
				return false;
			}

			sf::Font* font = new sf::Font(*fonts.find(originalName)->second);
			fonts.emplace(std::make_pair(newName, font));
			return true;
		}

		bool FontHandler::isFont(std::string name)
		{
			return (fonts.find(name) != fonts.end());
		}

		const sf::Font* FontHandler::getFont(std::string name)
		{
			VE_PROFILE_FUNC;
			std::unordered_map<std::string, sf::Font*>::iterator result = fonts.find(name);
			if (result != fonts.end())
				return result->second;

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to get font with name: " + name + ", doesn't exist", true);
			return nullptr;
		}

		bool FontHandler::removeFont(std::string name)
		{
			VE_PROFILE_FUNC;
			if (fonts.find(name) != fonts.end())
			{
				delete fonts.at(name);
				fonts.erase(name);
				return true;
			}

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to remove font with name: " + name + ", doesn't exist", true);
			return false;
		}

		//private:

		FontHandler::FontHandler()
		{

		}

		FontHandler::~FontHandler()
		{
			VE_PROFILE_FUNC_ONCE;
			for (auto& font : fonts)
				delete font.second;
		}
	}
}