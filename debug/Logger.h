#pragma once

#include <string>
#include <fstream>

#include "Engine/Config.h"

namespace VEngine
{
	namespace Debug
	{
		class Logger
		{
		public:
			enum Type
			{
				info, warning, error
			};

			static Logger& init() { static Logger instance; return instance; }

			void Log(Type type, const std::string& message, bool isEngine = false);

		private:
			std::ofstream file;
			void* stdHandle;

			Logger();
			~Logger();

			void changeConsoleColor(unsigned short color);
		};
	}
}