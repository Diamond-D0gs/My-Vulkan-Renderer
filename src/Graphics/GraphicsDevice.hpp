#pragma once

#include "Vulkan/GraphicsDeviceVK.hpp"

namespace Oak::Graphics {
    class Instance;
    
    class Device {
    protected:
        Device() = default;

    public:
        virtual ~Device() = default;

        friend Instance;
    };
}