#pragma once

#include "Config.h"

#include "Engine/core/Engine.h"
#include "Engine/core/Globals.h"
#include "Engine/core/Game.h"
#include "Engine/core/Window.h"
#include "Engine/core/Renderer.h"
#include "Engine/core/EventHandler.h"
#include "Engine/core/InputHandler.h"

#include "Engine/debug/Logger.h"
#include "Engine/debug/Profiler.h"
#include "Engine/debug/ProfilerSample.h"

#include "Engine/resources/TextureHandler.h"
#include "Engine/resources/FontHandler.h"
#include "Engine/resources/AudioHandler.h"
#include "Engine/resources/AnimationHandler.h"
#include "Engine/resources/ShaderHandler.h"

#include "Engine/resources/SFML Extensions/AnimSprite.h"

#include "event/Event.h"
#include "event/EventQueue.h"

#include "scene/SceneHandler.h"
#include "scene/Scene.h"

#include "scene/entities/Entity.h"
#include "scene/entities/AnimatorEntity.h"
#include "scene/entities/AudioEntity.h"
#include "scene/entities/CanvasEntity.h"
#include "scene/entities/ParticlesEntity.h"
#include "scene/entities/TileMapEntity.h"

#include "Engine/util/Utility.h"
#include "Engine/util/Random.h"