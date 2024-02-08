#pragma once

#include "GraphicsAdapterVK.hpp"
#include "GraphicsDeviceVK.hpp"
#include "../GraphicsInstance.hpp"

#include <volk.h>
#include <VkBootstrap.h>

#define REQUIRED_VK_VERSION VK_MAKE_API_VERSION(0, 1, 2, 0)

namespace Oak::Graphics::VK {
	class Instance final : public Graphics::Instance {
	private:
		vkb::Instance _vkInstance;

		Instance() = default;

	public:
		~Instance() { vkb::destroy_instance(_vkInstance); }

		static const Instance* CreateGraphicsInstance();

		const Device* CreateGraphicsDevice(const Graphics::Adapter* const graphicsAdapter) const {
			return Device::Create(static_cast<const VK::Adapter* const>(graphicsAdapter));
		}
	};
}