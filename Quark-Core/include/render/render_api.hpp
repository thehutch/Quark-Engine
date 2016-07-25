#pragma once

#include "quark.hpp"

namespace QE
{
	namespace Render
	{
		enum class RenderAPI
		{
			DIRECTX,
			OPENGL,
			VULKAN
		};

		/**
		 * Converts the specified render API to a string
		 *
		 * @param api The API to get the name of
		 *
		 * @return The API name, "Unknown" if not recognised
		 */
		auto GetAPIName(RenderAPI api)
		{
			switch (api)
			{
				case RenderAPI::DIRECTX:
					return "DirectX";
				case RenderAPI::OPENGL:
					return "OpenGL";
				case RenderAPI::VULKAN:
					return "Vulkan";
				default:
					return "Unknown";
			}
		}
	}
}
