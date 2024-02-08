#pragma once

#include "GraphicsAdapter.hpp"
#include "GraphicsDevice.hpp"

namespace Oak::Graphics {
    class Instance {
    protected:
        Instance() = default;

    public:
        Adapter* _adapter;

        virtual ~Instance() = default;

        static const Instance* CreateGraphicsInstance();
        
        virtual const Device* CreateGraphicsDevice(const Adapter* const graphicsAdapter) const = 0;
    };
}