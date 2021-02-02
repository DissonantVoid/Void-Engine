#include "AnimSprite.h"

#include "Engine/debug/Logger.h"

namespace VEngine
{
	AnimSprite::AnimSprite()
	{
		
	}

	AnimSprite::~AnimSprite()
	{

	}

	void AnimSprite::update()
	{
		if (isPlayingVar == false)
			return;

		if (animIndex == 0 || clock.getElapsedTime().asSeconds() >= animations[currentAnim]->frames[animIndex - 1].delay)//if first frame we ignore the delay, otherwise we use the delay of last fram since every frame has delay before next fram
		{
			if (animIndex >= animations[currentAnim]->frames.size())
			{
				if (animations[currentAnim]->isLoop)
					animIndex = 0;
				else
				{
					isPlayingVar = false;
					sprite.setPosition(0, 0);
				}
				return;
			}

			sprite.setTexture(*animations[currentAnim]->frames[animIndex].texture,true);
			
			sprite.setPosition(0,0);//sprite transform shouldn't be changed since we feed our transform to the draw function which will be set to the sprite, but since after applying offset this.transform we wont be able to go back, it makes sense to add the offset to the sprite and remove it when the frame is over aka next frame
			sprite.move(animations[currentAnim]->frames[animIndex].offset);
			
			animIndex++;
			clock.restart();
		}
	}

	bool AnimSprite::addAnimation(std::string name,Resources::animation* animation)
	{
		if (animations.find(name) != animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning,"couldn't add animation with name: " + name + " ,name already exist (anim is now deleted)",true);
			delete animation;
			return false;
		}
		
		animations.emplace(std::make_pair(name,animation));
		return true;
	}

	bool AnimSprite::removeAnimation(std::string name)
	{
		auto result = animations.find(name);
		if (result == animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't remove animation with name: " + name + " ,name doesn't exist", true);
			return false;
		}

		if (currentAnim == name)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't remove animation with name: " + name + " ,it is the current animation", true);
			return false;
		}

		delete result->second;
		animations.erase(result->first);
		return true;
	}

	bool AnimSprite::isValidAnim(std::string name)
	{
		return (animations.find(name) != animations.end());
	}

	Resources::animation* AnimSprite::getAnim(std::string name)
	{
		auto result = animations.find(name);
		if (result == animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't get animation with name: " + name + " ,name doesn't exist", true);
			return nullptr;
		}

		return result->second;
	}

	void AnimSprite::playAnim(std::string name)
	{
		if (animations.find(name) == animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't play animation with name: " + name + " ,name doesn't exist", true);
			return;
		}

		if (!currentAnim.empty())
			stopAnim();

		currentAnim = name;
		isPlayingVar = true;
		clock.restart();
	}

	std::string AnimSprite::getCurrentAnim()
	{
		return currentAnim;
	}

	bool AnimSprite::isPlaying()
	{
		return isPlayingVar;
	}

	void AnimSprite::stopAnim()
	{
		//TODO: the sprite is not changed so it will still have the texture from the last frame of previous animation, this can cause problems if last animation was deleted right after
		//we can just set texture to null since sprite::draw() checks for texture validity before drawing
		sprite.setTexture(sf::Texture()); // but this is expensive
		currentAnim.clear();
		isPlayingVar = false;
		animIndex = 0;
	}

	//private

	void AnimSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		target.draw(sprite,states);
	}
}