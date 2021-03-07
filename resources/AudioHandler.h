#pragma once
#include "SFML/Audio.hpp"
#include <unordered_map>

namespace VEngine
{
	namespace Resources
	{
		class AudioHandler
		{
		public:
			static AudioHandler& init() { static AudioHandler instance; return instance; }

			bool addSound(const std::string& name, sf::SoundBuffer* buffer);
			bool addSound(const std::string& name, const std::string& path);
			bool addMusic(const std::string& name, const std::string& path);
			bool duplicateSound(const std::string& originalName, const std::string& newName);
			bool duplicateMusic(const std::string& originalName, const std::string& newName);
			bool isSound(const std::string& name)const;
			bool isMusic(const std::string& name)const;
			const sf::SoundBuffer* getSound(const std::string& name)const;
			const std::string* getMusicPath(const std::string& name)const;
			bool removeSound(const std::string& name);
			bool removeMusic(const std::string& name);

		private:

			std::unordered_map<std::string, sf::SoundBuffer*> soundBuffers;
			std::unordered_map<std::string, std::string*> musicPaths;

			AudioHandler();
			~AudioHandler();
		};
	}
}