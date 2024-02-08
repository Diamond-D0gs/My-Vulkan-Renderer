#pragma once

#include "Vulkan/GraphicsAdapterVK.hpp"

class GraphicsInstance;

class GraphicsAdapter : public GraphicsAdapterVK {
private:
    GraphicsAdapter() = default;
    ~GraphicsAdapter() = default;

public:
    friend GraphicsInstance;
};