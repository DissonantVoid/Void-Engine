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

			bool addSound(std::string name, sf::SoundBuffer* buffer);
			bool addSound(std::string name, std::string path);
			bool addMusic(std::string name, std::string path);
			bool isSound(std::string name);
			bool isMusic(std::string name);
			const sf::SoundBuffer* getSound(std::string name);
			const std::string* getMusicPath(std::string name);
			bool removeSound(std::string name);
			bool removeMusic(std::string name);

		private:

			std::unordered_map<std::string, sf::SoundBuffer*> soundBuffers;
			std::unordered_map<std::string, std::string*> musicPaths;

			AudioHandler();
			~AudioHandler();
		};
	}
}