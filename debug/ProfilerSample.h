#pragma once

#include <string>
#include "SFML/System/Clock.hpp"
#include "Engine/Config.h"

#if defined (VE_PROFILER)
	#define VE_PROFILE_FUNC VEngine::Debug::ProfilerSample p(__FUNCTION__) //in release mode __function__ may or may not work acording to the value of [c/c++\general\Debug Information Format] if /ZI (edit and continue) is selected it will work, but if /Zi is selected instead the replacement wont work
#else
	#define VE_PROFILE_FUNC
#endif

namespace VEngine
{
	namespace Debug
	{
		class ProfilerSample
		{
		public:
			ProfilerSample(std::string functionName);
			~ProfilerSample();

		private:
			sf::Clock clock;
			std::string funcName;
			bool repeated;
		};
	}
}