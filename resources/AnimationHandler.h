#pragma once

#include <vector>
#include <unordered_map>

#include "SFML/Graphics.hpp"

#include "Engine/resources/SFML Extensions/AnimationData.h"

namespace VEngine
{
	namespace Resources
	{
		class AnimationHandler
		{
		public:
			static AnimationHandler& init() { static AnimationHandler instance; return instance;}

			bool addAnimation(const std::string& name, animation* animation);//should be heap "new" allocated
			bool addAnimation(const std::string& name, bool isLoop, std::vector<animFrame> frames);
			bool addAnimation(const std::string& name,std::string path);
			bool duplicateTexture(const std::string& originalName, const std::string& newName);
			bool isAnimation(const std::string& name)const;
			const animation* getAnimation(const std::string& name)const;
			animation* getAnimationMd(const std::string& name);
			bool removeAnimation(const std::string& name);

		private:
			std::unordered_map<std::string, animation*> animations;

			AnimationHandler();
			~AnimationHandler();
		};
	}
}



