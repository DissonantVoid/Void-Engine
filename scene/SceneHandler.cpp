#include "SceneHandler.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/ProfilerSample.h"
#include "Engine/core/Window.h"

#include "Engine/Config.h"

namespace VEngine
{
	void SceneHandler::update()
	{
		VE_PROFILE_FUNC;
		if (currentScene != nullptr)
		{
			currentScene->update();
			window->setView(currentScene->view);
		}
	}

	bool SceneHandler::pushScene(std::string name, Scene* scene)
	{
		VE_PROFILE_FUNC;
		if (scenes.find(name) != scenes.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error,"couldn't push scene with name: " + name + " ,name already exist (scene in now deleted)",true);
			delete scene;
			return false;
		}

		scene->name = name;
		scenes.emplace(std::make_pair(name,scene));
		return true;
	}
	
	Scene* SceneHandler::getScene(std::string name)
	{
		VE_PROFILE_FUNC;
		auto result = scenes.find(name);
		if (result != scenes.end())
			return result->second;

		Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't get scene with name: " + name + " ,it doesn't exist ", true);
		return nullptr;
	}

	Scene* SceneHandler::getCurrentScene()
	{
		VE_PROFILE_FUNC;
		if (currentScene != nullptr)
			return currentScene;

		Debug::Logger::init().Log(Debug::Logger::Type::warning, "couldn't get currentScene ,it is a nullptr", true);
		return nullptr;
	}

	bool SceneHandler::isScene(std::string name)const
	{
		return (scenes.find(name) != scenes.end());
	}

	bool SceneHandler::isCurrentScene(std::string name)const
	{
		if (currentScene == nullptr) return false;
		return (scenes.find(name)->second == currentScene);
	}

	bool SceneHandler::removeScene(std::string name)
	{
		VE_PROFILE_FUNC;
		auto result = scenes.find(name);
		if (result == scenes.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't remove scene with name: " + name + " ,it doesn't exist ", true);
			return false;
		}

		if (currentScene != nullptr && result->second == currentScene)
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't remove scene with name: " + name + " ,it is the current scene ", true);
			return false;
		}

		delete result->second;
		scenes.erase(name);
		return true;
	}

	bool SceneHandler::switchScene(std::string name)
	{
		VE_PROFILE_FUNC;
		auto result = scenes.find(name);
		if (result == scenes.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't switch to scene with name: " + name + " ,it doesn't exist ", true);
			return false;
		}
		
		if(currentScene != nullptr) currentScene->onDetach();
		currentScene = result->second;
		window->setView(currentScene->view);
		if (currentScene->startFuncCalled == false)
		{
			currentScene->startFuncCalled = true;
			currentScene->start();
		}
		else currentScene->onAttach();

		return true;
	}

	//private

	SceneHandler::SceneHandler()
	{
		window = &Window::init().getWindow();
	}

	SceneHandler::~SceneHandler()
	{
		VE_PROFILE_FUNC;
		for (std::unordered_map<std::string, Scene*>::iterator it = scenes.begin(); it != scenes.end(); it++)
			delete it->second;
	}
}