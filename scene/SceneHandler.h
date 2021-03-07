#pragma once

#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "Scene.h"

namespace VEngine
{
	class SceneHandler
	{
	public:
		static SceneHandler& init() { static SceneHandler instance ;return instance;}

		void update();

		bool pushScene(std::string name,Scene* scene); //NOTE: the pointer must be heap allocated + is cleaned automaticaly in case of failure
		Scene* getScene(std::string name);
		Scene* getCurrentScene();
		bool isScene(std::string name)const;
		bool isCurrentScene(std::string name)const;
		bool removeScene(std::string name);
		bool switchScene(std::string name);
		
	private:
		std::unordered_map<std::string,Scene*> scenes;
		Scene* currentScene = nullptr;
		sf::RenderWindow* window;
		
		SceneHandler();
		~SceneHandler();
	};
}
