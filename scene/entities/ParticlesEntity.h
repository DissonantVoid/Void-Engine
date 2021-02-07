#pragma once

#include <map>

#include "SFML/Graphics.hpp"

#include "Engine/scene/entities/Entity.h"
#include "Engine/resources/AnimationHandler.h"

namespace VEngine
{
	class ParticlesEntity : public Entity //TODO seperate particle class into 2 derived classes, one animated and the other not
	{
		struct particle
		{
			particle();
			~particle();

			void setSprite(const sf::Texture* texture);
			void setSprite(const Resources::animation* animation);
			void set(sf::Vector2f position, sf::Vector2f direction, float speed, float lifeTime, sf::Uint8 drawLayer);
			void update();


			sf::Vector2f direction; //between -1 / 1
			float speed;
			float lifeTime;
			sf::Clock lifeClock;
			sf::Uint8 drawLayer;
			bool shouldErase = false;

			sf::Sprite sprite;

			const Resources::animation* animation;
			sf::Clock animationClock;
			unsigned int currentAnimIndex = 0;
			sf::Vector2f currentOffset;
			bool isAnimated;
			bool isAnimFinished = false;
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

		void addTexture(std::string name,const sf::Texture* texture);
		void removeTexture(std::string name);
		void addAnimation(std::string name,const Resources::animation* animation);
		void removeAnimation(std::string name);

		void setAnimated(bool isAnimated);
		void setSpeed(float speed);
		void setSpeed(float min, float max);
		void setLifeTime(float lifeTime);
		void setLifeTime(float min, float max);
		void setOffset(float x,float y);
		void setEmitionType(emitionType type);
		void setEmitionDir(float x, float y); //this work with directional and cone types

		void imit(sf::Uint16 amount,sf::Vector2f position,sf::Uint8 layer);

		void start() override;
		void update() override;
		void handleEvent(Event event) override;

	private:
		std::vector<particle> particles;
		std::map<std::string,const sf::Texture*> textures; // it's fine to not keep a refrence counting or anything like that because we can remove a texture from here even if a particle is using it as long as it's still valid in the resource::textureHandler
		std::map<std::string,const Resources::animation*> animations;
		bool isAnimatedVar;

		bool isSpeedRange;
		float speedMin;
		float speedMax;
		
		bool isLifeRange;
		float lifeTimeMin;
		float lifeTimeMax;

		sf::Vector2f offset; //additional x,y offset which is add to the direction randomly between 0.xy and offset.xy, can be used for example in straight direction mode to add randomization
		emitionType currentEmType = emitionType::directional;
		sf::Vector2f direction; //between -1 / 1
	};
}