#include "AudioHandler.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	namespace Resources
	{

		bool AudioHandler::addSound(std::string name, sf::SoundBuffer* buffer)
		{
			VE_PROFILE_FUNC;
			if (soundBuffers.find(name) != soundBuffers.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add sound buffer with name: " + name + ", name already exist (buffer is now deleted)", true);
				delete buffer;
				return false;
			}
			soundBuffers.emplace(std::make_pair(name, buffer));
			return true;
		}

		bool AudioHandler::addSound(std::string name, std::string path)
		{
			VE_PROFILE_FUNC;
			if (soundBuffers.find(name) != soundBuffers.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add sound buffer with name: " + name + ", name already exist", true);
				return false;
			}

			sf::SoundBuffer* buffer = new sf::SoundBuffer;
			if (buffer->loadFromFile(path) == false)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add sound buffer with name: " + name + ", file path may be invalid", true);
				delete buffer;
				return false;
			}
			
			soundBuffers.emplace(std::make_pair(name, buffer));
			return true;
		}

		bool AudioHandler::addMusic(std::string name, std::string path)
		{
			VE_PROFILE_FUNC;
			if (musicPaths.find(name) != musicPaths.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add music with name: " + name + ", name already exist", true);
				return false;
			}

			sf::Music pathCheck;
			if (pathCheck.openFromFile(path) == false)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add music with name: " + name + ", file path may be invalid", true);
				return false;
			}

			std::string* pathHeap = new std::string;
			*pathHeap = path;
			musicPaths.emplace(std::make_pair(name, pathHeap));
			return true;
		}

		bool AudioHandler::isSound(std::string name)
		{
			return (soundBuffers.find(name) != soundBuffers.end());
		}

		bool AudioHandler::isMusic(std::string name)
		{
			return (musicPaths.find(name) != musicPaths.end());
		}

		const sf::SoundBuffer* AudioHandler::getSound(std::string name)
		{
			VE_PROFILE_FUNC;
			std::unordered_map<std::string, sf::SoundBuffer*>::iterator result = soundBuffers.find(name);
			if (result != soundBuffers.end())
				return result->second;

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to get sound buffer with name: " + name + ", doesn't exist", true);
			return nullptr;
		}

		const std::string* AudioHandler::getMusicPath(std::string name)
		{
			VE_PROFILE_FUNC;
			std::unordered_map<std::string, std::string*>::iterator result = musicPaths.find(name);
			if (result != musicPaths.end())
				return result->second;

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to get music with name: " + name + ", doesn't exist", true);
			return nullptr;
		}

		bool AudioHandler::removeSound(std::string name)
		{
			VE_PROFILE_FUNC;
			if (soundBuffers.find(name) != soundBuffers.end())
			{
				delete soundBuffers.at(name);
				soundBuffers.erase(name);
				return true;
			}

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to remove sound buffer with name: " + name + ", doesn't exist", true);
			return false;
		}

		bool AudioHandler::removeMusic(std::string name)
		{
			VE_PROFILE_FUNC;
			if (musicPaths.find(name) != musicPaths.end())
			{
				delete musicPaths.at(name);
				musicPaths.erase(name);
				return true;
			}

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to remove music with name: " + name + ", doesn't exist", true);
			return false;
		}

		//private:

		AudioHandler::AudioHandler()
		{

		}

		AudioHandler::~AudioHandler()
		{
			VE_PROFILE_FUNC_ONCE;
			for (auto& soundB : soundBuffers)
				delete soundB.second;

			for (auto& music : musicPaths)
				delete music.second;
		}
	}
}