#pragma once

#include <string>

#include "Engine/event/Event.h"

namespace VEngine
{
	class Scene;

	class Entity
	{
		friend class Scene;
	public:
		Entity() {};
		virtual ~Entity() {};

		virtual void start() = 0;
		virtual void update() = 0;
		virtual void handleEvent(Event event) = 0;

		const std::string& getName() { return name; }

	protected:
		Scene* parentScene;
		std::string name;
	};
}