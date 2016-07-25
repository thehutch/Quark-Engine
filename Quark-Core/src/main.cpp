#include <iostream>

#include <render/render_device.hpp>
#include <util/library_helper.hpp>
using namespace QE::Render;

int main(int argc, char* argv[])
{
	auto libGL = QE::OpenLibrary("lib/libQuark-GL.so");
	if (libGL != nullptr)
	{
		std::cout << "Loaded QuarkGL libary" << std::endl;

		auto fnPtr = QE::GetLibraryFunc<PFN_CreateRenderDevice>(libGL, "CreateRenderDevice");
		if (fnPtr != nullptr)
		{
			std::cout << "Found CreateRenderDevice function" << std::endl;
			fnPtr();
		}

		QE::CloseLibrary(libGL);
	}
	else
	{
		std::cout << "Failed to load library" << std::endl;
	}

    return 0;
}
