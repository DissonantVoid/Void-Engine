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
				{
					animIndex = 0;
				}
				else
				{
					isPlayingVar = false;
				}
				sprite.move(-currentOffset);
				currentOffset = sf::Vector2f(0,0);
				return;
			}

			sprite.setTexture(*animations[currentAnim]->frames[animIndex].texture,true);
			
			sprite.move(-currentOffset);
			currentOffset = animations[currentAnim]->frames[animIndex].offset;
			sprite.move(currentOffset);
			
			animIndex++;
			clock.restart();
		}
	}

	bool AnimSprite::addAnimation(const std::string& name,const animation* animation)
	{
		if (animations.find(name) != animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error,"couldn't add animation with name: " + name + " ,name already exist",true);
			return false;
		}
		
		animations.emplace(std::make_pair(name,animation));
		return true;
	}

	bool AnimSprite::removeAnimation(const std::string& name)
	{
		auto result = animations.find(name);
		if (result == animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't remove animation with name: " + name + " ,name doesn't exist", true);
			return false;
		}

		if (currentAnim == name)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't remove animation with name: " + name + " ,it is the current animation", true);
			return false;
		}

		delete result->second;
		animations.erase(result->first);
		return true;
	}

	bool AnimSprite::isValidAnim(const std::string& name) const
	{
		return (animations.find(name) != animations.end());
	}

	const animation* AnimSprite::getAnim(const std::string& name)
	{
		auto result = animations.find(name);
		if (result == animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't get animation with name: " + name + " ,name doesn't exist", true);
			return nullptr;
		}

		return result->second;
	}

	const sf::Sprite* AnimSprite::getSprite() const
	{
		return &sprite;
	}

	void AnimSprite::playAnim(const std::string& name, bool forcePlay)
	{
		if (animations.find(name) == animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't play animation with name: " + name + " ,name doesn't exist", true);
			return;
		}

		if (forcePlay == false && currentAnim == name)
		{
			return;
		}

		if (!currentAnim.empty())
			stopAnim();

		currentAnim = name;
		isPlayingVar = true;
		clock.restart();
	}

	std::string AnimSprite::getCurrentAnim() const
	{
		return currentAnim;
	}

	sf::Uint16 AnimSprite::getCurrentFrameIndex() const
	{
		return animIndex;
	}

	sf::FloatRect AnimSprite::getLocalBounds() const
	{
		sf::Vector2u size(0,0);
		if (sprite.getTexture() != nullptr)
			size = sprite.getTexture()->getSize();

		return sf::FloatRect(0,0,size.x,size.y);
	}

	sf::FloatRect AnimSprite::getGlobalBounds() const
	{
		return sprite.getTransform().transformRect(getLocalBounds());
	}

	bool AnimSprite::isPlaying() const
	{
		return isPlayingVar;
	}

	void AnimSprite::stopAnim()
	{
		currentAnim.clear();
		isPlayingVar = false;
		sprite.move(-currentOffset);
		currentOffset = sf::Vector2f(0,0);
		animIndex = 0;
	}

	//private

	void AnimSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(sprite,states);
	}
}