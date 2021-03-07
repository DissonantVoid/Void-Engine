#pragma once

#include <unordered_map>
#include "SFML/Audio.hpp"

#include "Engine/debug/Logger.h"
#include "Engine/scene/entities/Entity.h"

namespace VEngine
{
	class AudioEntity : public Entity //store music->audioHandler::string, sound->audioHandler::soundBuffer
	{
	public:
		AudioEntity();
		~AudioEntity();
	
		void start() override;
		void update() override;
		void handleEvent(Event event) override;

		bool addAudio(std::string name, sf::SoundSource* sound);
		bool removeAudio(std::string name);

		bool isValid(std::string name)const;

		template<typename as>
		as* getAudio(std::string name) const
		{
			auto result = audios.find(name);
			if (result == audios.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "audioEntity couldn't cast Data with name: " + name + " ,into the given type, name doesn't exist", true);
				return nullptr;
			}

			auto* castedData = dynamic_cast<as*>(result->second);
			if (castedData == nullptr)
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "audioEntity couldn't cast Data with name: " + name + " ,into the given type", true);

			return castedData;
		}

	private:
		std::unordered_map<std::string, sf::SoundSource*> audios;

	};
}