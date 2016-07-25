#include "render/render_device.hpp"
#include <iostream>

std::unique_ptr<QE::Render::RenderDevice> QE::Render::CreateRenderDevice()
{
	std::cout << "QuarkGL: Creaed RenderDevice" << std::endl;
	return nullptr;
}
