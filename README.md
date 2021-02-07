# Void-Engine
Void Engine is a simple 2d game engine built on top of SFML as a personal project

# DISCLAMER: 
This is a project made by a person who barely has a year and a half of experience with game development and coding in general, it is not recommended as a learning material as it may contain bad coding habbits and unorganized code

# How To Use: 
include all the engine files inside a folder with name "Engine", also make sure that SFML files are added to the project's additional include directories.
the first step to use the engine for your game is to make a class that inherites from the VEngine::Game class,
make sure to override the start, update, and handleEvent functions.
and set the window properties in the bass class constructor. the file VoidEngine.h will contain all the files in the engine but feel free to include what you need directly from the engine files.

the next step is to create a scene. the engine is designed so everything in the game is inside a scene structure, so you can make multiple scenes to represent different game levels for exampls. just make sure your scene inherites from VEngine::Scene as a base class, and override the start, update, onAttach, onDetach, and handleEvent functions.

then push the scene to the sceneHandler by calling SceneHandler::init().pushScene() with your scene and a given name. and make sure you call SceneHandler::init().switchScene() after that with the name of your first scene to activate it.
one important thing to keep in mind is that every scene have functions to add/get/remove entities that you can call to control scene entities, we will talk about entities in a moment but for now keep in mind that you'll have to call the start function of every entity in your scene's start function, and update all entities in your scene's update function

an entity is a representation of a game object and it could be anything for the player to GUI to a simple hitBox, but first your entity have to inherite from the VEngine::Entity base class and override the start, update, and hanleEvent functions. there are however some built in entities for common use that should be helpful like the particleEntity
and the CanvasEntity
