#pragma once

#include <map>

#include "Engine/Config.h"

namespace VEngine //TODO: improve profiling: no need for VE_PROF_ONCE, improve macros...
{
	namespace Debug
	{
		class Profiler //TODO: add average fps and average dt and maybe other infos to file
		{
		public:
			static Profiler& init() { static Profiler instance; return instance;}

			void addInfo(const std::string& funcName, float time);
			void logToFile(const std::string& filter = "");

		private:
			std::multimap<float, std::string,std::greater<float>> infos; //the key is the time not the name

			Profiler();
			~Profiler();

		};
	}
}