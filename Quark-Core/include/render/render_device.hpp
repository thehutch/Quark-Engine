#pragma once

#include "render_api.hpp"
#include "render_context.hpp"

namespace QE
{
	namespace Render
	{
		class RenderDevice
		{
		public:
			/**
			 *
			 */
			virtual RenderContext GetRenderContext() const = 0;

			/**
			 *
			 */
			virtual RenderAPI GetRenderAPI() const = 0;


		};

		/**
		 * Creates a render device
		 *
		 * @return A unique_ptr to the created render device, nullptr if failed
		 */
		extern "C" std::unique_ptr<RenderDevice> CreateRenderDevice();

		/**
		 *
		 */
		typedef decltype(&CreateRenderDevice) PFN_CreateRenderDevice;
	}
}
