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

			AnimSprite* animatedSprite = nullptr;
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

		bool isValid(std::string name)const;

		AnimSprite* getAnimatedDrawable(std::string name) const;

		animationData* getDrawableData(std::string name) const;

	private:
		std::unordered_map<std::string, animationData*> animObjects;

	};
}