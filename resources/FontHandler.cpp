#include "FontHandler.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	namespace Resources
	{
		bool FontHandler::addFont(const std::string& name, sf::Font* font)
		{
			VE_PROFILE_FUNC;

			if (font == nullptr)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add font with name: " + name + ", it's nullptr (texture is now deleted)", true);
				delete font;
				return false;
			}

			if (fonts.find(name) != fonts.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add font with name: " + name + ", name already exist (font is now deleted)", true);
				delete font;
				return false;
			}
			fonts.emplace(std::make_pair(name, font));
			return true;
		}

		bool FontHandler::addFont(const std::string& name, const std::string& path)
		{
			VE_PROFILE_FUNC;
			if (fonts.find(name) != fonts.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add font with name: " + name + ", name already exist", true);
				return false;
			}
			
			sf::Font* font = new sf::Font;
			if (font->loadFromFile(path) == false)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add font with name: " + name + ", file path may be invalid", true);
				delete font;
				return false;
			}

			fonts.emplace(std::make_pair(name, font));
			return true;
		}

		bool FontHandler::duplicateFont(const std::string& originalName, const std::string& newName)
		{
			VE_PROFILE_FUNC;
			if (fonts.find(originalName) != fonts.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to duplicate font with names: " + originalName + " - " + newName + ", originalName already exist", true);
				return false;
			}

			if (fonts.find(newName) != fonts.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to duplicate font with names: " + originalName + " - " + newName + ", newName already exist", true);
				return false;
			}

			sf::Font* font = new sf::Font(*fonts.find(originalName)->second);
			fonts.emplace(std::make_pair(newName, font));
			return true;
		}

		bool FontHandler::isFont(const std::string& name)const
		{
			return (fonts.find(name) != fonts.end());
		}

		const sf::Font* FontHandler::getFont(const std::string& name)const
		{
			VE_PROFILE_FUNC;
			auto result = fonts.find(name);
			if (result != fonts.end())
				return result->second;

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to get font with name: " + name + ", doesn't exist", true);
			return nullptr;
		}

		bool FontHandler::removeFont(const std::string& name)
		{
			VE_PROFILE_FUNC;
			if (fonts.find(name) != fonts.end())
			{
				delete fonts.at(name);
				fonts.erase(name);
				return true;
			}

			Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to remove font with name: " + name + ", doesn't exist", true);
			return false;
		}

		//private:

		FontHandler::FontHandler()
		{

		}

		FontHandler::~FontHandler()
		{
			for (auto& font : fonts)
				delete font.second;
		}
	}
}