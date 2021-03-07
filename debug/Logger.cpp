#include "Logger.h"

#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Engine/Config.h"
#include "Engine/debug/ProfilerSample.h"

#if VE_FILE_LOG == true
	#define AppendText(t,s) s.append(t)
#else
	#define AppendText(t,s)
#endif

namespace VEngine
{
	namespace Debug
	{

		void Logger::Log(Type type, const std::string& message, bool isEngine)
		{

#if VE_DEBUG == true
			VE_PROFILE_FUNC;
			std::string fullMessage;
			
			if (isEngine)
			{
				if (!VE_ENGINE_LOG)
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
			AppendText(mType + std::move(message) + '\n', fullMessage);

			if (VE_FILE_LOG && isEngine && file.is_open()) file << std::move(fullMessage);
#endif  //VE_DEBUG

		}

		//private
		
		Logger::Logger()
		{
#if VE_DEBUG == true 
			static_cast<HANDLE>(stdHandle);
			stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

#if VE_FILE_LOG == true
			file.open("Engine_Logs.txt", std::ios::out | std::ofstream::trunc);
			if (file.is_open() == false) Log(Type::error,"unable to open the log file for writing",true);
#endif
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