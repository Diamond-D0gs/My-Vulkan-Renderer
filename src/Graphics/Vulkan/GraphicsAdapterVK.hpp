#pragma once

#include "../Base/GraphicsAdapterBase.hpp"

#include <volk.h>
#include <VkBootstrap.h>

#include <string>
#include <cstdint>

class GraphicsInstanceVK;
class GraphicsDeviceVK;

class GraphicsAdapterVK : public GraphicsAdapterBase {
protected:
	VkPhysicalDevice _vkPhysicalDevice;

	GraphicsAdapterVK() = default;

	static GraphicsAdapterVK* Create(const vkb::Instance& vkInstance);

public:
	~GraphicsAdapterVK() = default;

	struct GraphicsAdapterInfo {
		std::u8string _name;
		uint64_t _vram;
	} _info;

	friend GraphicsInstanceVK;
	friend GraphicsDeviceVK;
};
