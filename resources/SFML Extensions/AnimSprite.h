#pragma once

#include <unordered_map>

#include "SFML/Graphics.hpp"
#include "Engine/resources/AnimationHandler.h"

namespace VEngine
{
	class AnimSprite : public sf::Drawable ,public sf::Transformable
	{
	public:
		AnimSprite();
		~AnimSprite();

		void update();

		bool addAnimation(std::string name,Resources::animation* animation);
		bool removeAnimation(std::string name);
		bool isValidAnim(std::string name);

		Resources::animation* getAnim(std::string name);
		void playAnim(std::string name);
		std::string getCurrentAnim();
		bool isPlaying();
		void stopAnim();

	private:
		sf::Sprite sprite;
		sf::Clock clock;
		bool isPlayingVar;
		std::string currentAnim;
		sf::Uint16 animIndex; //the index is between 0 and frames+1, because we'll need an additional iteration to wait for last delay since every frame waits for the delay of the previous frame
		sf::Vector2f currentOffset;// for sprite position in draw
		std::unordered_map<std::string, Resources::animation*> animations;

		void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

	};
}