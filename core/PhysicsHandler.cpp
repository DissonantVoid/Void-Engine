#include "PhysicsHandler.h"

#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{

	void PhysicsHandler::handleEvent(Event event)
	{
		switch (event.Type)
		{
		case Event::EventType::EnginePhysicsCollision:
			colliders.push_back(std::move(event.physicsCollisionEvent));
			break;
		}
	}

	void PhysicsHandler::update()
	{
		VE_PROFILE_FUNC;
		sf::Vector2f mousePos = inputCache->getMouseViewPos();

		for (size_t i = 0; i < colliders.size(); i++)
		{
			for (size_t j = i + 1; j < colliders.size(); j++)
			{
				if (colliders[i].thisEnttName == colliders[j].thisEnttName) continue;

				const sf::Vector2f posAndSizeI = colliders[i].position + static_cast<sf::Vector2f>(colliders[i].size);
				const sf::Vector2f posAndSizeJ = colliders[j].position + static_cast<sf::Vector2f>(colliders[j].size);

				if (((colliders[i].position.x > colliders[j].position.x && colliders[i].position.x < posAndSizeJ.x) || //collision ((a.x is between b.x and b.width) or (a.width is between b.x and b.width)) and same thing for y
					(posAndSizeI.x > colliders[j].position.x && posAndSizeI.x < posAndSizeJ.x)) &&
					((colliders[i].position.y > colliders[j].position.y && colliders[i].position.y < posAndSizeJ.y) ||
					(posAndSizeI.y > colliders[j].position.y && posAndSizeI.y < posAndSizeJ.y)))
				{
					Event event1(Event::EventType::PhysicsCollision);
					event1.physicsCollisionEvent = colliders[i];
					event1.physicsCollisionEvent.otherEnttName = colliders[j].thisEnttName;
					event1.submite();

					Event event2(Event::EventType::PhysicsCollision);
					event2.physicsCollisionEvent = colliders[j];
					event2.physicsCollisionEvent.otherEnttName = colliders[i].thisEnttName;
					event2.submite();

				}

			}
			//OPTIMIZATION: consider a function disableMouseCollision() in colliders, maybe ignoreEntity() too
			if (mousePos.x > colliders[i].position.x && // mouse collision
				mousePos.x < colliders[i].position.x + colliders[i].size.x &&
				mousePos.y > colliders[i].position.y &&
				mousePos.y < colliders[i].position.y + colliders[i].size.y)
			{
				Event event(Event::EventType::PhysicsMouseCollision);
				event.physicsCollisionEvent = colliders[i];
				event.submite();
			}
		}

		colliders.clear();
	}

	//private
	
	PhysicsHandler::PhysicsHandler()
	{
		inputCache = &InputHandler::init();
	}

	PhysicsHandler::~PhysicsHandler()
	{

	}
}