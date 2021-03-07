#pragma once

#include <string>

namespace VEngine
{
	struct animation;
}

namespace VEngine
{
	namespace Util
	{
		bool ParseFileAnimation(std::string path, animation* animation);

		//save and load scene
	}
}