#pragma once

#include <vector>
#include <unordered_map>

#include "SFML/Graphics.hpp"

namespace VEngine
{
	namespace Resources
	{
		struct animFrame
		{
			sf::Texture *texture;
			float delay;
			sf::Vector2f offset; //in case of texture being bigger/smaller than others and need to be adjusted
		};

		struct animation
		{
			bool isLoop;
			std::vector<animFrame> frames;
		};

		class AnimationHandler
		{
		public:
			static AnimationHandler& init() { static AnimationHandler instance; return instance;}

			bool addAnimation(std::string name, animation* animation);//should be heap "new" allocated
			bool addAnimation(std::string name, bool isLoop, std::vector<animFrame> frames);
			bool addAnimation(std::string name,std::string path);
			bool isAnimation(std::string name);
			const animation* getAnimation(std::string name);
			animation* getAnimationMd(std::string name);
			bool removeAnimation(std::string name);

		private:

			std::unordered_map<std::string, animation*> animations;

			AnimationHandler();
			~AnimationHandler();
		};
	}
}



