#pragma once

#include "GraphicsAdapter.hpp"
#include "GraphicsDevice.hpp"

#include <volk.h>
#include <VkBootstrap.h>

#define REQUIRED_VK_VERSION VK_MAKE_API_VERSION(0, 1, 2, 0)

class GraphicsInstance {
private:
	const vkb::Instance _vkInstance;

	GraphicsInstance(vkb::Instance& vkInstance, GraphicsAdapter* graphicsAdapter)
		: _vkInstance(std::move(vkInstance)), _graphicsAdapter(graphicsAdapter) {}

public:
	const GraphicsAdapter* const _graphicsAdapter;

	~GraphicsInstance() { vkb::destroy_instance(_vkInstance); }

	static const GraphicsInstance* CreateGraphicsInstance();

	const GraphicsDevice* CreateGraphicsDevice(const GraphicsAdapter const* graphicsAdapter) const { return GraphicsDevice::Create(_vkInstance, graphicsAdapter); }
};