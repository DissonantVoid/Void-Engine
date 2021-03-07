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

		void scaleTime(float scale);
		void setTargetFramerate(sf::Uint8 FPS);
		void unsetTargetFramerate();

	private:
		Game* clientGame = nullptr;
		bool isRunning;

		sf::Clock dtClock;
		sf::Clock fpsClock;
		unsigned int previousFps[5];
		unsigned int prevFpsIndex = 0;
		float timeScale = 1;
		sf::Uint8 targetFramerate;
		bool isTargetFPSSet;

		Engine();
		~Engine();

		void run();
	};
}