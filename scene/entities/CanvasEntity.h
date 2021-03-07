#pragma once

#include <unordered_map>
#include "SFML/Graphics.hpp"

#include "Engine/scene/entities/Entity.h"
#include "Engine/debug/Logger.h"

namespace VEngine
{
	class CanvasEntity : public Entity
	{
		struct canvasDrawData
		{
			canvasDrawData(sf::Drawable* drawable, sf::Uint8 drawLayer, bool shouldDraw, sf::RenderStates renderState)
			: drawable(drawable), drawLayer(drawLayer), renderState(renderState), shouldDraw(shouldDraw) {}

			sf::Drawable* drawable = nullptr;
			sf::RenderStates renderState;
			sf::Uint8 drawLayer;
			bool shouldDraw;
		};

	public:
		CanvasEntity();
		~CanvasEntity();

		void start() override;
		void update() override;
		void handleEvent(Event event) override;

		bool addDrawable(const std::string& name,sf::Drawable* drawable,sf::Uint8 drawLayer,bool hide = false,sf::RenderStates states = sf::RenderStates());
		bool removeDrawable(const std::string& name);

		bool isValid(const std::string& name)const;

		template<typename as>
		as* getDrawable(const std::string& name) const
		{
			auto* data = getDrawableData(name);
			if (data == nullptr)
				return nullptr;

			auto* castedData = dynamic_cast<as*>(data->drawable);
			if (castedData == nullptr)
				Debug::Logger::init().Log(Debug::Logger::Type::warning, "canvasEntity couldn't cast Data with name: " + name + " ,into the given type", true);
			
			return castedData;
		}

		canvasDrawData* getDrawableData(const std::string& name) const;

	private:
		std::unordered_map<std::string, canvasDrawData*> drawables;

	};
}