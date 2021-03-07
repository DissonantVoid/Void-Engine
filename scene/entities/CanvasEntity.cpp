#include "CanvasEntity.h"

#include "Engine/debug/Logger.h"

namespace VEngine
{
	CanvasEntity::CanvasEntity()
	{

	}

	CanvasEntity::~CanvasEntity()
	{
		for (auto& drawable : drawables)
		{
			delete drawable.second->drawable;
			delete drawable.second;
		}
	}

	void CanvasEntity::start()
	{

	}

	void CanvasEntity::update()
	{
		for (auto& drawable : drawables)
		{
			if (drawable.second->shouldDraw == true)
			{
				Event event(Event::EventType::EngineRendererDraw);
				event.drawEvent.drawable = drawable.second->drawable;
				event.drawEvent.drawLayer = drawable.second->drawLayer;
				event.drawEvent.renderState = drawable.second->renderState;
				event.submite();
			}
		}
	}

	void CanvasEntity::handleEvent(Event event)
	{

	}

	bool CanvasEntity::addDrawable(const std::string& name, sf::Drawable* drawable, sf::Uint8 drawLayer, bool hide, sf::RenderStates states)
	{
		if (drawable == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "canvasEntity couldn't add drawable with name: " + name + " ,it is nullptr " , true);
			return false;
		}

		if (drawables.find(name) != drawables.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "canvasEntity couldn't add drawable with name: " + name + " ,name already exist (drawable is now deleted)", true);
			delete drawable;
			return false;
		}

		canvasDrawData* data = new canvasDrawData(drawable,drawLayer,(!hide),states);
		drawables.emplace(std::make_pair(name,data));
		return true;
	}

	bool CanvasEntity::removeDrawable(const std::string& name)
	{
		auto result = drawables.find(name);
		if (result == drawables.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "canvasEntity couldn't remove drawable with name: " + name + " ,name doesn't exist", true);
			return false;
		}

		delete drawables.at(result->first);
		delete drawables.at(result->first)->drawable;
		drawables.erase(result);
		return true;
	}

	bool CanvasEntity::isValid(const std::string& name)const
	{
		return (drawables.find(name) != drawables.end());
	}

	CanvasEntity::canvasDrawData* CanvasEntity::getDrawableData(const std::string& name) const
	{
		auto result = drawables.find(name);
		if (result == drawables.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "canvasEntity couldn't get drawable Data with name: " + name + " ,name doesn't exist", true);
			return nullptr;
		}

		return result->second;
	}

	//private
}