#include "ProfilerSample.h"

#include "Engine/Config.h"
#include "Engine/debug/Profiler.h"

namespace VEngine
{
	namespace Debug
	{
		ProfilerSample::ProfilerSample(std::string functionName,bool repeated)
			: funcName(functionName), repeated(repeated)
		{
			if (VE_PROFILER && (VE_DEBUG || (VE_DEBUG == false && VE_PROFILER_DEBUG_ONLY == false)))
			{
				clock.restart();
			}
		}

		ProfilerSample::~ProfilerSample()
		{
			if (VE_PROFILER && (VE_DEBUG || (VE_DEBUG == false && VE_PROFILER_DEBUG_ONLY == false)))
			{
				Profiler::init().addInfo(funcName,clock.getElapsedTime().asSeconds(),repeated);
			}
		}

		//private
	}
}