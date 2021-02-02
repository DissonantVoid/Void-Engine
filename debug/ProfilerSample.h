#pragma once

#include <string>
#include "SFML/System/Clock.hpp"
#include "Engine/Config.h"

#if (VE_PROFILER == true) && ((VE_DEBUG == true) || (VE_DEBUG == false && VE_PROFILER_DEBUG_ONLY == false))
	#define VE_PROFILE_FUNC VEngine::Debug::ProfilerSample p(__FUNCTION__,true) //in release mode __function__ may or may not work acording to the value of [c/c++\general\Debug Information Format] if /ZI (edit and continue) is selected it will work, but if /Zi is selected instead the replacement wont work
	#define VE_PROFILE_FUNC_ONCE VEngine::Debug::ProfilerSample p(__FUNCTION__,false)
#else
	#define VE_PROFILE_FUNC
	#define VE_PROFILE_FUNC_ONCE
#endif

namespace VEngine
{
	namespace Debug
	{
		class ProfilerSample
		{
		public:
			ProfilerSample(std::string functionName,bool repeated);
			~ProfilerSample();

		private:
			sf::Clock clock;
			std::string funcName;
			bool repeated;
		};
	}
}