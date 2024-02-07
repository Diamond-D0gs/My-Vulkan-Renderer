#pragma once

#include "GraphicsAdapter.hpp"

#include <volk.h>
#include <VkBootstrap.h>

class GraphicsInstance;

class GraphicsDevice {
private:
	const VkDevice _vkDevice;

	GraphicsDevice(VkDevice vkDevice)
		: _vkDevice(vkDevice) {}

	static GraphicsDevice* Create(const vkb::Instance& vkInstance, const GraphicsAdapter const* graphicsAdapter);

public:
	friend GraphicsInstance;
};