#pragma once

#include "Engine/Config.h"
#include "Engine/core/Game.h"

#include "SFML/System.hpp"

namespace VEngine
{
	class Engine
	{
	public:
		static Engine& init() { static Engine instance; return instance;}

		void submiteGame(Game* game);
		Game* getClientGame();
		void handleEvent(Event event);

	private:
		Game* clientGame = nullptr;
		bool isRunning;

		sf::Clock dtClock;
		sf::Clock fpsClock;
		unsigned int previousFps[5];
		unsigned int prevFpsIndex = 0;

		Engine();
		~Engine();

		void run();
	};
}