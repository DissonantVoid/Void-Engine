#include "AudioEntity.h"

namespace VEngine
{
	AudioEntity::AudioEntity()
	{

	}

	AudioEntity::~AudioEntity()
	{
		for (auto& audio : audios)
		{
			delete audio.second;
		}
	}

	void AudioEntity::start()
	{

	}

	void AudioEntity::update()
	{

	}

	void AudioEntity::handleEvent(Event event)
	{

	}

	bool AudioEntity::addAudio(std::string name, sf::SoundSource* sound)
	{
		if (sound == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "audioEntity couldn't add audio with name: " + name + " ,it is nullptr ", true);
			return false;
		}

		if (audios.find(name) != audios.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "audioEntity couldn't add audio with name: " + name + " ,name already exist (drawable is now deleted)", true);
			delete sound;
			return false;
		}

		audios.emplace(std::make_pair(name, sound));
		return true;
	}

	bool AudioEntity::removeAudio(std::string name)
	{
		auto result = audios.find(name);
		if (result == audios.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "audioEntity couldn't remove drawable with name: " + name + " ,name doesn't exist", true);
			return false;
		}

		delete audios.at(result->first);
		audios.erase(result);
		return true;
	}

	bool AudioEntity::isValid(std::string name)const
	{
		return (audios.find(name) != audios.end());
	}

	//private
}