#include "AnimatorEntity.h"

#include "Engine/debug/Logger.h"

namespace VEngine
{
	AnimatorEntity::AnimatorEntity()
	{

	}

	AnimatorEntity::~AnimatorEntity()
	{
		for (auto& object : animObjects)
		{
			delete object.second->animatedSprite;
			delete object.second;
		}
	}

	void AnimatorEntity::start()
	{

	}

	void AnimatorEntity::update()
	{
		for (auto& object : animObjects)
		{
			if (object.second->shouldDraw == true)
			{
				Event event(Event::EventType::RendererDraw);
				event.drawEvent.drawable = object.second->animatedSprite;
				event.drawEvent.drawLayer = object.second->drawLayer;
				event.drawEvent.renderState = object.second->renderState;
				event.submite();
			}
		}
	}

	void AnimatorEntity::handleEvent(Event event)
	{

	}
	
	bool AnimatorEntity::addAnimObject(std::string name, AnimSprite* animatedObject, sf::Uint8 drawLayer, bool hide, sf::RenderStates states)
	{
		if (animatedObject == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "animatorEntity couldn't add object with name: " + name + " ,it is nullptr", true);
			return false;
		}

		if (animObjects.find(name) != animObjects.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "animatorEntity couldn't add object with name: " + name + " ,name already exist (drawable is now deleted)", true);
			delete animatedObject;
			return false;
		}

		animationData* data = new animationData(animatedObject, drawLayer, (!hide), states);
		animObjects.emplace(std::make_pair(name, data));
		return true;
	}

	bool AnimatorEntity::removeAnimObject(std::string name)
	{
		auto result = animObjects.find(name);
		if (result == animObjects.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "animatorEntity couldn't remove object with name: " + name + " ,name doesn't exist", true);
			return false;
		}

		delete animObjects.at(result->first);
		delete animObjects.at(result->first)->animatedSprite;
		animObjects.erase(result);
		return true;
	}

	bool AnimatorEntity::isValid(std::string name)
	{
		return (animObjects.find(name) != animObjects.end());
	}

	AnimatorEntity::animationData* AnimatorEntity::getDrawableData(std::string name)
	{
		auto result = animObjects.find(name);
		if (result == animObjects.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "animatorEntity couldn't get object Data with name: " + name + " ,name doesn't exist", true);
			return nullptr;
		}

		return result->second;
	}

	//private
}