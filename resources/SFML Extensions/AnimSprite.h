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

		bool addAnimation(const std::string& name,const animation* animation);
		bool removeAnimation(const std::string& name);
		bool isValidAnim(const std::string& name) const;

		const animation* getAnim(const std::string& name);
		const sf::Sprite* getSprite() const;
		void playAnim(const std::string& name,bool forcePlay = false);
		std::string getCurrentAnim() const;
		sf::Uint16 getCurrentFrameIndex() const;
		bool isPlaying() const;
		void stopAnim();

		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;
		inline void setPosition(float x, float y) { sprite.setPosition(x,y);}
		inline void setPosition(const sf::Vector2f& position) { sprite.setPosition(position); }
		inline void setRotation(float angle) { sprite.setRotation(angle);}
		inline void setScale(float factorX, float factorY) { sprite.setScale(factorX,factorY);}
		inline void setScale(const sf::Vector2f& factors) { sprite.setScale(factors);}
		inline void setOrigin(float x, float y) { sprite.setOrigin(x,y);}
		inline void setOrigin(const sf::Vector2f& origin) { sprite.setOrigin(origin); }
		inline const sf::Vector2f& getPosition() const { return sprite.getPosition();}
		inline float getRotation() const { return sprite.getRotation();}
		inline const sf::Vector2f& getScale() const { return sprite.getScale();}
		inline const sf::Vector2f& getOrigin() const { return sprite.getOrigin();}
		inline void move(float offsetX, float offsetY) { sprite.move(offsetX,offsetY);}
		inline void move(const sf::Vector2f& offset) { sprite.move(offset);}
		inline void rotate(float angle) { sprite.rotate(angle); }
		inline void scale(float factorX, float factorY) { sprite.scale(factorX, factorY);}
		inline void scale(const sf::Vector2f& factor) { sprite.scale(factor); }
		inline const sf::Transform& getTransform() const { return sprite.getTransform();}
		inline const sf::Transform& getInverseTransform() const { return sprite.getInverseTransform();}

	private:
		sf::Sprite sprite;
		sf::Clock clock;
		bool isPlayingVar;
		std::string currentAnim;
		sf::Uint8 animIndex; //the index is between 0 and frames+1, because we'll need an additional iteration to wait for last delay since every frame waits for the delay of the previous frame
		sf::Vector2f currentOffset;
		std::unordered_map<std::string,const animation*> animations;

		void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

	};
}