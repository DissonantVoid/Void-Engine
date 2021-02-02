#include "Renderer.h"

#include "Engine/core/Window.h"
#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"

namespace VEngine
{
	void Renderer::handleEvent(Event event)
	{
		switch (event.Type)
		{
		case Event::EventType::RendererDraw:
			drawables.push(drawData(event.drawEvent.drawable,event.drawEvent.renderState,event.drawEvent.drawLayer));
			break;
		}
	}

	void Renderer::draw()
	{
		VE_PROFILE_FUNC;
		window->clear();

		while (!drawables.empty())
		{
			if (drawables.top().drawable == nullptr) Debug::Logger::init().Log(Debug::Logger::Type::warning, "renderer drawable is nullptr", true);
			else window->draw(*drawables.top().drawable, drawables.top().states);
			drawables.pop();
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