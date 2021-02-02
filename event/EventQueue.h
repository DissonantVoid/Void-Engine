#pragma once

#include "Engine/event/Event.h"
#include <queue>

namespace VEngine
{
	class EventQueue
	{
		friend class Event;
	public:
		static EventQueue& init() { static EventQueue instance; return instance;}

		void handleEvents();

	private:
		std::queue<Event> events;

		EventQueue();
		~EventQueue();

		void pushEvent(Event event);
	};
}