#include "Scene.h"

#include "Engine/core/Window.h"

namespace VEngine
{
	Scene::Scene()
	{
		VE_PROFILE_FUNC;
		sf::Vector2u windowSize = Window::init().getWindow().getSize();
		view.setSize(windowSize.x, windowSize.y);
		view.setCenter(windowSize.x/2, windowSize.y/2);
	}

	Scene::~Scene()
	{
		for (std::unordered_map<std::string, Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
			delete it->second;
	}

	bool Scene::addEntity(std::string name, Entity* entity) //NOTE: the pointer must be heap allocated + is cleaned automaticaly in case of failure
	{
		VE_PROFILE_FUNC;
		if (entities.find(name) != entities.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't add entity with name: " + name + " ,already exist (the entity pointer is now deleted)", true);
			delete entity;
			return false;
		}

		entity->parentScene = this;
		entity->name = name;
		entities.emplace(std::make_pair(name, entity));
		return true;
	}

	Entity* Scene::getEntity(std::string name)
	{
		VE_PROFILE_FUNC;
		std::unordered_map<std::string, Entity*>::iterator result = entities.find(name);
		if (result == entities.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::warning, "entity with name: " + name + " doesn't exist in the scene named: " + this->name, true);
			return nullptr;
		}

		return result->second;
	}

	sf::View& Scene::getView()
	{
		return view;
	}

	bool Scene::removeEntity(std::string name)
	{
		VE_PROFILE_FUNC;
		std::unordered_map<std::string, Entity*>::iterator result = entities.find(name);

		if (result == entities.end())
		{
			Debug::Logger::init().Log(Debug::Logger::Type::error, "couldn't remove entity with name: " + name + " ,it doesn't exist", true);
			return false;
		}
		delete result->second;
		entities.erase(name);
		return true;
	}

	//private
}