#pragma once

#include "../GraphicsDevice.hpp"
#include "GraphicsAdapterVK.hpp"

#include <volk.h>
#include <VkBootstrap.h>

namespace Oak::Graphics::VK {
	class Instance;

	class Device : public Graphics::Device {
	protected:
		VkDevice _vkDevice;

		Device() = default;

		static Device* Create(const vkb::Instance& vkInstance, const Adapter* const graphicsAdapter);

	public:
		~Device() { vkDestroyDevice(_vkDevice, nullptr); }

		friend Instance;
	};
}