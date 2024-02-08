#pragma once

#include "Vulkan/GraphicsInstanceVK.hpp"
#include "GraphicsAdapter.hpp"
#include "GraphicsDevice.hpp"

namespace Oak::Graphics {
    class Instance {
    protected:
        Instance() = default;

    public:
        virtual ~Instance() = default;

        static const Instance* CreateGraphicsInstance();
        
        virtual const Device* CreateGraphicsDevice(const Adapter* const graphicsAdapter) const;
    };
}