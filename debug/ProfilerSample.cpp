#include "ProfilerSample.h"

#include "Engine/Config.h"
#include "Engine/debug/Profiler.h"

namespace VEngine
{
	namespace Debug
	{
		ProfilerSample::ProfilerSample(std::string functionName)
			: funcName(functionName), repeated(repeated)
		{

		}

		ProfilerSample::~ProfilerSample()
		{
#if VE_PROFILER == true
				Profiler::init().addInfo(funcName,clock.getElapsedTime().asSeconds());
#endif
		}

		//private
	}
}