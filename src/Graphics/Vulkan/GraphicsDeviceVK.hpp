#pragma once

#include "../Base/GraphicsDeviceBase.hpp"
#include "GraphicsAdapterVK.hpp"

#include <volk.h>
#include <VkBootstrap.h>

class GraphicsInstanceVK;

class GraphicsDeviceVK : public GraphicsDeviceBase {
protected:
	VkDevice _vkDevice;

	GraphicsDeviceVK() = default;

	static GraphicsDeviceVK* Create(const vkb::Instance& vkInstance, const GraphicsAdapterVK const* graphicsAdapter);

public:
	~GraphicsDeviceVK() { vkDestroyDevice(_vkDevice, nullptr); }

	friend GraphicsInstanceVK;
};