#pragma once

#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "Engine/core/Globals.h"
#include "Engine/debug/ProfilerSample.h"
#include "Engine/scene/entities/Entity.h"
#include "Engine/debug/Logger.h"
#include "Engine/event/Event.h"

namespace VEngine
{
	class Scene : public sf::NonCopyable
	{
		friend class SceneHandler;
	public:
		Scene();
		virtual ~Scene();

		virtual void start() = 0;
		virtual void update() = 0;

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void handleEvent(Event event) = 0;

		bool addEntity(std::string name, Entity* entity); //NOTE: the pointer must be heap allocated + is cleaned automaticaly in case of failure
		
		template<typename as>
		as* getEntity(std::string name)
		{
			VE_PROFILE_FUNC;
			
			Entity* entity = getEntity(name);
			if (entity == nullptr) return nullptr;

			as* castedEntity = dynamic_cast<as*>(entity);
			if (castedEntity != nullptr)
			{
				return castedEntity;
			}
			else
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't cast " + this->name + " into the given type, it isn't of that type", true);
				return nullptr;
			}
			
		}
		Entity* getEntity(std::string name);
		bool removeEntity(std::string name);

		sf::View& getView();

	protected:
		std::unordered_map<std::string, Entity*> entities;
		sf::View view;
		std::string name;

	private:
		bool startFuncCalled = false;
	};

}