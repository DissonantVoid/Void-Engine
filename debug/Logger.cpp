#include "Logger.h"

#include <iostream>
#include <Windows.h> //TODO: consider putting this in a special VWindow.h file where some macros are defined before

#include "Engine/Config.h"
#include "Engine/debug/ProfilerSample.h"

#if defined (VE_FILE_LOG)
	#define AppendText(t,s) s.append(t)
#else
	#define AppendText(t,s)
#endif

namespace VEngine
{
	namespace Debug
	{
#if VE_DEBUG == true

		void Logger::Log(Type type, std::string message, bool isEngine)
		{
			VE_PROFILE_FUNC;
			std::string fullMessage;
			
			if (isEngine)
			{
				if (!VE_ENGINE_LOG || (type == Type::warning && !VE_ENGINE_LOG_WARNINGS) || (type == Type::info && !VE_ENGINE_LOG_INFO))
					return;

				changeConsoleColor(5);
				std::cout << "[VEngine]";
				AppendText("[VEngine]", fullMessage);
			}
			
			std::string mType;
			switch (type)
			{
			case Type::info: changeConsoleColor(2); mType = "[Info] "; break;
			case Type::warning: changeConsoleColor(6); mType = "[Warning] "; break;
			case Type::error: changeConsoleColor(4); mType = "[Error] "; break;
			}

			std::cout << mType;
			
			changeConsoleColor(7);
			std::cout << message << '\n';
			AppendText(mType + message + '\n', fullMessage);

			if (VE_FILE_LOG && isEngine && file.is_open()) file << fullMessage;
	}

#else
		void Logger::Log(Type type, std::string message, bool isEngine) {};
#endif  //VE_DEBUG

		//private
		
		Logger::Logger()
		{
			static_cast<HANDLE>(stdHandle);
			stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

			if (VE_DEBUG == true && VE_FILE_LOG)
			{
				file.open("Engine_Logs.txt", std::ios::out | std::ofstream::trunc);
				if (file.is_open() == false) Log(Type::error,"unable to open the log file for writing",true);
			
			}
		}

		Logger::~Logger()
		{
			if (file.is_open()) file.close();
		}

		void Logger::changeConsoleColor(unsigned short color)
		{
			SetConsoleTextAttribute(stdHandle, color);
		}

	}
}