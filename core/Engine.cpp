#include "Engine.h"

#include "Engine/core/Globals.h"
#include "Engine/core/Window.h"
#include "Engine/core/EventHandler.h"
#include "Engine/event/EventQueue.h"
#include "Engine/core/InputHandler.h"
#include "Engine/core/Renderer.h"
#include "Engine/scene/SceneHandler.h"
#include "Engine/debug/Logger.h"
#include "Engine/debug/Profiler.h"

namespace VEngine
{
	void Engine::submiteGame(Game* game)
	{
		if (clientGame != nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error,"Game class submited more than once", true);
			return;
		}
		if (game == nullptr)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "subnitted Game class is nullptr", true);
			return;
		}

		clientGame = game;

		if (Window::init().getWindow().isOpen() == false)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "Unable to run engine, window hasen't been created, make sure to set window params in the game constructor", true);
			return;
		}

		run();
	}

	Game* Engine::getClientGame()
	{
		if (clientGame == nullptr) Debug::Logger::init().Log(Debug::Logger::Type::warning,"getting client game as a nullptr",true);
		return clientGame;
	}

	void Engine::handleEvent(Event event)
	{
		switch (event.Type)
		{
		case Event::EventType::EngineQuit:
			//handle engine subsystems before quiting
			Window::init().getWindow().close();
			isRunning = false;
			break;
		}
	}

	//private

	Engine::Engine()
	{

	}

	Engine::~Engine()
	{

	}

	void Engine::run()
	{
		Debug::Logger::init().Log(Debug::Logger::Type::info,"Engine initiated successfully, starting the game...",true);
		
		Window::init().getWindow().setKeyRepeatEnabled(false); //TODO: this is temprary while we change the input handler so isKeyPressed doesn't repeat itself
															   //we can do it the old sf::Keyboard::isKeyPressed way, but that would add a little overhead since we would have to check for every key every frame
		isRunning = true;
		clientGame->start();
		
		unsigned int framesPerSecond = 0;

		while (isRunning)
		{
			Global::deltaTime = dtClock.restart().asSeconds();
			framesPerSecond++;
			if (fpsClock.getElapsedTime().asSeconds() >= 1)
			{
				Global::FPS = framesPerSecond;
				
				previousFps[prevFpsIndex] = framesPerSecond;
				if(++prevFpsIndex > 5) prevFpsIndex = 0;
				int prevFpsSum = 0;
				for (int i = 0; i < 5; i++) prevFpsSum += previousFps[i];
				Global::AVERAGE_FPS = prevFpsSum / 5;

				framesPerSecond = 0;
				fpsClock.restart();
			}
			
			InputHandler::init().reset();
			EventHandler::init().handleEvents();

			clientGame->update();
			SceneHandler::init().update();
			EventQueue::init().handleEvents();

			Renderer::init().draw();
		}

		Debug::Profiler::init().logToFile();
		Debug::Logger::init().Log(Debug::Logger::Type::info, "Shuting down the Engine...", true);
	}
}