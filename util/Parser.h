#pragma once

#include <string>

namespace VEngine::Resources
{
	struct animation;
}

namespace VEngine
{
	namespace Util
	{
		bool ParseFileAnimation(std::string path, Resources::animation* animation);

		//save and load scene
	}
}