#include <iostream>
#include <exception>
#include <vector>

#include "Graphics/GraphicsInstance.hpp"

int main(void) {
    auto graphicsInstance = Oak::Graphics::Instance::CreateGraphicsInstance();

    auto graphicsDevice = graphicsInstance->CreateGraphicsDevice(graphicsInstance->_adapter);

    delete graphicsDevice;
    delete graphicsInstance;

    return 0;
}