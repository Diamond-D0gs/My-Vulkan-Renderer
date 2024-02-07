#pragma once

#include <volk.h>
#include <VkBootstrap.h>

#include <string>
#include <cstdint>

class GraphicsInstance;
class GraphicsDevice;

class GraphicsAdapter {
private:
	const VkPhysicalDevice _vkPhysicalDevice;

	GraphicsAdapter(VkPhysicalDevice vkPhysicalDevice)
		: _vkPhysicalDevice(vkPhysicalDevice) {}

	static GraphicsAdapter* Create(const vkb::Instance& vkInstance);

public:
	struct GraphicsAdapterInfo {
		std::u8string _name;
		uint64_t _vram;
	} const _info;

	friend GraphicsInstance;
	friend GraphicsDevice;
};
