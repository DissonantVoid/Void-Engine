#include "Event.h"

#include "Engine/event/EventQueue.h"

namespace VEngine
{
	Event::Event()
	{

	}

	Event::Event(EventType type)
		: Type(type)
	{

	}

	void Event::submite()
	{
		EventQueue::init().pushEvent(*this);
	}

	//private
}