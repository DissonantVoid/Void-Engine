#include "Profiler.h"

#include <fstream>

#include "Engine/debug/Logger.h"
#include "Engine/Config.h"

namespace VEngine
{
	namespace Debug
	{
		void Profiler::addInfo(const std::string& funcName, float time)
		{
			infos.emplace(std::make_pair(time, std::move(funcName)));
		}

		void Profiler::logToFile(const std::string& filter)//TODO: the profiler gets a lot of functions per frame which causes a big memory usage in a short time, one way to fix this is to only store functions with execution time above a threshhold
		{
#if VE_PROFILER == true

			std::ofstream file;
			file.open("Engine_Profiler.txt", std::ios::out | std::ofstream::trunc);

			if (!file.is_open())
			{
				Logger::init().Log(Logger::Type::error, "unable to open the profiler file for writing", true);
				return;
			}

			int tableSpace = 50;
			file << "funcName" << std::string((tableSpace - 8), ' ') << "time to execute" << "\n\n";

			for (auto& info : infos)
			{
				if (!filter.empty() && info.second != filter) continue;
				file << info.second;
				int size = tableSpace - info.second.size();
				if (size > 0) file << std::string(size, ' ');
				file << info.first << '\n';
			}

			Logger::init().Log(Logger::Type::info, "Profiler data successfuly logged into txt", true);
			file.close();
#endif
		}

		//private

		Profiler::Profiler()
		{
			
		}

		Profiler::~Profiler()
		{

		}

	}
}