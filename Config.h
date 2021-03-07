#pragma once

#ifndef NDEBUG
	#define VE_DEBUG true
#else
	#define VE_DEBUG false
#endif

#define VE_ENGINE_LOG true
#define VE_FILE_LOG true

#define VE_PROFILER false

#define VE_MULTITHREADING false //unused yet




#if VE_DEBUG == false //this should help avoiding checking for VE_DEBUG for everytime we use these macros
	#define VE_ENGINE_LOG false;
	#define VE_FILE_LOG false;
	#define VE_PROFILER false;
#endif