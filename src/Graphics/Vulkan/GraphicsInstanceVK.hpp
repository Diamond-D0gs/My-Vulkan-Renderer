#pragma once

#include "../GraphicsInstance.hpp"
#include "GraphicsAdapterVK.hpp"
#include "GraphicsDeviceVK.hpp"

#include <volk.h>
#include <VkBootstrap.h>

#define REQUIRED_VK_VERSION VK_MAKE_API_VERSION(0, 1, 2, 0)

namespace Oak::Graphics::VK {
	class Instance : public Graphics::Instance {
	private:
		vkb::Instance _vkInstance;

		Instance() = default;

	public:
		~Instance() { vkb::destroy_instance(_vkInstance); }

		static const Instance* CreateGraphicsInstance();

		const Device* CreateGraphicsDevice(const Adapter* const graphicsAdapter) const { 
			return Device::Create(_vkInstance, graphicsAdapter); 
		}
	};
}