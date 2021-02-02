#include "Profiler.h"

#include <fstream>

#include "Engine/debug/Logger.h"
#include "Engine/Config.h"

namespace VEngine
{
	namespace Debug
	{
		
		void Profiler::addInfo(std::string funcName, float time, bool repeated) //TODO: for non repeated samples, this will still be called a lot of times which is bad, also macros gards are scatered and this function don't have/need one, but macros should be more ordered
		{
			if (repeated == false)
			{
				for (auto it = infos.begin(); it != infos.end(); it++)
				{
					if (it->second == funcName) return;
				}
			}

			infos.emplace(std::make_pair(time, funcName));
		}

		void Profiler::logToFile(std::string filter)
		{
			if (!VE_PROFILER || (!VE_DEBUG && VE_PROFILER_DEBUG_ONLY)) return;

			std::ofstream file;
			file.open("Engine_Profiler.txt",std::ios::out | std::ofstream::trunc);
			
			if (!file.is_open())
			{
				Logger::init().Log(Logger::Type::error ,"unable to open the profiler file for writing", true);
				return;
			}

			int tableSpace = 50;
			file << "funcName" << std::string((tableSpace - 8),' ') << "time to execute" << "\n\n";

			for (auto& info : infos)
			{
				if (!filter.empty() && info.second != filter) continue;
				file << info.second;
				int size = tableSpace - info.second.size();
				if (size > 0) file << std::string(size,' ');
				file << info.first << '\n';
			}

			Logger::init().Log(Logger::Type::info, "Profiler data successfuly logged into txt", true);
			file.close();

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