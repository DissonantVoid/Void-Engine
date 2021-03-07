#include "AudioHandler.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	namespace Resources
	{

		bool AudioHandler::addSound(const std::string& name, sf::SoundBuffer* buffer)
		{
			VE_PROFILE_FUNC;

			if (buffer == nullptr)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add sound buffer with name: " + name + ", it's nullptr (texture is now deleted)", true);
				delete buffer;
				return false;
			}

			if (soundBuffers.find(name) != soundBuffers.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add sound buffer with name: " + name + ", name already exist (buffer is now deleted)", true);
				delete buffer;
				return false;
			}
			soundBuffers.emplace(std::make_pair(name, buffer));
			return true;
		}

		bool AudioHandler::addSound(const std::string& name, const std::string& path)
		{
			VE_PROFILE_FUNC;
			if (soundBuffers.find(name) != soundBuffers.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add sound buffer with name: " + name + ", name already exist", true);
				return false;
			}

			sf::SoundBuffer* buffer = new sf::SoundBuffer;
			if (buffer->loadFromFile(path) == false)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add sound buffer with name: " + name + ", file path may be invalid", true);
				delete buffer;
				return false;
			}
			
			soundBuffers.emplace(std::make_pair(name, buffer));
			return true;
		}

		bool AudioHandler::addMusic(const std::string& name, const std::string& path)
		{
			VE_PROFILE_FUNC;
			if (musicPaths.find(name) != musicPaths.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add music with name: " + name + ", name already exist", true);
				return false;
			}

			sf::Music pathCheck;
			if (pathCheck.openFromFile(path) == false)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to add music with name: " + name + ", file path may be invalid", true);
				return false;
			}

			std::string* pathHeap = new std::string;
			*pathHeap = path;
			musicPaths.emplace(std::make_pair(name, pathHeap));
			return true;
		}

		bool AudioHandler::duplicateSound(const std::string& originalName, const std::string& newName)
		{
			VE_PROFILE_FUNC;
			if (soundBuffers.find(originalName) != soundBuffers.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to duplicate sound with names: " + originalName + " - " + newName + ", originalName already exist", true);
				return false;
			}

			if (soundBuffers.find(newName) != soundBuffers.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to duplicate sound with names: " + originalName + " - " + newName + ", newName already exist", true);
				return false;
			}

			sf::SoundBuffer* sound = new sf::SoundBuffer(*soundBuffers.find(originalName)->second);
			soundBuffers.emplace(std::make_pair(newName, sound));
			return true;
		}

		bool AudioHandler::duplicateMusic(const std::string& originalName, const std::string& newName)
		{
			VE_PROFILE_FUNC;
			if (musicPaths.find(originalName) != musicPaths.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to duplicate music with names: " + originalName + " - " + newName + ", originalName already exist", true);
				return false;
			}

			if (musicPaths.find(newName) != musicPaths.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to duplicate music with names: " + originalName + " - " + newName + ", newName already exist", true);
				return false;
			}

			std::string* musicPath = new std::string(*musicPaths.find(originalName)->second);
			musicPaths.emplace(std::make_pair(newName, musicPath));
			return true;
		}

		bool AudioHandler::isSound(const std::string& name) const
		{
			return (soundBuffers.find(name) != soundBuffers.end());
		}

		bool AudioHandler::isMusic(const std::string& name) const
		{
			return (musicPaths.find(name) != musicPaths.end());
		}

		const sf::SoundBuffer* AudioHandler::getSound(const std::string& name) const
		{
			VE_PROFILE_FUNC;
			auto result = soundBuffers.find(name);
			if (result != soundBuffers.end())
				return result->second;

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to get sound buffer with name: " + name + ", doesn't exist", true);
			return nullptr;
		}

		const std::string* AudioHandler::getMusicPath(const std::string& name) const
		{
			VE_PROFILE_FUNC;
			auto result = musicPaths.find(name);
			if (result != musicPaths.end())
				return result->second;

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to get music with name: " + name + ", doesn't exist", true);
			return nullptr;
		}

		bool AudioHandler::removeSound(const std::string& name)
		{
			VE_PROFILE_FUNC;
			if (soundBuffers.find(name) != soundBuffers.end())
			{
				delete soundBuffers.at(name);
				soundBuffers.erase(name);
				return true;
			}

			Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to remove sound buffer with name: " + name + ", doesn't exist", true);
			return false;
		}

		bool AudioHandler::removeMusic(const std::string& name)
		{
			VE_PROFILE_FUNC;
			if (musicPaths.find(name) != musicPaths.end())
			{
				delete musicPaths.at(name);
				musicPaths.erase(name);
				return true;
			}

			Debug::Logger::init().Log(Debug::Logger::Type::error, "unable to remove music with name: " + name + ", doesn't exist", true);
			return false;
		}

		//private:

		AudioHandler::AudioHandler()
		{

		}

		AudioHandler::~AudioHandler()
		{
			for (auto& soundB : soundBuffers)
				delete soundB.second;

			for (auto& music : musicPaths)
				delete music.second;
		}
	}
}