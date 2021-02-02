#pragma once

#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "Engine/core/Globals.h"
#include "Engine/scene/entities/Entity.h"
#include "Engine/debug/Logger.h"
#include "Engine/event/Event.h"

namespace VEngine
{
	class Scene //NOTE: the base class will clean entities
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
			Entity* entity = entities.find(name)->second;
			if (entity == nullptr)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "entity with name: " + name + " doesn't exist in the scene named: " + this->name, true);
				return nullptr;
			}
			if (dynamic_cast<as*>(entity) == nullptr)
			{
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't cast " + this->name + " into the given type, it wasen't originaly of that type", true);
				return nullptr;
			}
			return dynamic_cast<as*>(entity);
		}

		bool removeEntity(std::string name);

	protected:
		std::unordered_map<std::string, Entity*> entities;
		sf::View view;
		std::string name;

	private:
		bool startFuncCalled = false;
	};

}