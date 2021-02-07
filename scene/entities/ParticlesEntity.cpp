#include "ParticlesEntity.h"

#include "Engine/debug/Logger.h"
#include "Engine/core/Globals.h"
#include "Engine/util/Random.h"

namespace VEngine
{
	ParticlesEntity::particle::particle()
	{

	}

	ParticlesEntity::particle::~particle()
	{

	}

	void ParticlesEntity::particle::setSprite(const sf::Texture* texture)
	{
		isAnimated = false;
		this->sprite.setTexture(*texture);
	}
	
	void ParticlesEntity::particle::setSprite(const Resources::animation* animation)
	{
		isAnimated = true;
		this->animation = animation;
	}

	void ParticlesEntity::particle::set(sf::Vector2f position, sf::Vector2f direction, float speed, float lifeTime, sf::Uint8 drawLayer)
	{
		this->direction = direction;
		this->speed = speed;
		this->lifeTime = lifeTime;
		this->drawLayer = drawLayer;

		sprite.setPosition(position);

		animationClock.restart();
		lifeClock.restart();
	}

	void ParticlesEntity::particle::update()
	{
		if (shouldErase == false && lifeClock.getElapsedTime().asSeconds() >= lifeTime)
			shouldErase = true;

		sprite.move(direction * speed * Global::deltaTime);

		if (isAnimated && !isAnimFinished &&
			[&]() -> bool
		{
			if(currentAnimIndex == 0) return true;
			if(animationClock.getElapsedTime().asSeconds() >= animation->frames[currentAnimIndex - 1].delay) return true;
			return false;
		}())

		{
			if (currentAnimIndex >= animation->frames.size())
			{
				if (animation->isLoop)
					currentAnimIndex = 0;
				else
				{
					sprite.setPosition(-currentOffset);
					currentOffset = sf::Vector2f(0,0);
					isAnimFinished = true;
				}
				return;
			}

			sprite.setTexture(*animation->frames[currentAnimIndex].texture, true);
			sprite.move(-currentOffset);
			sprite.move(animation->frames[currentAnimIndex].offset);
			currentOffset = animation->frames[currentAnimIndex].offset;

			currentAnimIndex++;
			animationClock.restart();
		}
	}
}

namespace VEngine
{
	ParticlesEntity::ParticlesEntity()
	{

	}

	ParticlesEntity::~ParticlesEntity()
	{

	}

	void ParticlesEntity::addTexture(std::string name, const sf::Texture* texture)
	{
		if (texture == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't add texture with name: " + name + ", it is nullptr", true);
			return;
		}

		if (textures.find(name) != textures.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error,"couldn't add texture with name: " + name + ", name already exist", true);
			return;
		}

