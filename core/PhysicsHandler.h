#pragma once

#include "Engine/resources/SFML Extensions/Collider.h"
#include "Engine/core/InputHandler.h"
#include <vector>

namespace VEngine
{
	class PhysicsHandler
	{
	public:
		static PhysicsHandler& init() { static PhysicsHandler instance; return instance; }
	
		void handleEvent(Event event);
		void update();

	private:
		InputHandler* inputCache;
		std::vector<Event::physicsCollisionStruct> colliders;

		sf::Uint8 CollBoxlayer;
		sf::Color CollBoxcolor;
		float CollBoxOutlineThickness;

		PhysicsHandler();
		~PhysicsHandler();

	};
}