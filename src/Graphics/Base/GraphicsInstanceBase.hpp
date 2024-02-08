#pragma once

#include "../GraphicsAdapter.hpp"

class GraphicsInstanceBase {
protected:
    GraphicsInstanceBase() = default;

public:
    GraphicsAdapter* _graphicsAdapter;

    virtual ~GraphicsInstanceBase() = default;
};