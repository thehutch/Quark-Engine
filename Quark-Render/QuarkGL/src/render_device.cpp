#include "render/render_device.hpp"
#include <iostream>

QE_API QE::Render::RenderDevice* CreateRenderDevice()
{
	std::cout << "Created Render Device" << std::endl;
	return nullptr;
}
