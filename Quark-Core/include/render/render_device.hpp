#pragma once

#include "render_api.hpp"
#include "render_context.hpp"

#include <GL/gl.h>

namespace QE
{
	namespace Render
	{
		class RenderDevice
		{
		public:
			virtual RenderContext GetRenderContext() const = 0;

			virtual RenderAPI GetRenderAPI() const = 0;
		};

		typedef RenderDevice* (*PFN_CreateRenderDevice)();
	}
}
