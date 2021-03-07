#include "Collider.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"
#include "Engine/event/Event.h"

namespace VEngine
{
	bool Collider::s_showCollider = false;
	sf::Color Collider::s_color = sf::Color::White;
	float Collider::s_outlineThickness = 5;
}

namespace VEngine
{
	Collider::Collider()
	{
		colliderBox.setFillColor(sf::Color(0, 0, 0, 0)); //NOTE: the changes only apply to colliders that were initiated after showCollider() has been called
		colliderBox.setOutlineColor(s_color);
		colliderBox.setOutlineThickness(s_outlineThickness);
	}

	Collider::~Collider()
	{

	}

	void Collider::setPositionOffset(sf::Vector2f position)
	{
		if (isBound)
			posOffset = position;
		else
			posOffset += position; //in case of no bound, we won't have a sprite::position to add the offset to later so instead of adding a position variable for that, we use the offset to store the position and the offset
	}

	void Collider::setSizeOffset(sf::Vector2u size)
	{
		if (isBound)
			sizeOffset = size;
		else
			sizeOffset += size;
	}

	void Collider::set(const Entity* entity, const sf::Sprite* sprite, sf::Uint8 ID)
	{
		reset();

		this->entity = entity;
		this->sprite = sprite;
		this->ID = ID;
		isBound = true;
	}

	void Collider::set(const Entity* entity, sf::Vector2f position, sf::Vector2u size, sf::Uint8 ID)
	{
		reset();

		this->entity = entity;
		this->ID = ID;
		posOffset = position;
		sizeOffset = size;
		isBound = false;
	}

	void Collider::update()
	{
		VE_PROFILE_FUNC;
		if (entity != nullptr)
		{
			sf::Vector2f position = sf::Vector2f((isBound == true ? sprite->getPosition() + posOffset  : posOffset));
			sf::Vector2u size = sf::Vector2u((isBound == true ? sf::Vector2u(sprite->getLocalBounds().width,sprite->getLocalBounds().height) + sizeOffset  : sizeOffset));

			Event event(Event::EventType::EnginePhysicsCollision);
			event.physicsCollisionEvent.thisEnttName = entity->getName();
			event.physicsCollisionEvent.position = position;
			event.physicsCollisionEvent.size = size;
			event.physicsCollisionEvent.colliderID = ID;
			event.submite();

			//Show Collider
			if (s_showCollider == false) return;

			colliderBox.setPosition(position);
			colliderBox.setSize((sf::Vector2f)size);

			Event drawEvent(Event::EventType::EngineRendererDraw);
			drawEvent.drawEvent.drawable = &colliderBox;
			drawEvent.drawEvent.drawLayer = 255;
			drawEvent.submite();

		}
	}

	void Collider::showColliders(sf::Uint8 layer, sf::Color color, float outlineThickness)
	{
		s_color = color;
		s_outlineThickness = outlineThickness;
		s_showCollider = true;
	}
	
	void Collider::hideColliders()
	{
		s_showCollider = false;
	}

	//private

	void Collider::reset()
	{
		entity = nullptr;
		sprite = nullptr;
		ID = 0;
		posOffset = sf::Vector2f(0,0);
		sizeOffset = sf::Vector2u(0,0);
	}

}