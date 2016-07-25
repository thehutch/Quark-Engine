#pragma once

/////////////////////////////////////////////////////////////////////////////////////
/// Library Export/Import Macros
/////////////////////////////////////////////////////////////////////////////////////

#if (defined(_WIN32) || defined(__CYGWIN__))
  #if defined(BUILD_SHARED_LIBS)
	#if defined(__GNUC__)
	  #define QE_API extern "C" __attribute__((dllexport))
	#else
	  #define QE_API extern "C" __declspec(dllexport)
	#endif
  #else
	#if defined(__GNUC__)
	  #define QE_API extern "C" __attribute__((dllimport))
	#else
	  #define QE_API extern "C" __declspec(dllimport)
	#endif
  #endif
#else
  #define QE_API extern "C" __attribute__((visibility ("default")))
#endif

/////////////////////////////////////////////////////////////////////////////////////
/// Platform Headers
/////////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32)
  #include <Windows.h>
#elif defined(__linux__)
  #include <dlfcn.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////
/// STL Headers
/////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <forward_list>
#include <unordered_map>
