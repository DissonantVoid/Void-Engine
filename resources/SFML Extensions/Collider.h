#pragma once

#include <SFML/Graphics.hpp>
#include "Engine/scene/entities/Entity.h"
#include "Engine/resources/SFML Extensions/AnimSprite.h"

namespace VEngine
{
	class Collider//currently collider only work with sf::sprite and animSprite because transformable does't have a size
	{
		friend class PhysicsHandler;
	public:
		Collider(); //only suport rectangle conllision because sfml doesn't support non perfect circles
		~Collider();

		void set(const Entity* entity, const sf::Sprite* sprite, sf::Uint8 ID);
		void set(const Entity* entity, sf::Vector2f position, sf::Vector2u size, sf::Uint8 ID);
		void update();
		
		void setPositionOffset(sf::Vector2f position);
		void setSizeOffset(sf::Vector2u size);

		static void showColliders(sf::Uint8 layer, sf::Color color, float outlineThickness);
		static void hideColliders();

	private:
		const Entity* entity = nullptr;
		const sf::Sprite* sprite = nullptr;

		sf::Uint8 ID;
		bool isBound; // is the collider bound to a sprite ?
		sf::Vector2f posOffset;
		sf::Vector2u sizeOffset;

		static bool s_showCollider;
		static sf::Color s_color;
		static float s_outlineThickness;
		sf::RectangleShape colliderBox;

		void reset();

	};
}