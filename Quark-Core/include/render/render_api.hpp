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
