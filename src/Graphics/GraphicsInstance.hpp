#pragma once

#include "Vulkan/GraphicsInstanceVK.hpp"
#include "GraphicsAdapter.hpp"
#include "GraphicsDevice.hpp"

class GraphicsInstance : public GraphicsInstanceVK {
public:
    static const GraphicsInstance* CreateGraphicsInstance() { return static_cast<const GraphicsInstance*>(GraphicsInstanceVK::CreateGraphicsInstance()); }
    const GraphicsDevice* CreateGraphicsDevice(const GraphicsAdapter* const graphicsAdapter) const { return static_cast<const GraphicsDevice*>(GraphicsInstanceVK::CreateGraphicsDevice(graphicsAdapter)); }
};