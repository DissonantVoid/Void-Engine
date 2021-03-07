#pragma once

#include "SFML/Graphics.hpp"

namespace VEngine
{
	class Scene;
	class Entity;
	class Collider;
}

namespace VEngine
{
	class Event
	{
		friend class PhysicsHandler;
	private:

		struct engineStruct
		{

		};

		struct drawStruct
		{
			const sf::Drawable* drawable = nullptr;
			sf::RenderStates renderState;
			sf::Uint8 drawLayer;
		};

		struct physicsCollisionStruct
		{
			sf::String thisEnttName;
			sf::Vector2f position;
			sf::Vector2u size;
			
			sf::String otherEnttName;
			sf::Uint8 colliderID;
		};

		struct sfmlStruct
		{
			sf::Event sfEvent;
		};

		struct costumStruct
		{
			sf::String message;
			sf::Uint16 bitsData;
		};

	public:
		enum class EventType
		{
			EngineQuit,
			EngineRendererDraw, EngineRendererDrawUI,
			EnginePhysicsCollision,
			PhysicsCollision, PhysicsMouseCollision,
			SFML,
			Costum
		}Type;

		engineStruct engineEvent;
		drawStruct drawEvent;
		physicsCollisionStruct physicsCollisionEvent;
		sfmlStruct sfmlEvent;
		costumStruct costumEvent;

		Event(EventType type);
	
		void submite();
	};
}