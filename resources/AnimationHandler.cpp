#include "AnimationHandler.h"

#include "Engine/resources/TextureHandler.h"
#include "Engine/debug/Logger.h"
#include "Engine/util/Parser.h"

#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	namespace Resources
	{
		bool AnimationHandler::addAnimation(std::string name, animation* animation)
		{
			VE_PROFILE_FUNC;

			if (animation == nullptr)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add animation with name: " + name + ", it's nullptr (texture is now deleted)", true);
				delete animation;
				return false;
			}

			if (animations.find(name) != animations.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add animation with name: " + name + ", name already exist (animation is now deleted)", true);
				delete animation;
				return false;
			}
			animations.emplace(std::make_pair(name, animation));
			return true;
		}

		bool AnimationHandler::addAnimation(std::string name, bool isLoop, std::vector<animFrame> frames)
		{
			VE_PROFILE_FUNC;
			if (animations.find(name) != animations.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add animation with name: " + name + ", name already exist", true);
				return false;
			}

			animation* anim = new animation;
			anim->isLoop = isLoop;
			for (int i = 0; i < frames.size(); i++) anim->frames.push_back(frames[i]);

			animations.emplace(std::make_pair(name, anim));
			return true;
		}

		bool AnimationHandler::addAnimation(std::string name, std::string path)
		{
			VE_PROFILE_FUNC;
			if (animations.find(name) != animations.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add animation with name: " + name + ", name already exist", true);
				return false;
			}

			animation* anim = new animation;
			bool parseData = Util::ParseFileAnimation(path, anim);
			if (!parseData)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to add animation with name: " + name + ", parser failed", true);
				delete anim;
				return false;
			}

			animations.emplace(std::make_pair(name, anim));
			return true;
		}

		bool AnimationHandler::duplicateTexture(std::string originalName, std::string newName)
		{
			VE_PROFILE_FUNC;
			if (animations.find(originalName) != animations.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to duplicate animation with names: " + originalName + " - " + newName + ", originalName already exist", true);
				return false;
			}

			if (animations.find(newName) != animations.end())
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to duplicate animation with names: " + originalName + " - " + newName + ", newName already exist", true);
				return false;
			}

			animation* aniamtion = new animation(*animations.find(originalName)->second);
			animations.emplace(std::make_pair(newName, aniamtion));
			return true;
		}

		bool AnimationHandler::isAnimation(std::string name)
		{
			return (animations.find(name) != animations.end());
		}

		const animation* AnimationHandler::getAnimation(std::string name)
		{
			return getAnimationMd(name);
		}

		animation* AnimationHandler::getAnimationMd(std::string name)
		{
			VE_PROFILE_FUNC;
			auto result = animations.find(name);
			if (result != animations.end())
				return result->second;

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to get animation with name: " + name + ", doesn't exist", true);
			return nullptr;
		}

		bool AnimationHandler::removeAnimation(std::string name)
		{
			VE_PROFILE_FUNC;
			if (animations.find(name) != animations.end())
			{
				delete animations.at(name);
				animations.erase(name);
				return true;
			}

			Debug::Logger::init().Log(Debug::Logger::Type::warning, "unable to remove animation with name: " + name + ", doesn't exist", true);
			return false;
		}


		//private

		AnimationHandler::AnimationHandler()
		{

		}

		AnimationHandler::~AnimationHandler()
		{
			VE_PROFILE_FUNC_ONCE;
			for (auto& anim : animations)
				delete anim.second;
		}
	}
}
