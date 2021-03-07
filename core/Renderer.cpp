#include "Renderer.h"

#include "Engine/core/Window.h"
#include "Engine/debug/Logger.h"
#include "Engine/scene/SceneHandler.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	void Renderer::handleEvent(Event event)
	{
		switch (event.Type)
		{
		case Event::EventType::EngineRendererDraw:
			drawables.push(drawData(event.drawEvent.drawable,event.drawEvent.renderState,event.drawEvent.drawLayer));
			break;
		case Event::EventType::EngineRendererDrawUI:
			UIdrawables.push(drawData(event.drawEvent.drawable, event.drawEvent.renderState, event.drawEvent.drawLayer));
			break;
		}
	}

	void Renderer::draw() //layer 255 should be reserved for debug drawings
	{
		VE_PROFILE_FUNC;
		window->clear();

		while (!drawables.empty())
		{
			if (drawables.top().drawable == nullptr) Debug::Logger::init().Log(Debug::Logger::Type::warning, "renderer drawable is nullptr", true);
			else window->draw(*drawables.top().drawable, drawables.top().states);
			
			drawables.pop();
		}

		window->setView(window->getDefaultView());

		while (!UIdrawables.empty())
		{
			if (UIdrawables.top().drawable == nullptr) Debug::Logger::init().Log(Debug::Logger::Type::warning, "renderer UIdrawable is nullptr", true);
			else window->draw(*UIdrawables.top().drawable, UIdrawables.top().states);

			UIdrawables.pop();
		}

		Scene* currentScene = SceneHandler::init().getCurrentScene();
		if (currentScene != nullptr)
		{
			window->setView(currentScene->getView());
		}
		
		window->display();
	}

	//private

	Renderer::Renderer()
	{
		window = &Window::init().getWindow();
	}

	Renderer::~Renderer()
	{

	}
}