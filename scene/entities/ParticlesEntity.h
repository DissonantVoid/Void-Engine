#pragma once

#include "SFML/Graphics.hpp"
#include "Engine/scene/entities/Entity.h"
#include "Engine/resources/AnimationHandler.h"

namespace VEngine
{
	class ParticlesEntity : public sf::Transformable ,public Entity
	{
		struct particle
		{
			particle(sf::Texture* texture): isStatic(true) {};
			particle(Resources::animation* animation): isStatic(false) {};

			void update();

			sf::Vector2f direction;
			float speed;
			float lifeTime;
			sf::Clock animationClock;
			sf::Clock lifeClock;
			bool isStatic;
			sf::Sprite sprite;
			sf::Texture* texture;
			Resources::animation* animation;
		};

	public:

		enum class emitionType
		{
			directional,
			circular,
			cone
		};

		ParticlesEntity();

		~ParticlesEntity();

		void setParticles(const sf::Texture* texture);
		void setParticles(const Resources::animation* animation);

		void setSpeed(float speed);
		void setSpeed(float min, float max);
		void setLifeTime(float lifeTime);
		void setLifeTime(float min, float max);
		void setOffset(float x,float y);
		void setEmitionType(emitionType type);
		void setEmitionDir(float x, float y); //this work with directional and cone types

		bool isAnimated();
		void imit(sf::Uint32 amount); //don't clear particles here

		void start() override;
		void update() override;// don't forget the position
		void handleEvent(Event event) override;

	private:
		//TODO: support for multiple textures/animations randomly assigned
		//what if the texture is changed while some particles are still using it ?
		std::vector<particle> particles;
		const sf::Texture* texture;
		const Resources::animation* animation;
		
		bool isSpeedRange;
		float speedMin;
		float speedMax;
		
		bool isLifeRange;
		float lifeTimeMin;
		float lifeTimeMax;

		sf::Vector2f offset; //additional x,y offset which is add to the direction randomly between 0.xy and offset.xy, can be used for example in straight direction mode to add randomization
		emitionType currentEmType;
		sf::Vector2f direction;
	};
}