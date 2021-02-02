#pragma once

#include <map>

namespace VEngine
{
	namespace Debug
	{
		class Profiler
		{
		public:
			static Profiler& init() { static Profiler instance; return instance;}

			void addInfo(std::string funcName,float time,bool repeated);
			void logToFile(std::string filter = "");

		private:
			std::multimap<float, std::string,std::greater<float>> infos; //the key is the time not the name

			Profiler();
			~Profiler();
		};
	}
}