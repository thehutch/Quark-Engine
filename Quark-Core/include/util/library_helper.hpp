#pragma once

#include <quark.hpp>

namespace QE
{

#ifdef _WIN32
	typedef HMODULE QE_DLHANDLE;
#else
	typedef void* QE_DLHANDLE;
#endif

	/**
	 * Loads the dynamic library with the specified name using platform-specific functions
	 *
	 * @param name The name of the library to load
	 *
	 * @return A handle to the loaded library, null is failed
	 */
	inline auto OpenLibrary(const std::string& name)
	{
#ifdef _WIN32
		return ::LoadLibrary(name.c_str());
#else
		return ::dlopen(name.c_str(), RTLD_NOW | RTLD_LOCAL);
#endif
	}

	/**
	 *
	 * @param handle
	 * @return
	 */
	inline auto CloseLibrary(QE_DLHANDLE handle)
	{
#ifdef _WIN32
		return ::FreeLibrary(handle) != 0;
#else
		return ::dlclose(handle) == 0;
#endif
	}

	/**
	 *
	 * @param handle
	 * @param name
	 * @return
	 */
	template<typename T>
	inline auto GetLibraryFunc(QE_DLHANDLE handle, const std::string& name)
	{
#ifdef _WIN32
		return reinterpret_cast<T>(::GetProcAddress(handle, name,c_str()));
#else
		return reinterpret_cast<T>(::dlsym(handle, name.c_str()));
#endif
	}
}
