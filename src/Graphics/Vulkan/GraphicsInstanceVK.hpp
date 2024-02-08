#pragma once

#include "../Base/GraphicsInstanceBase.hpp"
#include "../GraphicsAdapter.hpp"
#include "GraphicsAdapterVK.hpp"
#include "GraphicsDeviceVK.hpp"

#include <volk.h>
#include <VkBootstrap.h>

#define REQUIRED_VK_VERSION VK_MAKE_API_VERSION(0, 1, 2, 0)

class GraphicsInstanceVK : public GraphicsInstanceBase {
private:
	vkb::Instance _vkInstance;

	GraphicsInstanceVK() = default;

public:
	~GraphicsInstanceVK() { vkb::destroy_instance(_vkInstance); }

	static const GraphicsInstanceVK* CreateGraphicsInstance();

	const GraphicsDeviceVK* CreateGraphicsDevice(const GraphicsAdapter const* graphicsAdapter) const { return GraphicsDeviceVK::Create(_vkInstance, graphicsAdapter); }
};