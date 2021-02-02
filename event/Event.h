#pragma once

#include "SFML/Graphics.hpp"

class Scene;

namespace VEngine
{
	class Event
	{
	private:

		struct engineStruct
		{

		};

		struct drawStruct
		{
			sf::Drawable* drawable = nullptr;
			sf::RenderStates renderState;
			sf::Uint8 drawLayer;
		};

		struct sfmlStruct
		{
			sf::Event sfEvent;
		};

		struct costumStruct
		{
			std::string message;
			sf::Uint64 bitsData;
		};

	public:
		enum class EventType
		{
			EngineQuit,
			RendererDraw,
			SFML,
			Costum
		}Type;

		engineStruct engineEvent;
		drawStruct drawEvent;
		sfmlStruct sfmlEvent;
		costumStruct costumEvent;

		Event();
		Event(EventType type);
	
		void submite();
	};
}