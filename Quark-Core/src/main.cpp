#include <iostream>
#include <dlfcn.h>

#include "memory_block.hpp"
#include "render/render_device.hpp"
using namespace QE::Render;

int main(int argc, char* argv[])
{
	auto libGL = dlopen("lib/libQuark-GL.so", RTLD_NOW);
	if (libGL != nullptr)
	{
		std::cout << "Loaded QuarkGL libary" << std::endl;


		auto fnPtr = reinterpret_cast<PFN_CreateRenderDevice>(dlsym(libGL, "CreateRenderDevice"));
		if (fnPtr != nullptr)
		{
			std::cout << "Found CreateRenderDevice function" << std::endl;
			fnPtr();
		}

		dlclose(libGL);
	}
	else
	{
		std::cout << "Failed to load library" << std::endl;
	}

    return 0;
}
