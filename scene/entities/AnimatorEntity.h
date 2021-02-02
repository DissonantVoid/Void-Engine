#pragma once

#include "Engine/scene/entities/Entity.h"
#include "Engine/resources/SFML Extensions/AnimSprite.h"

namespace VEngine
{
	class AnimatorEntity : public Entity
	{
		struct animationData
		{
			animationData(AnimSprite* animatedObject, sf::Uint8 drawLayer, bool shouldDraw, sf::RenderStates renderState)
				: animatedSprite(animatedObject), drawLayer(drawLayer), renderState(renderState), shouldDraw(shouldDraw) {}

			AnimSprite* animatedSprite = nullptr; //TODO: since we may have animated text as well, consider a base class for animated objects
			sf::RenderStates renderState;
			sf::Uint8 drawLayer;
			bool shouldDraw;
		};
	public:
		AnimatorEntity();
		~AnimatorEntity();
	
		void start() override;
		void update() override;
		void handleEvent(Event event) override;

		bool addAnimObject(std::string name, AnimSprite* animatedObject, sf::Uint8 drawLayer, bool hide = false, sf::RenderStates states = sf::RenderStates());
		bool removeAnimObject(std::string name);

		bool isValid(std::string name);

		template<typename as>
		as* getDrawable(std::string name)
		{
			auto* data = getDrawableData(name);
			if (data == nullptr)
				return nullptr;

			auto* castedData = dynamic_cast<as*>(data->animatedSprite);
			if (castedData == nullptr)
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "animatorEntity couldn't cast Data with name: " + name + " ,into the given type", true);

			return castedData;
		}

		animationData* getDrawableData(std::string name);

	private:
		std::unordered_map<std::string, animationData*> animObjects;

	};
}