		textures.emplace(std::make_pair(name,texture));
	}

	void ParticlesEntity::removeTexture(std::string name)
	{
		auto result = textures.find(name);
		if (result == textures.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't remove texture with name: " + name + ", name doesn't exist", true);
			return;
		}

		textures.erase(result);

	}

	void ParticlesEntity::addAnimation(std::string name, const Resources::animation* animation)
	{
		if (animation == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't add animation with name: " + name + ", it is nullptr", true);
			return;
		}

		if (animations.find(name) != animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't add animation with name: " + name + ", name already exist", true);
			return;
		}

		animations.emplace(std::make_pair(name, animation));
	}

	void ParticlesEntity::removeAnimation(std::string name)
	{
		auto result = animations.find(name);
		if (result == animations.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't remove animation with name: " + name + ", name doesn't exist", true);
			return;
		}

		animations.erase(result);
	}

	void ParticlesEntity::setAnimated(bool isAnimated)
	{
		isAnimatedVar = isAnimated;
	}

	void ParticlesEntity::setSpeed(float speed)
	{
		isSpeedRange = false;
		speedMin = speed;
	}

	void ParticlesEntity::setSpeed(float min, float max)
	{
		isSpeedRange = true;
		speedMin = min;
		speedMax = max;
	}

	void ParticlesEntity::setLifeTime(float lifeTime)
	{
		isLifeRange = false;
		lifeTimeMin = lifeTime;
	}

	void ParticlesEntity::setLifeTime(float min, float max)
	{
		isLifeRange = true;
		lifeTimeMin = min;
		lifeTimeMax = max;
	}

	void ParticlesEntity::setOffset(float x, float y)
	{
		offset.x = x;
		offset.y = y;
	}

	void ParticlesEntity::setEmitionType(emitionType type)
	{
		currentEmType = type;
	}

	void ParticlesEntity::setEmitionDir(float x, float y) // -1 / 1
	{
		direction.x = x;
		direction.y = y;
	}

	void ParticlesEntity::imit(sf::Uint16 amount, sf::Vector2f position, sf::Uint8 layer)
	{
		//check if there is any textures, or animations acording to the animated variable
		if (particles.size() + amount > 10'000)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error,"couldn't emit particles with amount: " + std::to_string(amount) + " ,maximum amount exceeded",true);
			return;
		}

		for (int i = 0; i < amount; i++)
		{
			particle particle;

			//Drawable
			if (isAnimatedVar == false)
			{
				if (textures.size() == 0)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't emit unanimated particles textures list is empty", true);
					return;
				}

				int index = Util::Random::init().getInt(0,textures.size()-1);
				std::map<std::string, const sf::Texture*>::iterator it = textures.begin();
				for (int i = 0; i < index; i++)
					it++;

				particle.setSprite(textures.at(it->first));
			}
			else
			{
				if (animations.size() == 0)
				{
					Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't emit animated particles animations list is empty", true);
					return;
				}

				int index = Util::Random::init().getInt(0, animations.size() - 1);
				std::map<std::string, const Resources::animation*>::iterator it = animations.begin();
				for (int i = 0; i < index; i++)
					it++;

				particle.setSprite(animations.at(it->first));
			}
			
			//Direction
			float Xdir;
			float Ydir;
			
			switch (currentEmType)
			{
			case emitionType::directional:
				Xdir = direction.x;
				Ydir = direction.y;
				break;
			
			
			case emitionType::circular:
				Xdir = Util::Random::init().getFloat(-1,1);
				Ydir = Util::Random::init().getFloat(-1,1);
				break;
			
			
			case emitionType::cone:
				float coneOffset = 1.f;
				Xdir = direction.x;
				Ydir = direction.y;

				bool rndx = Util::Random::init().getBool();
				if (rndx == true)
					Xdir += Util::Random::init().getFloat(0, coneOffset);
				else
					Xdir -= Util::Random::init().getFloat(0, coneOffset);

				bool rndy = Util::Random::init().getBool();
				if (rndy == true)
					Ydir += Util::Random::init().getFloat(0, coneOffset);
				else
					Ydir -= Util::Random::init().getFloat(0, coneOffset);

				break;
			}

			if (offset.x > 0)
			{
				bool rnd = Util::Random::init().getBool();
				if (rnd == true)
					Xdir += Util::Random::init().getFloat(0, offset.x);
				else 
					Xdir -= Util::Random::init().getFloat(0, offset.x);
			}

			if (offset.y > 0)
			{
				bool rnd = Util::Random::init().getBool();
				if (rnd == true)
					Ydir += Util::Random::init().getFloat(0, offset.y);
				else
					Ydir -= Util::Random::init().getFloat(0, offset.y);
			}

			//Speed
			float spd;

			if (isSpeedRange == false)
				spd = speedMin;
			else
				spd = Util::Random::init().getFloat(speedMin,speedMax);

			//LifeTime
			float lifeT;

			if (isLifeRange == false)
				lifeT = lifeTimeMin;
			else
				lifeT = Util::Random::init().getFloat(lifeTimeMin,lifeTimeMax); 


			particle.set(position,sf::Vector2f(Xdir,Ydir),spd, lifeT,layer);
			particles.push_back(particle);
		}
	}

	void ParticlesEntity::start()
	{

	}

	void ParticlesEntity::update()
	{
		std::vector<particle>::iterator it = particles.begin();
		while (it != particles.end())
		{
			it->update();

			if (it->shouldErase)
				it = particles.erase(it);
			else
			{
				Event event(Event::EventType::RendererDraw);
				event.drawEvent.drawable = &it->sprite;
				event.drawEvent.drawLayer = it->drawLayer;
				event.submite();
				it++;
			}
		}

	}

	void ParticlesEntity::handleEvent(Event event)
	{

	}
}