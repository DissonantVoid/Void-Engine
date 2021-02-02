#include "EventQueue.h"

#include "Engine/core/Engine.h"
#include "Engine/core/Renderer.h"
#include "Engine/scene/SceneHandler.h"

#include "Engine/debug/ProfilerSample.h"

using EType = VEngine::Event::EventType;

namespace VEngine
{
	void EventQueue::handleEvents()
	{
		VE_PROFILE_FUNC;
		while (!events.empty())
		{
			Event& event = events.front();
			switch(event.Type)
			{
			case EType::EngineQuit:
				Engine::init().handleEvent(event);
				break;
			case EType::RendererDraw:
				Renderer::init().handleEvent(event);
				break;
			case EType::SFML:
				VEngine::Engine::init().getClientGame()->handleEvent(event);
				break;
			case EType::Costum:
				{
					Scene* scene = SceneHandler::init().getCurrentScene();
					if (scene != nullptr)scene->handleEvent(event);
					break;
				}
			}
			
			events.pop();
		}
	}

	//private

	EventQueue::EventQueue()
	{

	}

	EventQueue::~EventQueue()
	{

	}

	void EventQueue::pushEvent(Event event)
	{
		events.push(event);
	}

}